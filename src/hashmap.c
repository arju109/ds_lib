#define _POSIX_C_SOURCE 200809L
#include "hashmap.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* ---- djb2 hash function ---- */
static size_t hash_key(const char *key, size_t capacity) {
    size_t hash = 5381;
    int c;
    while ((c = (unsigned char)*key++))
        hash = ((hash << 5) + hash) + c;
    return hash % capacity;
}

/* ---- Lifecycle ---- */

HashMap *hashmap_create(size_t initial_capacity) {
    if (initial_capacity == 0) initial_capacity = HASHMAP_DEFAULT_CAPACITY;
    HashMap *map = malloc(sizeof(HashMap));
    if (!map) return NULL;
    map->buckets = calloc(initial_capacity, sizeof(HashEntry *));
    if (!map->buckets) { free(map); return NULL; }
    map->capacity = initial_capacity;
    map->size     = 0;
    return map;
}

void hashmap_destroy(HashMap *map, void (*free_value)(void *)) {
    if (!map) return;
    for (size_t i = 0; i < map->capacity; i++) {
        HashEntry *entry = map->buckets[i];
        while (entry) {
            HashEntry *next = entry->next;
            free(entry->key);
            if (free_value) free_value(entry->value);
            free(entry);
            entry = next;
        }
    }
    free(map->buckets);
    free(map);
}

/* ---- Internal: resize when load factor exceeded ---- */

static int hashmap_resize(HashMap *map) {
    size_t new_capacity = map->capacity * 2;
    HashEntry **new_buckets = calloc(new_capacity, sizeof(HashEntry *));
    if (!new_buckets) return -1;

    for (size_t i = 0; i < map->capacity; i++) {
        HashEntry *entry = map->buckets[i];
        while (entry) {
            HashEntry *next  = entry->next;
            size_t     index = hash_key(entry->key, new_capacity);
            entry->next            = new_buckets[index];
            new_buckets[index]     = entry;
            entry = next;
        }
    }
    free(map->buckets);
    map->buckets  = new_buckets;
    map->capacity = new_capacity;
    return 0;
}

/* ---- Core operations ---- */

int hashmap_put(HashMap *map, const char *key, void *value) {
    if (!map || !key) return -1;

    /* Resize if needed */
    if ((double)map->size / map->capacity >= HASHMAP_LOAD_FACTOR) {
        if (hashmap_resize(map) != 0) return -1;
    }

    size_t idx = hash_key(key, map->capacity);

    /* Update existing key */
    HashEntry *entry = map->buckets[idx];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return 0;
        }
        entry = entry->next;
    }

    /* Insert new entry at front of chain */
    HashEntry *new_entry = malloc(sizeof(HashEntry));
    if (!new_entry) return -1;
    new_entry->key   = strdup(key);
    if (!new_entry->key) { free(new_entry); return -1; }
    new_entry->value = value;
    new_entry->next  = map->buckets[idx];
    map->buckets[idx] = new_entry;
    map->size++;
    return 0;
}

void *hashmap_get(const HashMap *map, const char *key) {
    if (!map || !key) return NULL;
    size_t     idx   = hash_key(key, map->capacity);
    HashEntry *entry = map->buckets[idx];
    while (entry) {
        if (strcmp(entry->key, key) == 0) return entry->value;
        entry = entry->next;
    }
    return NULL;
}

int hashmap_remove(HashMap *map, const char *key, void (*free_value)(void *)) {
    if (!map || !key) return -1;
    size_t     idx   = hash_key(key, map->capacity);
    HashEntry *entry = map->buckets[idx];
    HashEntry *prev  = NULL;

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) prev->next = entry->next;
            else       map->buckets[idx] = entry->next;
            free(entry->key);
            if (free_value) free_value(entry->value);
            free(entry);
            map->size--;
            return 0;
        }
        prev  = entry;
        entry = entry->next;
    }
    return -1; /* key not found */
}

int hashmap_contains(const HashMap *map, const char *key) {
    return hashmap_get(map, key) != NULL;
}

size_t hashmap_size(const HashMap *map)     { return map ? map->size : 0; }
int    hashmap_is_empty(const HashMap *map) { return !map || map->size == 0; }

void hashmap_foreach(const HashMap *map,
                     void (*callback)(const char *, void *, void *),
                     void *user_data) {
    if (!map || !callback) return;
    for (size_t i = 0; i < map->capacity; i++) {
        HashEntry *entry = map->buckets[i];
        while (entry) {
            callback(entry->key, entry->value, user_data);
            entry = entry->next;
        }
    }
}

void hashmap_print(const HashMap *map, void (*print_value)(const void *)) {
    if (!map || !print_value) return;
    printf("HashMap { size=%zu, capacity=%zu }\n", map->size, map->capacity);
    for (size_t i = 0; i < map->capacity; i++) {
        HashEntry *entry = map->buckets[i];
        if (!entry) continue;
        printf("  [%zu]: ", i);
        while (entry) {
            printf("%s -> ", entry->key);
            print_value(entry->value);
            if (entry->next) printf(", ");
            entry = entry->next;
        }
        printf("\n");
    }
}

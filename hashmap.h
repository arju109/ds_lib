#ifndef HASHMAP_H
#define HASHMAP_H

#include <stddef.h>

/* =========================================================
 * Hash Map — string keys, void* values, chaining collision
 * ========================================================= */

#define HASHMAP_DEFAULT_CAPACITY 16
#define HASHMAP_LOAD_FACTOR      0.75

typedef struct HashEntry {
    char             *key;
    void             *value;
    struct HashEntry *next;  /* chaining */
} HashEntry;

typedef struct {
    HashEntry **buckets;
    size_t      capacity;
    size_t      size;
} HashMap;

/* Lifecycle */
HashMap *hashmap_create(size_t initial_capacity);
void     hashmap_destroy(HashMap *map, void (*free_value)(void *));

/* Core operations */
int    hashmap_put(HashMap *map, const char *key, void *value);
void  *hashmap_get(const HashMap *map, const char *key);
int    hashmap_remove(HashMap *map, const char *key,
                      void (*free_value)(void *));
int    hashmap_contains(const HashMap *map, const char *key);

/* Queries */
size_t hashmap_size(const HashMap *map);
int    hashmap_is_empty(const HashMap *map);

/* Iteration */
void hashmap_foreach(const HashMap *map,
                     void (*callback)(const char *key, void *value,
                                      void *user_data),
                     void *user_data);

/* Utility */
void hashmap_print(const HashMap *map, void (*print_value)(const void *));

#endif /* HASHMAP_H */

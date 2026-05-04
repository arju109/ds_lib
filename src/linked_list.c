#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

/* ---- Lifecycle ---- */

LinkedList *list_create(void) {
    LinkedList *list = malloc(sizeof(LinkedList));
    if (!list) return NULL;
    list->head = NULL;
    list->size = 0;
    return list;
}

void list_destroy(LinkedList *list, void (*free_data)(void *)) {
    if (!list) return;
    Node *curr = list->head;
    while (curr) {
        Node *next = curr->next;
        if (free_data) free_data(curr->data);
        free(curr);
        curr = next;
    }
    free(list);
}

/* ---- Internal helper ---- */

static Node *make_node(void *data) {
    Node *node = malloc(sizeof(Node));
    if (!node) return NULL;
    node->data = data;
    node->next = NULL;
    return node;
}

/* ---- Mutation ---- */

int list_push_front(LinkedList *list, void *data) {
    if (!list) return -1;
    Node *node = make_node(data);
    if (!node) return -1;
    node->next = list->head;
    list->head = node;
    list->size++;
    return 0;
}

int list_push_back(LinkedList *list, void *data) {
    if (!list) return -1;
    Node *node = make_node(data);
    if (!node) return -1;
    if (!list->head) {
        list->head = node;
    } else {
        Node *curr = list->head;
        while (curr->next) curr = curr->next;
        curr->next = node;
    }
    list->size++;
    return 0;
}

int list_insert_at(LinkedList *list, size_t index, void *data) {
    if (!list || index > list->size) return -1;
    if (index == 0) return list_push_front(list, data);
    Node *node = make_node(data);
    if (!node) return -1;
    Node *curr = list->head;
    for (size_t i = 0; i < index - 1; i++) curr = curr->next;
    node->next = curr->next;
    curr->next = node;
    list->size++;
    return 0;
}

void *list_pop_front(LinkedList *list) {
    if (!list || !list->head) return NULL;
    Node *node = list->head;
    void *data = node->data;
    list->head = node->next;
    free(node);
    list->size--;
    return data;
}

void *list_pop_back(LinkedList *list) {
    if (!list || !list->head) return NULL;
    if (!list->head->next) return list_pop_front(list);
    Node *curr = list->head;
    while (curr->next->next) curr = curr->next;
    void *data = curr->next->data;
    free(curr->next);
    curr->next = NULL;
    list->size--;
    return data;
}

void *list_remove_at(LinkedList *list, size_t index) {
    if (!list || index >= list->size) return NULL;
    if (index == 0) return list_pop_front(list);
    Node *curr = list->head;
    for (size_t i = 0; i < index - 1; i++) curr = curr->next;
    Node *to_remove = curr->next;
    void *data = to_remove->data;
    curr->next = to_remove->next;
    free(to_remove);
    list->size--;
    return data;
}

/* ---- Access ---- */

void *list_get(const LinkedList *list, size_t index) {
    if (!list || index >= list->size) return NULL;
    Node *curr = list->head;
    for (size_t i = 0; i < index; i++) curr = curr->next;
    return curr->data;
}

size_t list_size(const LinkedList *list) {
    return list ? list->size : 0;
}

int list_is_empty(const LinkedList *list) {
    return !list || list->size == 0;
}

/* ---- Search ---- */

Node *list_find(const LinkedList *list, const void *target,
                int (*cmp)(const void *, const void *)) {
    if (!list || !cmp) return NULL;
    Node *curr = list->head;
    while (curr) {
        if (cmp(curr->data, target) == 0) return curr;
        curr = curr->next;
    }
    return NULL;
}

/* ---- Utility ---- */

void list_print(const LinkedList *list, void (*print_data)(const void *)) {
    if (!list || !print_data) return;
    Node *curr = list->head;
    printf("[ ");
    while (curr) {
        print_data(curr->data);
        if (curr->next) printf(" -> ");
        curr = curr->next;
    }
    printf(" ] (size=%zu)\n", list->size);
}

void list_reverse(LinkedList *list) {
    if (!list) return;
    Node *prev = NULL, *curr = list->head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->head = prev;
}

#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stddef.h>

/* =========================================================
 * Singly Linked List — generic (stores void* data)
 * ========================================================= */

typedef struct Node {
    void        *data;
    struct Node *next;
} Node;

typedef struct {
    Node  *head;
    size_t size;
} LinkedList;

/* Lifecycle */
LinkedList *list_create(void);
void        list_destroy(LinkedList *list, void (*free_data)(void *));

/* Mutation */
int  list_push_front(LinkedList *list, void *data);
int  list_push_back(LinkedList *list, void *data);
int  list_insert_at(LinkedList *list, size_t index, void *data);
void *list_pop_front(LinkedList *list);
void *list_pop_back(LinkedList *list);
void *list_remove_at(LinkedList *list, size_t index);

/* Access */
void  *list_get(const LinkedList *list, size_t index);
size_t list_size(const LinkedList *list);
int    list_is_empty(const LinkedList *list);

/* Search */
Node  *list_find(const LinkedList *list, const void *target,
                 int (*cmp)(const void *, const void *));

/* Utility */
void list_print(const LinkedList *list, void (*print_data)(const void *));
void list_reverse(LinkedList *list);

#endif /* LINKED_LIST_H */

#ifndef STACK_H
#define STACK_H

#include <stddef.h>

/* =========================================================
 * Stack — LIFO, generic (stores void* data)
 * ========================================================= */

typedef struct StackNode {
    void            *data;
    struct StackNode *next;
} StackNode;

typedef struct {
    StackNode *top;
    size_t     size;
} Stack;

/* Lifecycle */
Stack *stack_create(void);
void   stack_destroy(Stack *stack, void (*free_data)(void *));

/* Core operations */
int    stack_push(Stack *stack, void *data);
void  *stack_pop(Stack *stack);
void  *stack_peek(const Stack *stack);

/* Queries */
size_t stack_size(const Stack *stack);
int    stack_is_empty(const Stack *stack);

/* Utility */
void stack_print(const Stack *stack, void (*print_data)(const void *));

#endif /* STACK_H */

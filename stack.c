#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

Stack *stack_create(void) {
    Stack *stack = malloc(sizeof(Stack));
    if (!stack) return NULL;
    stack->top  = NULL;
    stack->size = 0;
    return stack;
}

void stack_destroy(Stack *stack, void (*free_data)(void *)) {
    if (!stack) return;
    StackNode *curr = stack->top;
    while (curr) {
        StackNode *next = curr->next;
        if (free_data) free_data(curr->data);
        free(curr);
        curr = next;
    }
    free(stack);
}

int stack_push(Stack *stack, void *data) {
    if (!stack) return -1;
    StackNode *node = malloc(sizeof(StackNode));
    if (!node) return -1;
    node->data  = data;
    node->next  = stack->top;
    stack->top  = node;
    stack->size++;
    return 0;
}

void *stack_pop(Stack *stack) {
    if (!stack || !stack->top) return NULL;
    StackNode *node = stack->top;
    void      *data = node->data;
    stack->top = node->next;
    free(node);
    stack->size--;
    return data;
}

void *stack_peek(const Stack *stack) {
    if (!stack || !stack->top) return NULL;
    return stack->top->data;
}

size_t stack_size(const Stack *stack)    { return stack ? stack->size : 0; }
int    stack_is_empty(const Stack *stack){ return !stack || stack->size == 0; }

void stack_print(const Stack *stack, void (*print_data)(const void *)) {
    if (!stack || !print_data) return;
    StackNode *curr = stack->top;
    printf("TOP -> ");
    while (curr) {
        print_data(curr->data);
        if (curr->next) printf(" -> ");
        curr = curr->next;
    }
    printf(" -> BOTTOM (size=%zu)\n", stack->size);
}

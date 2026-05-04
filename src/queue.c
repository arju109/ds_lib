#include "queue.h"
#include <stdlib.h>
#include <stdio.h>

Queue *queue_create(void) {
    Queue *queue = malloc(sizeof(Queue));
    if (!queue) return NULL;
    queue->front = queue->rear = NULL;
    queue->size  = 0;
    return queue;
}

void queue_destroy(Queue *queue, void (*free_data)(void *)) {
    if (!queue) return;
    QueueNode *curr = queue->front;
    while (curr) {
        QueueNode *next = curr->next;
        if (free_data) free_data(curr->data);
        free(curr);
        curr = next;
    }
    free(queue);
}

int queue_enqueue(Queue *queue, void *data) {
    if (!queue) return -1;
    QueueNode *node = malloc(sizeof(QueueNode));
    if (!node) return -1;
    node->data  = data;
    node->next  = NULL;
    if (!queue->rear) {
        queue->front = queue->rear = node;
    } else {
        queue->rear->next = node;
        queue->rear       = node;
    }
    queue->size++;
    return 0;
}

void *queue_dequeue(Queue *queue) {
    if (!queue || !queue->front) return NULL;
    QueueNode *node = queue->front;
    void      *data = node->data;
    queue->front = node->next;
    if (!queue->front) queue->rear = NULL;
    free(node);
    queue->size--;
    return data;
}

void *queue_peek_front(const Queue *queue){
    return (queue && queue->front) ? queue->front->data : NULL;
}
void *queue_peek_rear(const Queue *queue){
    return (queue && queue->rear)  ? queue->rear->data  : NULL;
}

size_t queue_size(const Queue *queue)     { return queue ? queue->size : 0; }
int    queue_is_empty(const Queue *queue) { return !queue || queue->size == 0; }

void queue_print(const Queue *queue, void (*print_data)(const void *)) {
    if (!queue || !print_data) return;
    QueueNode *curr = queue->front;
    printf("FRONT -> ");
    while (curr) {
        print_data(curr->data);
        if (curr->next) printf(" -> ");
        curr = curr->next;
    }
    printf(" <- REAR (size=%zu)\n", queue->size);
}

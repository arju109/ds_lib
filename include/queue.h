#ifndef QUEUE_H
#define QUEUE_H

#include <stddef.h>

/* =========================================================
 * Queue — FIFO, generic (stores void* data)
 * ========================================================= */

typedef struct QueueNode {
    void             *data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;
    QueueNode *rear;
    size_t     size;
} Queue;

/* Lifecycle */
Queue *queue_create(void);
void   queue_destroy(Queue *queue, void (*free_data)(void *));

/* Core operations */
int    queue_enqueue(Queue *queue, void *data);
void  *queue_dequeue(Queue *queue);
void  *queue_peek_front(const Queue *queue);
void  *queue_peek_rear(const Queue *queue);

/* Queries */
size_t queue_size(const Queue *queue);
int    queue_is_empty(const Queue *queue);

/* Utility */
void queue_print(const Queue *queue, void (*print_data)(const void *));

#endif /* QUEUE_H */

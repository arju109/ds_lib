#include "test_framework.h"
#include "stack.h"
#include "queue.h"

static void print_int(const void *data) { printf("%d", *(int *)data); }

void test_stack(void) {
    TEST_SUITE_BEGIN("Stack");

    Stack *s = stack_create();
    TEST_ASSERT_NOT_NULL(s,            "stack_create returns non-NULL");
    TEST_ASSERT(stack_is_empty(s),     "new stack is empty");
    TEST_ASSERT_EQ(0, (int)stack_size(s), "new stack size == 0");
    TEST_ASSERT_NULL(stack_pop(s),     "pop empty stack returns NULL");
    TEST_ASSERT_NULL(stack_peek(s),    "peek empty stack returns NULL");

    int a=10, b=20, c=30;
    stack_push(s, &a);
    stack_push(s, &b);
    stack_push(s, &c);
    TEST_ASSERT_EQ(3, (int)stack_size(s), "size == 3 after 3 pushes");
    TEST_ASSERT_EQ(30, *(int *)stack_peek(s), "peek returns 30 (top)");

    void *popped = stack_pop(s);
    TEST_ASSERT_EQ(30, *(int *)popped, "pop returns 30");
    TEST_ASSERT_EQ(20, *(int *)stack_peek(s), "peek returns 20 after pop");
    TEST_ASSERT_EQ(2, (int)stack_size(s), "size == 2 after pop");

    stack_pop(s); stack_pop(s);
    TEST_ASSERT(stack_is_empty(s), "stack empty after popping all");

    printf("  Print test: ");
    int x=1, y=2, z=3;
    stack_push(s, &x); stack_push(s, &y); stack_push(s, &z);
    stack_print(s, print_int);

    stack_destroy(s, NULL);
    TEST_ASSERT(1, "stack_destroy completes without crash");
}

void test_queue(void) {
    TEST_SUITE_BEGIN("Queue");

    Queue *q = queue_create();
    TEST_ASSERT_NOT_NULL(q,            "queue_create returns non-NULL");
    TEST_ASSERT(queue_is_empty(q),     "new queue is empty");
    TEST_ASSERT_NULL(queue_dequeue(q), "dequeue empty queue returns NULL");

    int a=10, b=20, c=30;
    queue_enqueue(q, &a);
    queue_enqueue(q, &b);
    queue_enqueue(q, &c);
    TEST_ASSERT_EQ(3, (int)queue_size(q), "size == 3 after 3 enqueues");
    TEST_ASSERT_EQ(10, *(int *)queue_peek_front(q), "peek_front == 10");
    TEST_ASSERT_EQ(30, *(int *)queue_peek_rear(q),  "peek_rear == 30");

    void *dequeued = queue_dequeue(q);
    TEST_ASSERT_EQ(10, *(int *)dequeued, "dequeue returns 10 (FIFO)");
    TEST_ASSERT_EQ(20, *(int *)queue_peek_front(q), "front is now 20");
    TEST_ASSERT_EQ(2, (int)queue_size(q), "size == 2 after dequeue");

    queue_dequeue(q); queue_dequeue(q);
    TEST_ASSERT(queue_is_empty(q), "queue empty after dequeuing all");
    TEST_ASSERT_NULL(queue_peek_front(q), "peek_front NULL on empty queue");
    TEST_ASSERT_NULL(queue_peek_rear(q),  "peek_rear  NULL on empty queue");

    printf("  Print test: ");
    int x=1, y=2, z=3;
    queue_enqueue(q, &x); queue_enqueue(q, &y); queue_enqueue(q, &z);
    queue_print(q, print_int);

    queue_destroy(q, NULL);
    TEST_ASSERT(1, "queue_destroy completes without crash");
}

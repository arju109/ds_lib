#include "test_framework.h"
#include "linked_list.h"
#include <string.h>

static int int_cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

static void print_int(const void *data) {
    printf("%d", *(int *)data);
}

void test_linked_list(void) {
    TEST_SUITE_BEGIN("Linked List");

    /* --- Create --- */
    LinkedList *list = list_create();
    TEST_ASSERT_NOT_NULL(list,       "list_create() returns non-NULL");
    TEST_ASSERT_EQ(0, list_size(list), "new list size == 0");
    TEST_ASSERT(list_is_empty(list), "new list is empty");

    /* --- push_back / push_front --- */
    int a=1, b=2, c=3, d=0;
    list_push_back(list, &a);
    list_push_back(list, &b);
    list_push_back(list, &c);
    TEST_ASSERT_EQ(3, (int)list_size(list), "size == 3 after 3 push_back");
    TEST_ASSERT_EQ(1, *(int *)list_get(list, 0), "get(0) == 1");
    TEST_ASSERT_EQ(3, *(int *)list_get(list, 2), "get(2) == 3");

    list_push_front(list, &d);
    TEST_ASSERT_EQ(4, (int)list_size(list), "size == 4 after push_front");
    TEST_ASSERT_EQ(0, *(int *)list_get(list, 0), "push_front: get(0) == 0");

    /* --- insert_at --- */
    int x = 99;
    list_insert_at(list, 2, &x);
    TEST_ASSERT_EQ(99, *(int *)list_get(list, 2), "insert_at(2): correct value");
    TEST_ASSERT_EQ(5, (int)list_size(list), "size == 5 after insert_at");

    /* --- pop_front / pop_back --- */
    void *popped = list_pop_front(list);
    TEST_ASSERT_EQ(0,  *(int *)popped, "pop_front returns 0");
    TEST_ASSERT_EQ(4, (int)list_size(list), "size == 4 after pop_front");

    popped = list_pop_back(list);
    TEST_ASSERT_EQ(3, *(int *)popped, "pop_back returns 3");

    /* --- remove_at --- */
    popped = list_remove_at(list, 0);
    TEST_ASSERT_EQ(1, *(int *)popped, "remove_at(0) returns 1");

    /* --- find --- */
    int target = 99;
    Node *found = list_find(list, &target, int_cmp);
    TEST_ASSERT_NOT_NULL(found, "list_find finds existing value");
    int missing = 42;
    Node *not_found = list_find(list, &missing, int_cmp);
    TEST_ASSERT_NULL(not_found, "list_find returns NULL for missing value");

    /* --- reverse --- */
    LinkedList *rev = list_create();
    int r1=1, r2=2, r3=3;
    list_push_back(rev, &r1);
    list_push_back(rev, &r2);
    list_push_back(rev, &r3);
    list_reverse(rev);
    TEST_ASSERT_EQ(3, *(int *)list_get(rev, 0), "reverse: first element is 3");
    TEST_ASSERT_EQ(1, *(int *)list_get(rev, 2), "reverse: last element is 1");

    /* --- boundary: out-of-bounds --- */
    void *oob = list_get(list, 999);
    TEST_ASSERT_NULL(oob, "list_get out-of-bounds returns NULL");

    /* --- print (visual check) --- */
    printf("  Print test: ");
    list_print(list, print_int);

    list_destroy(list,  NULL);
    list_destroy(rev,   NULL);
    TEST_ASSERT(1, "list_destroy completes without crash");
}

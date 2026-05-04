#include "test_framework.h"
#include "hashmap.h"
#include "bst.h"
#include <string.h>

/* ---- HashMap tests ---- */

static void print_int_val(const void *v) { printf("%d", *(int *)v); }

void test_hashmap(void) {
    TEST_SUITE_BEGIN("HashMap");

    HashMap *map = hashmap_create(0);
    TEST_ASSERT_NOT_NULL(map,             "hashmap_create returns non-NULL");
    TEST_ASSERT(hashmap_is_empty(map),    "new map is empty");
    TEST_ASSERT_EQ(0, (int)hashmap_size(map), "new map size == 0");

    int v1=100, v2=200, v3=300;
    hashmap_put(map, "alpha",   &v1);
    hashmap_put(map, "beta",    &v2);
    hashmap_put(map, "gamma",   &v3);
    TEST_ASSERT_EQ(3, (int)hashmap_size(map), "size == 3 after 3 puts");

    void *result = hashmap_get(map, "alpha");
    TEST_ASSERT_NOT_NULL(result, "get 'alpha' returns non-NULL");
    TEST_ASSERT_EQ(100, *(int *)result, "get 'alpha' == 100");

    TEST_ASSERT(hashmap_contains(map, "beta"), "contains 'beta' == true");
    TEST_ASSERT(!hashmap_contains(map, "zzz"), "contains 'zzz' == false");

    /* Update existing key */
    int v1_new = 999;
    hashmap_put(map, "alpha", &v1_new);
    result = hashmap_get(map, "alpha");
    TEST_ASSERT_EQ(999, *(int *)result, "updated 'alpha' == 999");
    TEST_ASSERT_EQ(3, (int)hashmap_size(map), "size still 3 after update");

    /* Remove */
    int removed = hashmap_remove(map, "beta", NULL);
    TEST_ASSERT_EQ(0, removed, "remove 'beta' returns 0 (success)");
    TEST_ASSERT_EQ(2, (int)hashmap_size(map), "size == 2 after remove");
    TEST_ASSERT(!hashmap_contains(map, "beta"), "beta no longer in map");

    int bad_remove = hashmap_remove(map, "nosuchkey", NULL);
    TEST_ASSERT_EQ(-1, bad_remove, "remove missing key returns -1");

    /* NULL safety */
    TEST_ASSERT_NULL(hashmap_get(map, "missing"), "get missing key returns NULL");

    /* Load factor / resize stress */
    HashMap *stress = hashmap_create(4);
    char key[16];
    int  vals[100];
    for (int i = 0; i < 100; i++) {
        snprintf(key, sizeof(key), "key%d", i);
        vals[i] = i * 10;
        hashmap_put(stress, key, &vals[i]);
    }
    TEST_ASSERT_EQ(100, (int)hashmap_size(stress), "stress: size == 100");
    snprintf(key, sizeof(key), "key50");
    result = hashmap_get(stress, key);
    TEST_ASSERT_NOT_NULL(result, "stress: get key50 non-NULL");
    TEST_ASSERT_EQ(500, *(int *)result, "stress: key50 == 500");

    hashmap_destroy(stress, NULL);
    hashmap_destroy(map,    NULL);
    TEST_ASSERT(1, "hashmap_destroy completes without crash");
}

/* ---- BST tests ---- */

static int int_cmp(const void *a, const void *b) {
    return *(int *)a - *(int *)b;
}

static void print_int(const void *data) {
    printf("%d ", *(int *)data);
}

void test_bst(void) {
    TEST_SUITE_BEGIN("Binary Search Tree");

    BST *tree = bst_create(int_cmp);
    TEST_ASSERT_NOT_NULL(tree,            "bst_create returns non-NULL");
    TEST_ASSERT(bst_is_empty(tree),       "new tree is empty");
    TEST_ASSERT_EQ(-1, bst_height(tree),  "empty tree height == -1");

    int vals[] = {50, 30, 70, 20, 40, 60, 80};
    for (int i = 0; i < 7; i++) bst_insert(tree, &vals[i]);

    TEST_ASSERT_EQ(7, (int)bst_size(tree), "size == 7 after 7 inserts");
    TEST_ASSERT_EQ(2, bst_height(tree),    "height == 2 (balanced tree)");

    /* Search */
    int target = 40;
    void *found = bst_search(tree, &target);
    TEST_ASSERT_NOT_NULL(found, "search finds 40");
    TEST_ASSERT_EQ(40, *(int *)found, "search returns correct value");

    int missing = 99;
    void *not_found = bst_search(tree, &missing);
    TEST_ASSERT_NULL(not_found, "search returns NULL for missing value");

    /* Min / Max */
    TEST_ASSERT_EQ(20, *(int *)bst_min(tree), "min == 20");
    TEST_ASSERT_EQ(80, *(int *)bst_max(tree), "max == 80");

    /* Duplicate insert */
    int dup = 50;
    int dup_result = bst_insert(tree, &dup);
    TEST_ASSERT_EQ(1, dup_result,              "duplicate insert returns 1");
    TEST_ASSERT_EQ(7, (int)bst_size(tree),     "size unchanged after duplicate");

    /* Delete leaf */
    int del = 20;
    bst_delete(tree, &del, NULL);
    TEST_ASSERT_EQ(6, (int)bst_size(tree), "size == 6 after deleting leaf 20");
    TEST_ASSERT_NULL(bst_search(tree, &del), "deleted node not found");

    /* Delete node with two children */
    int del2 = 30;
    bst_delete(tree, &del2, NULL);
    TEST_ASSERT_EQ(5, (int)bst_size(tree),  "size == 5 after deleting node 30");
    TEST_ASSERT_NULL(bst_search(tree, &del2), "deleted node not found");

    /* Traversal */
    printf("  Inorder   (should be sorted): ");
    bst_inorder(tree, print_int);
    printf("\n");
    printf("  Preorder  : ");
    bst_preorder(tree, print_int);
    printf("\n");
    printf("  Postorder : ");
    bst_postorder(tree, print_int);
    printf("\n");

    bst_destroy(tree, NULL);
    TEST_ASSERT(1, "bst_destroy completes without crash");
}

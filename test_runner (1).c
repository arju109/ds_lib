#include "test_framework.h"
#include <stdio.h>

int _tests_run    = 0;
int _tests_passed = 0;
int _tests_failed = 0;

void test_linked_list(void);
void test_stack(void);
void test_queue(void);
void test_hashmap(void);
void test_bst(void);

int main(void) {
    printf("\033[1m========================================\033[0m\n");
    printf("\033[1m   Data Structures Library — Test Suite \033[0m\n");
    printf("\033[1m========================================\033[0m\n");

    test_linked_list();
    test_stack();
    test_queue();
    test_hashmap();
    test_bst();

    printf("\n\033[1m========================================\033[0m\n");
    TEST_SUMMARY();
    printf("\033[1m========================================\033[0m\n\n");

    return TEST_EXIT_CODE();
}

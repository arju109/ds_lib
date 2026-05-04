#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>

extern int _tests_run;
extern int _tests_passed;
extern int _tests_failed;

#define TEST_ASSERT(condition, message)                                \
    do {                                                               \
        _tests_run++;                                                  \
        if (condition) {                                               \
            _tests_passed++;                                           \
            printf("  \033[32m[PASS]\033[0m %s\n", message);         \
        } else {                                                       \
            _tests_failed++;                                           \
            printf("  \033[31m[FAIL]\033[0m %s  (line %d)\n",        \
                   message, __LINE__);                                 \
        }                                                              \
    } while (0)

#define TEST_ASSERT_NULL(ptr, msg)     TEST_ASSERT((ptr) == NULL, msg)
#define TEST_ASSERT_NOT_NULL(ptr, msg) TEST_ASSERT((ptr) != NULL, msg)
#define TEST_ASSERT_EQ(a, b, msg)      TEST_ASSERT((a) == (b), msg)
#define TEST_ASSERT_NE(a, b, msg)      TEST_ASSERT((a) != (b), msg)

#define TEST_SUITE_BEGIN(name) \
    printf("\n\033[1m=== %s ===\033[0m\n", name)

#define TEST_SUMMARY()                                                 \
    do {                                                               \
        printf("\n\033[1mResults: %d/%d passed", _tests_passed, _tests_run); \
        if (_tests_failed == 0)                                        \
            printf("  \033[32mall tests passed!\033[0m\n");           \
        else                                                           \
            printf("  \033[31m%d failed\033[0m\n", _tests_failed);   \
        printf("\033[0m");                                             \
    } while (0)

#define TEST_EXIT_CODE() (_tests_failed == 0 ? 0 : 1)

#endif /* TEST_FRAMEWORK_H */

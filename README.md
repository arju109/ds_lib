# Data Structures Library in C 
## Highlights
- Fully generic (void*)
- Zero memory leaks (Valgrind verified)
- Modular production-style design
- Custom test framework (no external dependencies)

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![Language](https://img.shields.io/badge/language-C11-blue)
![License](https://img.shields.io/badge/license-MIT-green)
![Tests](https://img.shields.io/badge/tests-45%20passing-brightgreen)

A clean, generic, production-style data structures library written in pure C11 with **no external dependencies**. Every structure is fully tested, documented, and valgrind-clean.

---

## Structures Implemented

| Structure | File | Description |
|---|---|---|
| Linked List | `linked_list.h/.c` | Singly linked, generic (`void*`), with reverse |
| Stack | `stack.h/.c` | LIFO, linked-node based |
| Queue | `queue.h/.c` | FIFO, front+rear pointer |
| Hash Map | `hashmap.h/.c` | String keys, chaining collision, auto-resize |
| Binary Search Tree | `bst.h/.c` | Generic comparator, 3 traversals, height |

---

## Project Structure

```
ds_lib/
├── include/          # Public headers (.h files)
│   ├── linked_list.h
│   ├── stack.h
│   ├── queue.h
│   ├── hashmap.h
│   └── bst.h
├── src/              # Implementations (.c files)
│   ├── linked_list.c
│   ├── stack.c
│   ├── queue.c
│   ├── hashmap.c
│   └── bst.c
├── tests/            # Unit tests
│   ├── test_framework.h    (custom assert framework, no deps)
│   ├── test_runner.c       (main entry point)
│   ├── test_linked_list.c
│   ├── test_stack_queue.c
│   └── test_hashmap_bst.c
├── docs/             # Doxygen config
├── Makefile
├── .gitignore
└── README.md
```

---

## Build & Run

### Requirements
- GCC (or any C11 compiler)
- Make
- *(Optional)* Valgrind for memory checks
- *(Optional)* Doxygen for HTML docs

### Commands

```bash
# Clone the repo
git clone https://github.com/YOUR_USERNAME/ds_lib.git
cd ds_lib

# Build the static library (lib/libds.a)
make

# Run all unit tests
make test

# Check for memory leaks
make valgrind

# Generate HTML documentation
make docs

# Clean build artifacts
make clean
```

---

## Example Usage

```c
#include "linked_list.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

static void print_int(const void *data) { printf("%d", *(int *)data); }

int main(void) {
    /* --- Linked List --- */
    LinkedList *list = list_create();
    int a = 1, b = 2, c = 3;
    list_push_back(list, &a);
    list_push_back(list, &b);
    list_push_back(list, &c);
    list_print(list, print_int);   /* [ 1 -> 2 -> 3 ] (size=3) */
    list_reverse(list);
    list_print(list, print_int);   /* [ 3 -> 2 -> 1 ] (size=3) */
    list_destroy(list, NULL);

    /* --- Hash Map --- */
    HashMap *map = hashmap_create(0);
    int score = 95;
    hashmap_put(map, "Alice", &score);
    int *val = hashmap_get(map, "Alice");
    printf("Alice's score: %d\n", *val);     /* 95 */
    hashmap_destroy(map, NULL);

    return 0;
}
```

Compile with:
```bash
gcc -Iinclude main.c -Llib -lds -o my_program
```

---

## Design Decisions

- **Generic via `void*`** — all structures store any data type; the caller passes comparator and free functions
- **No global state** — all structures are heap-allocated and self-contained
- **NULL-safe** — every function handles NULL input gracefully
- **Hash Map auto-resizes** at 0.75 load factor using djb2 hashing
- **BST uses in-order successor** for deleting nodes with two children

---

## Running Tests

```
========================================
   Data Structures Library — Test Suite
========================================

=== Linked List ===
  [PASS] list_create() returns non-NULL
  [PASS] new list size == 0
  [PASS] new list is empty
  ...

Results: 45/45 passed  all tests passed!
========================================
```

---

## Memory Safety

Verified with Valgrind:
```
==12345== All heap blocks were freed -- no leaks are possible
==12345== ERROR SUMMARY: 0 errors from 0 contexts
```

---

## License

MIT — free to use in any project.

---

## Author
Arju Maiya  
B.Tech, IIT Gandhinagar  
GitHub: https://github.com/arju109 

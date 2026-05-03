#ifndef BST_H
#define BST_H

#include <stddef.h>

/* =========================================================
 * Binary Search Tree — generic, user-supplied comparator
 * ========================================================= */

typedef struct BSTNode {
    void            *data;
    struct BSTNode  *left;
    struct BSTNode  *right;
} BSTNode;

typedef struct {
    BSTNode *root;
    size_t   size;
    int    (*cmp)(const void *, const void *);
} BST;

/* Lifecycle */
BST  *bst_create(int (*cmp)(const void *, const void *));
void  bst_destroy(BST *tree, void (*free_data)(void *));

/* Mutation */
int  bst_insert(BST *tree, void *data);
int  bst_delete(BST *tree, const void *data, void (*free_data)(void *));

/* Search */
void *bst_search(const BST *tree, const void *data);
void *bst_min(const BST *tree);
void *bst_max(const BST *tree);

/* Traversal — callback receives each node's data */
void bst_inorder(const BST *tree,   void (*visit)(const void *));
void bst_preorder(const BST *tree,  void (*visit)(const void *));
void bst_postorder(const BST *tree, void (*visit)(const void *));

/* Queries */
size_t bst_size(const BST *tree);
int    bst_is_empty(const BST *tree);
int    bst_height(const BST *tree);

#endif /* BST_H */

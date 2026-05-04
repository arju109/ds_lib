#include "../include/bst.h"
#include <stdlib.h>
#include <stdio.h>

/* ---- Lifecycle ---- */

BST *bst_create(int (*cmp)(const void *, const void *)) {
    if (!cmp) return NULL;
    BST *tree = malloc(sizeof(BST));
    if (!tree) return NULL;
    tree->root = NULL;
    tree->size = 0;
    tree->cmp  = cmp;
    return tree;
}

static void destroy_recursive(BSTNode *node, void (*free_data)(void *)) {
    if (!node) return;
    destroy_recursive(node->left,  free_data);
    destroy_recursive(node->right, free_data);
    if (free_data) free_data(node->data);
    free(node);
}

void bst_destroy(BST *tree, void (*free_data)(void *)) {
    if (!tree) return;
    destroy_recursive(tree->root, free_data);
    free(tree);
}

/* ---- Mutation ---- */

static BSTNode *insert_recursive(BSTNode *node, void *data,
                                  int (*cmp)(const void *, const void *),
                                  int *inserted) {
    if (!node) {
        BSTNode *new_node = malloc(sizeof(BSTNode));
        if (!new_node) return NULL;
        new_node->data  = data;
        new_node->left  = new_node->right = NULL;
        *inserted = 1;
        return new_node;
    }
    int result = cmp(data, node->data);
    if (result < 0)
        node->left  = insert_recursive(node->left,  data, cmp, inserted);
    else if (result > 0)
        node->right = insert_recursive(node->right, data, cmp, inserted);
    /* Equal keys: no duplicate insert */
    return node;
}

int bst_insert(BST *tree, void *data) {
    if (!tree) return -1;
    int inserted = 0;
    tree->root = insert_recursive(tree->root, data, tree->cmp, &inserted);
    if (inserted) tree->size++;
    return inserted ? 0 : 1; /* 1 = duplicate */
}

/* Find in-order successor (smallest in right subtree) */
static BSTNode *min_node(BSTNode *node) {
    while (node->left) node = node->left;
    return node;
}

static BSTNode *delete_recursive(BSTNode *node, const void *data,
                                   int (*cmp)(const void *, const void *),
                                   void (*free_data)(void *),
                                   int *deleted) {
    if (!node) return NULL;
    int result = cmp(data, node->data);
    if (result < 0) {
        node->left  = delete_recursive(node->left,  data, cmp, free_data, deleted);
    } else if (result > 0) {
        node->right = delete_recursive(node->right, data, cmp, free_data, deleted);
    } else {
        *deleted = 1;
        if (!node->left) {
            BSTNode *right = node->right;
            if (free_data) free_data(node->data);
            free(node);
            return right;
        }
        if (!node->right) {
            BSTNode *left = node->left;
            if (free_data) free_data(node->data);
            free(node);
            return left;
        }
        /* Two children: replace with in-order successor */
        BSTNode *successor = min_node(node->right);
        node->data  = successor->data;
        node->right = delete_recursive(node->right, successor->data,
                                        cmp, NULL, deleted);
        *deleted = 1; /* already counted once */
    }
    return node;
}

int bst_delete(BST *tree, const void *data, void (*free_data)(void *)) {
    if (!tree) return -1;
    int deleted = 0;
    tree->root = delete_recursive(tree->root, data, tree->cmp,
                                   free_data, &deleted);
    if (deleted) tree->size--;
    return deleted ? 0 : -1;
}

/* ---- Search ---- */

void *bst_search(const BST *tree, const void *data) {
    if (!tree) return NULL;
    BSTNode *curr = tree->root;
    while (curr) {
        int result = tree->cmp(data, curr->data);
        if      (result < 0) curr = curr->left;
        else if (result > 0) curr = curr->right;
        else                 return curr->data;
    }
    return NULL;
}

void *bst_min(const BST *tree) {
    if (!tree || !tree->root) return NULL;
    return min_node(tree->root)->data;
}

void *bst_max(const BST *tree) {
    if (!tree || !tree->root) return NULL;
    BSTNode *node = tree->root;
    while (node->right) node = node->right;
    return node->data;
}

/* ---- Traversal ---- */

static void inorder_rec(const BSTNode *node, void (*visit)(const void *)) {
    if (!node) return;
    inorder_rec(node->left, visit);
    visit(node->data);
    inorder_rec(node->right, visit);
}

static void preorder_rec(const BSTNode *node, void (*visit)(const void *)) {
    if (!node) return;
    visit(node->data);
    preorder_rec(node->left, visit);
    preorder_rec(node->right, visit);
}

static void postorder_rec(const BSTNode *node, void (*visit)(const void *)) {
    if (!node) return;
    postorder_rec(node->left, visit);
    postorder_rec(node->right, visit);
    visit(node->data);
}

void bst_inorder(const BST *tree, void (*visit)(const void *)) {
    if (tree) inorder_rec(tree->root, visit);
}
void bst_preorder(const BST *tree, void (*visit)(const void *)) {
    if (tree) preorder_rec(tree->root, visit);
}
void bst_postorder(const BST *tree, void (*visit)(const void *)) {
    if (tree) postorder_rec(tree->root, visit);
}

/* ---- Queries ---- */

size_t bst_size(const BST *tree)     { return tree ? tree->size : 0; }
int    bst_is_empty(const BST *tree) { return !tree || tree->size == 0; }

static int height_rec(const BSTNode *node) {
    if (!node) return -1;
    int left  = height_rec(node->left);
    int right = height_rec(node->right);
    return 1 + (left > right ? left : right);
}

int bst_height(const BST *tree) {
    return tree ? height_rec(tree->root) : -1;
}

#include <string.h>
#include <stdio.h>
#include "tree.h"
#include "dialog.h"

void treeInorderWalk(Node *ptr) {
    if (ptr != NULL) {
        treeInorderWalk(ptr->left);
        printf("%s: ", ptr->key);
        printData(ptr->data, ptr->len);
        treeInorderWalk(ptr->right);
    }
}

Node *treeSearch(Node *ptr, char *key) {
    while ((ptr != NULL) && (strcmp(key, ptr->key) != 0)) {
        if (strcmp(key, ptr->key) < 0) {
            ptr = ptr->left;
        } else {
            ptr = ptr->right;
        }
    }
    return ptr;
}

Node *treeMinimum(Node *ptr) {
    while (ptr->left != NULL) {
        ptr = ptr->left;
    }
    return ptr;
}

Node *treeMaximum(Node *ptr) {
    while (ptr->right != NULL) {
        ptr = ptr->right;
    }
    return ptr;
}

Node *treeSuccessor(Node *prt) {
    if (prt->right != NULL) {
        return treeMinimum(prt->right);
    }
    Node *x = prt->p;
    while ((x != NULL) && (prt == x->right)) {
        prt = x;
        x = x->p;
    }
    return x;
}

Node *treePredecessor(Node *ptr) {
    if (ptr->left != NULL) {
        return treeMaximum(ptr->left);
    }
    Node *x = ptr->p;
    while ((x != NULL) && (ptr == x->left)) {
        ptr = x;
        x = x->p;
    }
    return x;
}

void treeInsert(Tree *tree, Node *ptr) {
    int i = 0;
    Node *y = NULL;
    Node *x = tree->root;
    while (x != NULL) {
        y = x;
        if (strcmp(ptr->key, x->key) < 0) {
            x = x->left;
        } else {
            x = x->right;
        }
        i++;
    }
    ptr->p = y;
    if (y == NULL) {
        tree->root = ptr;
    } else if (strcmp(ptr->key, y->key) < 0) {
        y->left = ptr;
    } else {
        y->right = ptr;
    }
    // Обновление высоты дерева
    if (i > tree->size) {
        tree->size = i;
    }
}

void transplant(Tree *tree, Node *x, Node *y) {
    if (x->p == NULL) {
        tree->root = y;
    } else if (x == x->p->left) {
        x->p->left = y;
    } else {
        x->p->right = y;
    }
    if (y != NULL) {
        y->p = x->p;
    }
}

void treeDelete(Tree *tree, Node *ptr) {
    if (ptr->left == NULL) {
        transplant(tree, ptr, ptr->right);
    } else if (ptr->right == NULL) {
        transplant(tree, ptr, ptr->left);
    } else {
        Node *x = treeMinimum(ptr->right);
        if (x->p != ptr) {
            transplant(tree, x, x->right);
            x->right = ptr->right;
            x->right->p = x;
        }
        transplant(tree, ptr, x);
        x->left = ptr->left;
        x->left->p = x;
    }
}
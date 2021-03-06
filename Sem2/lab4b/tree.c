#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Node *BtreeSearch(Node *ptr, int key, int *index) {
    int i = 0;
    if (!ptr)
        return NULL;
    while (i < ptr->n && key > ptr->key[i])
        i++;
    if (i < ptr->n && key == ptr->key[i]) {
        *index = i;
        return ptr;
    }
    else if (ptr->leaf)
        return NULL;
    else
        return BtreeSearch(ptr->ch[i], key, index);
}

Tree *BtreeCreate(Tree *tree) {
    Node *r = calloc(1, sizeof(Node));
    r->leaf = 1;
    r->n = 0;
    r->p = NULL;
    tree->root = r;
    return tree;
}

void BtreeSplitChild(Node *par, int i) {
    Node *ptr = calloc(1, sizeof(Node));
    Node *child = par->ch[i];
    ptr->p = par;
    ptr->leaf = child->leaf;
    ptr->n = 1;
    ptr->key[0] = child->key[2];
    ptr->data[0] = child->data[2];
    if (!child->leaf) {
        ptr->ch[0] = child->ch[2];
        ptr->ch[0]->p = ptr;
        ptr->ch[1] = child->ch[3];
        ptr->ch[1]->p = ptr;
    }
    child->n = 1;
    for (int j = par->n + 1; j > i + 1; j--)
        par->ch[j] = par->ch[j - 1];
    par->ch[i + 1] = ptr;
    for (int j = par->n; j > i; j--) {
        par->key[j] = par->key[j - 1];
        par->data[j] = par->data[j - 1];
    }
    par->key[i] = child->key[1];
    par->data[i] = child->data[1];
    (par->n)++;
    if (par->n == 3 && par->p) {
        i = 0;
        while (par->p->ch[i] != par && i < par->p->n)
            i++;
        BtreeSplitChild(par->p, i);
    }
}

void BtreeInsert(Tree *tree, Node *ptr, int key, Data *data) {
    BtreeInsertNonfull(ptr, key, data);
    Node *r = tree->root;
    if (r->n == 3) {
        Node *new_root = calloc(1, sizeof(Node));
        tree->root = new_root;
        new_root->p = NULL;
        r->p = new_root;
        new_root->leaf = 0;
        new_root->n = 0;
        new_root->ch[0] = r;
        BtreeSplitChild(new_root, 0);
    }
}

void BtreeInsertNonfull(Node *ptr, int key, Data *data) {
    if (ptr) {
        int i = ptr->n;
        if (ptr->leaf) {
            while (i >= 1 && key < ptr->key[i - 1]) {
                ptr->key[i] = ptr->key[i - 1];
                ptr->data[i] = ptr->data[i - 1];
                i--;
            }
            ptr->key[i] = key;
            ptr->data[i] = data;
            (ptr->n)++;
            if (ptr->p != NULL && ptr->n >= 3) {
                int j = 0;
                while (ptr->p->ch[j] != ptr && j < ptr->p->n)
                    j++;
                BtreeSplitChild(ptr->p, j);
            }
        } else {
            while (i >= 1 && key < ptr->key[i - 1])
                i--;
            BtreeInsertNonfull(ptr->ch[i], key, data);
            if (ptr->ch[i] && ptr->ch[i]->n == 3) {
                BtreeSplitChild(ptr, i);
            }
        }
    }
}

void BtreeInsertNonfull_extra(Node *ptr, int key) {
    int i = ptr->n;
    while (i >= 1 && key < ptr->key[i - 1]) {
        ptr->key[i] = ptr->key[i - 1];
        i--;
    }
    ptr->key[i] = key;
    (ptr->n)++;
}

Node *BtreeSearchMax(Node *ptr) {
    if (!ptr)
        return ptr;
    if (ptr->leaf)
        return ptr;
    else
        return BtreeSearchMax(ptr->ch[ptr->n]);
}

Node *BtreeSearchMin(Node *ptr) {
    if (!ptr)
        return ptr;
    if (ptr->leaf)
        return ptr;
    else
        return BtreeSearchMin(ptr->ch[0]);
}
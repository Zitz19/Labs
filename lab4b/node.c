#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "tree.h"

Node *newNode(float f, char *str) {
    Node *ptr = calloc(1, sizeof(Node));
    ptr->data[0]->f = f;
    ptr->data[0]->str = str;
    return ptr;
}

void Insert(Tree *tree, int key, Data *data) {
    Node *ptr = tree->root;
    printf("%f %s\n", data->f, data->str);
    int j;
    if (!ptr) {
        tree = BtreeCreate(tree);
        ptr = tree->root;
    }
    while (!ptr->leaf) {
        j = 0;
        while (key > ptr->key[j] && j < ptr->n)
            j++;
        ptr = ptr->ch[j];
    }
    BtreeInsert(tree, ptr, key, data);
}

void swap(int *x, int *y) {
    int z = *x;
    *x = *y;
    *y = z;
}

void removeFromNode(Node *ptr, int key) {
    if (ptr->n >= 1 && ptr->key[0] == key) {
        ptr->key[0] = ptr->key[1];
        ptr->key[1] = ptr->key[2];
        ptr->n--;
    }
    else if (ptr->n == 2 && ptr->key[1] == key) {
        ptr->key[1] = ptr->key[2];
        ptr->n--;
    }
}

Node *Redistribute(Node *ptr) {
    Node *par = ptr->p;
    Node *first = par->ch[0];
    Node *second = par->ch[1];
    Node *third = par->ch[2];
    if (par->n == 2 && first->n < 2 && second->n < 2 && third->n < 2) {
        if (first == ptr) {
            par->ch[0] = par->ch[1];
            par->ch[1] = par->ch[2];
            par->ch[2] = NULL;
            BtreeInsertNonfull(par->ch[0], par->key[0], NULL);
            par->ch[0]->ch[2] = par->ch[0]->ch[1];
            par->ch[0]->ch[1] = par->ch[0]->ch[0];
            if (ptr->ch[0] != NULL)
                par->ch[0]->ch[0] = ptr->ch[0];
            else if (ptr->ch[1] != NULL)
                par->ch[0]->ch[0] = ptr->ch[1];
            if (par->ch[0]->ch[0] != NULL)
                par->ch[0]->ch[0]->p = par->ch[0];
            removeFromNode(par, par->key[0]);
            free(first);
        }
        else if (second == ptr) {
            BtreeInsertNonfull(first, par->key[0], NULL);
            removeFromNode(par, par->key[0]);
            if (ptr->ch[0] != NULL)
                first->ch[2] = ptr->ch[0];
            else if (ptr->ch[1] != NULL)
                first->ch[2] = ptr->ch[1];
            if  (first->ch[2] != NULL)
                first->ch[2]->p = first;
            par->ch[1] = par->ch[2];
            par->ch[2] = NULL;
            free(second);
        }
        else if (third == ptr) {
            BtreeInsertNonfull(second, par->key[1], NULL);
            par->ch[2] = NULL;
            removeFromNode(par, par->key[1]);
            if (ptr->ch[0] != NULL)
                second->ch[2] = ptr->ch[0];
            else if (ptr->ch[1] != NULL)
                second->ch[2] = ptr->ch[1];
            if (second->ch[2] != NULL)
                second->ch[2]->p = second;
            free(third);
        }
    }
    else if (par->n == 2 && (first->n == 2 || second->n == 2 || third->n == 2)) {
        if (third == ptr) {
            if (ptr->ch[0] != NULL) {
                ptr->ch[1] = ptr->ch[0];
                ptr->ch[0] = NULL;
            }
            BtreeInsertNonfull(ptr, par->key[1], NULL);
            if (second->n == 2) {
                par->key[1] = second->key[1];
                removeFromNode(second, second->key[1]);
                ptr->ch[0] = second->ch[2];
                second->ch[2] = NULL;
                if (ptr->ch[0] != NULL)
                    ptr->ch[0]->p = ptr;
            } else if (first->n == 2) {
                par->key[1] = second->key[0];
                ptr->ch[0] = second->ch[1];
                second->ch[1] = second->ch[0];
                if (ptr->ch[0] != NULL)
                    ptr->ch[0]->p = ptr;
                second->key[0] = par->key[0];
                par->key[0] = first->key[1];
                removeFromNode(first, first->key[1]);
                second->ch[0] = first->ch[2];
                if (second->ch[0] != NULL)
                    second->ch[0]->p = par;
                first->ch[2] = NULL;
            }
        } else if (second == ptr) {
            if (third->n == 2) {
                if (ptr->ch[0] == NULL) {
                    ptr->ch[0] = ptr->ch[1];
                    ptr->ch[1] = NULL;
                }
                BtreeInsertNonfull(second, par->key[1], NULL);
                par->key[1] = third->key[0];
                removeFromNode(third, third->key[0]);
                second->ch[1] = third->ch[0];
                if (second->ch[1] != NULL)
                    second->ch[1]->p = second;
                third->ch[0] = third->ch[1];
                third->ch[1] = third->ch[2];
                third->ch[2] = NULL;
            } else if (first->n == 2) {
                if (ptr->ch[1] == NULL) {
                    ptr->ch[1] = ptr->ch[0];
                    ptr->ch[0] = NULL;
                }
                BtreeInsertNonfull(second, par->key[0], NULL);
                par->key[0] = first->key[1];
                removeFromNode(first, first->key[1]);
                second->ch[0] = first->ch[2];
                if (second->ch[0] != NULL)
                    second->ch[0]->p = second;
                first->ch[2] = NULL;
            }
        } else if (first == ptr) {
            if (ptr->ch[0] == NULL) {
                ptr->ch[0] = ptr->ch[1];
                ptr->ch[1] = NULL;
            }
            BtreeInsertNonfull(first, par->key[0], NULL);
            if (second->n == 2) {
                par->key[0] = second->key[0];
                removeFromNode(second, second->key[0]);
                first->ch[1] = second->ch[0];
                if (first->ch[1] != NULL)
                    first->ch[1]->p = first;
                second->ch[0] = second->ch[1];
                second->ch[1] = second->ch[2];
                second->ch[2] = NULL;
            } else if (third->n == 2) {
                par->key[0] = second->key[0];
                second->key[0] = par->key[1];
                par->key[1] = third->key[0];
                removeFromNode(third, third->key[0]);
                first->ch[1] = second->ch[0];
                if (first->ch[1] != NULL)
                    first->ch[1]->p = first;
                second->ch[0] = second->ch[1];
                second->ch[1] =third->ch[0];
                if (second->ch[1] != NULL)
                    second->ch[1]->p = second;
                third->ch[0] = third->ch[1];
                third->ch[1] = third->ch[2];
                third->ch[2] = NULL;
            }
        }
    } else if (par->n == 1) {
        BtreeInsertNonfull(ptr, par->key[0], NULL);
        if (first == ptr && second->n == 2) {
            par->key[0] = second->key[0];
            removeFromNode(second, second->key[0]);
            if (ptr->ch[0] == NULL)
                ptr->ch[0] = ptr->ch[1];
            ptr->ch[1] = second->ch[0];
            second->ch[0] = second->ch[1];
            second->ch[1] = second->ch[2];
            second->ch[2] = NULL;
            if (ptr->ch[1] != NULL)
                ptr->ch[1]->p = ptr;
        } else if (second == ptr && first->n == 2) {
            par->key[0] = first->key[1];
            removeFromNode(first, first->key[1]);
            if (ptr->ch[1] == NULL)
                ptr->ch[1] = ptr->ch[0];
            ptr->ch[0] = first->ch[2];
            first->ch[2] = NULL;
            if (ptr->ch[0] != NULL)
                ptr->ch[0]->p = ptr;
        }
    }
    return par;
}

Node *Merge(Node *ptr) {
    Node *par = ptr->p;
    if (par->ch[0] == ptr) {
        BtreeInsertNonfull_extra(par->ch[1], par->key[0]);
        //BtreeInsertNonfull(par->ch[1], par->key[0]);
        par->ch[1]->ch[2] = par->ch[1]->ch[1];
        par->ch[1]->ch[1] = par->ch[1]->ch[0];
        if (ptr->ch[0] != NULL)
            par->ch[1]->ch[0] = ptr->ch[0];
        else if (ptr->ch[1] != NULL)
            par->ch[1]->ch[0] = ptr->ch[1];
        if (par->ch[1]->ch[0] != NULL)
            par->ch[1]->ch[0]->p = par->ch[1];
        removeFromNode(par, par->key[0]);
        free(par->ch[0]);
        par->ch[0] = NULL;
    } else if (par->ch[1] == ptr) {
        BtreeInsertNonfull_extra(par->ch[0], par->key[0]);
        //BtreeInsertNonfull(par->ch[0], par->key[0]);
        if (ptr->ch[0] != NULL)
            par->ch[0]->ch[2] = ptr->ch[0];
        else if (ptr->ch[1] != NULL)
            par->ch[0]->ch[2] = ptr->ch[1];
        if (par->ch[0]->ch[2] != NULL)
            par->ch[0]->ch[2]->p = par->ch[0];
        removeFromNode(par, par->key[0]);
        free(par->ch[1]);
        par->ch[1] = NULL;
    }
    if (par->p == NULL) {
        Node *tmp = NULL;
        if (par->ch[0] != NULL)
            tmp = par->ch[0];
        else
            tmp = par->ch[1];
        tmp->p = NULL;
        free(par);
        return tmp;
    }
    return par;
}

Node *Fix(Node *ptr) {
    if (ptr->n == 0 && ptr->p == NULL) {
        free(ptr);
        return NULL;
    }
    if (ptr->n != 0) {
        if (ptr->p)
            return Fix(ptr->p);
        else
            return ptr;
    }
    Node *par = ptr->p;
    if (par->ch[0]->n == 2 || par->ch[1]->n == 2 || par->n == 2)
        ptr = Redistribute(ptr);
    else if (par->n == 2 && par->ch[2]->n == 2)
        ptr = Redistribute(ptr);
    else
        ptr = Merge(ptr);
    return Fix(ptr);
}

Node *Delete(Node *r, int key) {
    int index;
    Node *ptr = BtreeSearch(r, key, &index);
    if (!ptr)
        return r;
    Node *min = NULL;
    min = BtreeSearchMin(ptr->ch[index + 1]);
    if (min) {
        int z = (key == ptr->key[0] ? ptr->key[0] : ptr->key[1]);
        swap(&z, &min->key[0]);
        ptr = min;
    }
    removeFromNode(ptr, key);
    return Fix(ptr);
}

void Print(Node *ptr, long n) {
    long i;
    if (ptr) {
        if (ptr->n == 2) {
            Print(ptr->ch[2], n+8);
            for (i = 0; i < n; i++)
                printf(" ");
            for (i = 0; i < ptr->n; i++)
                printf("%d ", ptr->key[i]);
            printf("\n");
            Print(ptr->ch[1], n+8);
            Print(ptr->ch[0], n+8);
        }
        else {
            Print(ptr->ch[1], n+8);
            for (i = 0; i < n; i++)
                printf(" ");
            printf("%d ", ptr->key[0]);
            printf("\n");
            Print(ptr->ch[0], n+8);
        }
    }
}

void FreeTree(Tree *tree) {
    if (tree->root->n == 0) {
        free(tree->root);
    }
    else {
        while (tree->root) {
            tree->root = Delete(tree->root, tree->root->key[0]);
        }
    }
}

void Timing(Tree *tree) {
    int key[10000], k, cnt = 1000000, m;
    int index = 0;
    clock_t first, last;
    srand(time(NULL));
    for (int n = 10; n > 0; n--) {
        for (int i = 0; i < 10000; i++) {
            key[i] = rand() * rand();
        }
        for (int i = 0; i < cnt; i++) {
            k = rand() * rand();
            Insert(tree, k, NULL);
        }
        m = 0;
        first = clock();
        for (int i = 0; i < 10000; i++) {
            if (BtreeSearch(tree->root, key[i], &index))
                m++;
        }
        last = clock();
        printf("%d items was found\n", m);
        printf("Test #%d, number of nodes = %d, time = %ld\n", 11 - n, (11 - n) * cnt, 1000 * (last - first) / CLOCKS_PER_SEC);
    }
}

void ReadFromFile(Tree *tree, char *name) {
    int key;
    FILE *fd = fopen(name, "r");
    float f;
    while (fscanf(fd, "%d", &key) != EOF) {
        Data *tmp = calloc(1, sizeof(Data));
        char *str = calloc(10, sizeof(char));
        fscanf(fd, "%s%f", str, &f);
        tmp->f = f;
        tmp->str = str;
        //printf("%d\n", key);
        //printf("INFO IS %f %s\n", tmp->f, tmp->str);
        Insert(tree, key, tmp);
    }
    fclose(fd);
}
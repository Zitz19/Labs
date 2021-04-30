#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "struct.h"
/*
typedef struct Item {
    char data;
    struct Item *prev;
    struct Item *next;
} Item;

typedef struct List {
    Item *head;
    Item *tail;
} List;

List* list_new() {
    List *new_list = (List*) calloc(1, sizeof(List));
    new_list->head = NULL;
    new_list->tail = NULL;
    return new_list;
}

void add_item(List *list, char symbol) {
    Item *ptr = (Item*) calloc(1, sizeof(Item));
    ptr->data = symbol;
    ptr->prev = list->tail;
    ptr->next = NULL;
    if (list->head == NULL) {
        list->head = ptr;
    }
    else {
        list->tail->next = ptr;
    }
    list->tail = ptr;
}

void deleteList(List *list) {
    Item *temp;
    do {
        temp = list->head;
		if (temp == NULL) {break;}
		temp = temp->next;
        free(list->head);
        list->head = temp;
    } while (temp != NULL);
    list->tail = temp;
}

void delete_item(List *list, Item *temp) {
	if (temp == list->head) {
       	if (temp == list->tail) {list->tail = NULL;}
		list->head = temp->next;
		if (list->head != NULL) {list->head->prev = NULL;}
   	}
   	else if (temp == list->tail) {
		list->tail = temp->prev;
		list->tail->next = NULL;
		}
   	else {
		temp->prev->next = temp->next;
		temp->next->prev = temp->prev;
	}
   	free(temp);
}

void putList(List *list) {
    Item *temp = list->head;
    printf("\"");
	if (temp != NULL) {
	    do {
        	printf("%c", temp->data);
        	temp = temp->next;
    	} while (temp != NULL);
	}
    printf("\"\n");
}

void delete_space(List *list) {
	Item *temp;
	Item *extra;
	while ((list->tail) && ((list->tail->data == ' ') || (list->tail->data == '\t'))) {
		delete_item(list, list->tail);
	}
	while ((list->head) && ((list->head->data == ' ') || (list->head->data == '\t')))  {
		delete_item(list, list->head);
	}
	temp = list->head;
	while (temp != NULL) {
		if (temp->data == '\t') {temp->data = ' ';}
		extra = temp->next;
		if (temp->prev != NULL) {
			if ((temp->prev->data == ' ') && (temp->data == ' ')) {
				delete_item(list, temp);
			}
		}
		temp = extra;
	}
}

int checkPalindrome(List *list, Item *start, Item *end) {
	do {
		if (start->data != end->data) {return 0;}
		else {
			start = start->next;
			end = end->prev;
		}
	} while ((start != end) && (start->prev != end));
	return 1;
}

void changeList(List *list) {
	Item *temp;
	Item *local_head;
	Item *local_tail;
	Item *buf;
	Item *extra;
	delete_space(list);
	temp = list->head;
	while (temp != NULL) {
		extra = temp->next;
		if ((temp->prev == NULL) || (temp->prev->data == ' ')) {
			local_head = temp;
		}
		else if ((temp->next == NULL) || (temp->next->data == ' ')) {
			local_tail = temp;
			if (checkPalindrome(list, local_head, local_tail) == 0) {
				do {
					buf = local_head;
					local_head = local_head->next;
					delete_item(list, buf);
				} while(local_head != local_tail);
				delete_item(list, local_head);
				local_head = NULL;
				local_tail = NULL;
			}
		}
		temp = extra;;
	}
	delete_space(list);
}
*/
int main() {
    List *list = list_new();
    int symb;
    do {
        symb = getchar();
        if (symb == EOF) {
            if (ferror(stdin) == 0) {
                printf("End\n");
                break;
            }
            else {
                printf("\nError\n");
                break;
            }
        }
        else if (symb == '\n') {
            putList(list);
		if (list->head != NULL) {changeList(list);}
			putList(list);
			deleteList(list);
        }
        else {
            add_item(list, (char) symb);
        }
    } while (symb != -1);
    deleteList(list);
	free(list);
	return 0;
}

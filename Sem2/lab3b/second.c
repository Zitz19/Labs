и#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "second.h"

KeySpace2* Space2_Create(int size)
{
	return calloc(size, sizeof(KeySpace1));
}

Table* Table2_Create()
{
	Table* table = (Table*)calloc(1, sizeof(Table));
	table->msize1 = 10;
	table->msize2 = 10;
	//table->space1 = Space1_Create(table->msize1);
	table->space2 = Space2_Create(table->msize2);
	return table;
}

unsigned Hash(unsigned key)
{
	return key % 10;
}

Node2** Space2_Search(unsigned key, Table* table, int* size)
{
	KeySpace2* space = table->space2;
	Node2* ptr = space[Hash(key)].node;
	int count = 0;
	Node2** ptrs = NULL;
	while(ptr)
	{
		if(ptr->key == key)
		{
			ptrs = (Node2**)realloc(ptrs, (count + 1) * sizeof(Node2*));
			ptrs[count++] = ptr;
		}
		ptr = ptr->next;
	}
	*size = count;	//0 if no ptrs
	if(!count)
	{
		return NULL;
	}
	return ptrs;
}

int List_Insert(Table* table, unsigned key, Item* item, unsigned release)
{
	KeySpace2* space = table->space2;
	Node2* new = (Node2*)calloc(1, sizeof(Node2));
	if(!new)
	{
		printf("Not anough space.\n");
		return -1;
	}
	new->next = space[Hash(key)].node;
	space[Hash(key)].node = new;
	new->key = key;
	new->item = item;
	item->release = release;
	new->release = release;
	return 0;
}

int Space2_Insert(unsigned key, Item* item, Table* table)
{
	int nothing;
	Node2** prev = Space2_Search(key, table, &nothing);
	if(!prev)
	{
		item->next = NULL;
		if(List_Insert(table, key, item, 0) == -1)
		{
			//printf("Error1\n");
			free(prev);
			return -1;
		}
	}
	else
	{
		item->next = prev[0]->item;
		if(List_Insert(table, key, item, prev[0]->release + 1) == -1)
		{
			//printf("Error2\n");
			free(prev);
			return -1;
		}
	}
	//printf("NO Errors\n");
	free(prev);	
	return 0;
}

void Node2_Remove(Node2* ptr)
{
	Item* item = ptr->item;
	free(item);
}

void Space2_Remove(unsigned key, Table* table)
{
	KeySpace2* space = table->space2;
	unsigned hash = Hash(key);
	Node2* ptr = space[hash].node;
	Node2* prev = NULL;
	while(ptr)
	{
		if(ptr->key == key)
		{
			if(ptr == space[hash].node)
			{
				space[hash].node = ptr->next;
				Node2_Remove(ptr);
				free(ptr);
				ptr = space[hash].node;
			}
			else
			{
				prev->next = ptr->next;
				Node2_Remove(ptr);
				free(ptr);
				ptr = prev->next;
			}
		}
		else
		{
			prev = ptr;
			ptr = ptr->next;
		}
	}
}

void Space2_Print(Table* table)
{
	FILE* file = table->file;
	KeySpace2* space = table->space2;
	Node2* ptr;
	printf("Space2:\n");
	for(int i = 0; i < table->msize2; i++)
	{
		ptr = space[i].node;
		while(ptr)
		{
			
			int num1, num2;
			char* str = (char*)calloc(ptr->item->len + 1, sizeof(char));
			fseek(file, ptr->item->offset, SEEK_SET);
			fread(&num1, sizeof(int), 1, file);
			fread(&num2, sizeof(int), 1, file);
			fread(str, sizeof(char), ptr->item->len, file);

			printf("%d.  key: %u  release: %u  item->relese: %u  info: %d  %d  %s\n", i, ptr->key, ptr->release, ptr->item->release, num1, num2, str);
			free(str);
			ptr = ptr->next;
		}
	}
	printf("\n");
}

void Space2_Erase(Table* table)
{
	KeySpace2* space = table->space2;
	Node2* ptr, *prev;
	for(int i = 0; i < table->msize2; i++)
	{
		ptr = space[i].node;
		while(ptr)
		{
			prev = ptr;
			ptr = ptr->next;
			Node2_Remove(prev);
			free(prev);
		}
		space[i].node = NULL;
	}
}

//Table* Space2_Subtable(unsigned key, Table* table)
//{
//	Table* new = Table2_Create();
///	int size;
//	Node2** ptrs = Space2_Search(key, table, &size);
//	if(!ptrs)
//	{
//		printf("No such items.\n");
//		free(new);
//		return NULL;
//	}
////	int size = (int)(sizeof(ptrs) / sizeof(*ptrs));
////	int size = -1;
////	while(ptrs[++size]);
//	//for(int i = 0; i < size; i++)
//	for(int i = size - 1; i >= 0; i--)
//	{
//		Info* info = (Info*)calloc(1, sizeof(Info));
//		Item* item = (Item*)calloc(1, sizeof(Item));
//		item->info = info;
//		item->release = ptrs[i]->item->release;
//		info->num1 = ptrs[i]->item->info->num1;
//		info->num2 = ptrs[i]->item->info->num2;
//		char* str = (char*)calloc(1 + strlen(ptrs[i]->item->info->str), sizeof(char));
//		strcpy(str, ptrs[i]->item->info->str);
//		info->str = str;
//		Space2_Insert(ptrs[i]->key, item, new);
//	}
//	free(ptrs);
//	return new;
//}

void Space2_Clear(Table* table)
{
	KeySpace2* space = table->space2;
	Node2* ptr1, *ptr2, *prev;
	for(int i = 0; i < table->msize2; i++)
	{
		ptr1 = space[i].node;
		while(ptr1)
		{
			ptr2 = ptr1->next;
			prev = ptr1;
			while(ptr2)
			{
				if(ptr1->key == ptr2->key)
				{
					prev->next = ptr2->next;
					Node2_Remove(ptr2);
					free(ptr2);
					ptr2 = prev->next;			
				}
				else
				{
					prev = ptr2;
					ptr2 = ptr2->next;
				}
			}
			ptr1 = ptr1->next;
		}
	}
}

void Space2_Delete(Table* table)
{
	Space2_Erase(table);
	free(table->space2);
}

int Space2_Release(unsigned key, unsigned release, Table* table)
{
	KeySpace2* space = table->space2;
	int size;
	Node2** ptrs = Space2_Search(key, table, &size);
	if(!ptrs)
	{
		printf("No such item.\n");
		return -1;
	}
	int i;	
	for(i = 0; i < size; i++)
	{
		if(ptrs[i]->release == release)
		{
			if(i)
			{
				ptrs[i - 1]->item->next = ptrs[i]->item->next;
			}
			if(ptrs[i]->item->key1)
			{
				free(ptrs[i]->item->key1);
			}
			free(ptrs[i]->item);
			break;
		}	
	}
	if(i == size)
	{
		printf("No such item.\n");
		return -1;
	}

	Node2* ptr, *prev = NULL;
	unsigned hash = Hash(key);
	ptr = space[hash].node;

	while(ptr)
	{
		if(ptr->key == key && ptr->release == release)
		{
			if(prev)
			{
				prev->next = ptr->next;
			}
			else
			{
				space[hash].node = ptr->next;

			}
			free(ptr);
			break;
		}
		prev = ptr;
		ptr = ptr->next;
	}
	free(ptrs);
	return 0;
}

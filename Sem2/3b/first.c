#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structures.h"
#include "first.h"

KeySpace1* Space1_Create(int size)
{
	return calloc(size, sizeof(KeySpace1));
}

Table* Table1_Create()
{
	Table* table = (Table*)calloc(1, sizeof(Table));
	table->msize1 = 10;
	//table->msize2 = 10;
	table->space1 = Space1_Create(table->msize1);
	//table->space2 = Space2_Create(table->msize2);
	return table;
}

int Space1_Search(char* key, Table* table, int mode)
{
	KeySpace1* space = table->space1;
	if(!mode)
	{
		if(strcmp(key, "NULL") == 0)
		{
			return-2;
		}
		for(int i = 0; i < table->csize1; i++)
		{
			if(!strcmp(key, space[i].key))
			{
				return i;
			}
		}
	}
	else
	{
		for(int i = 0; i < table->csize1; i++)
		{
			if(!strcmp(key, space[i].par))
			{
				return i;
			}
		}
	}
	return -1;
}

int Space1_Insert(char* key, char* par, Item* item, Table* table)
{
	if (table->msize1 == table->csize1)
	{
		printf("Not enough space.\n");
		return -1;
	}
	if(Space1_Search(key, table, 0) != -1)
	{
//		printf("Item with the same key already exists.\n");
		return -1;
	}
	if(Space1_Search(par, table, 0) == -1 && strcmp(par, "NULL"))
	{
		printf("Parent item does not exist.\n");
		return -1;
	}
	if(!strcmp(key, "NULL"))
	{
		printf("Incorect key.\n");
		return -1;
	}
	KeySpace1* space = table->space1;
	{
		space[table->csize1].par = par;
		space[table->csize1].key = key;
		space[table->csize1].item = item;
	}
//	int i = table->csize1 - 1;
//	while(i >= 0 && strcmp(space[i].par, par) > 0)
//	{
//		space[i + 1] = space[i];
//		i--;
//	}
////	strcpy(space[i + 1].key, key);
////	strcpy(space[i + 1].par, par);
//	space[i + 1].par = par;
//	space[i + 1].key = key;
//
//	space[i + 1].item = item;
//
////	space[i + 1].info = (Info*)calloc(1, sizeof(Info));
////	&(space[i + 1].info) = info;
////	space[i + 1].info->num1 = info.num1;
////	space[i + 1].info->num2 = info.num2;
////	space[i + 1].info->str = info.str;
	++table->csize1;
	return 0;
}

int Space1_Remove(char* key, Table* table)
{
	KeySpace1* space = table->space1;
	int index = Space1_Search(key, table, 0);
	if(index == -1)
	{
		printf("No such item in table.\n");
		return -1;
	}
	if(Space1_Search(key, table, 1) != -1)
	{
		printf("Parent item can not be removed.\n");
		return -1;
	}
free(space[index].key);
//free(space[index].par);
	//free(space[index].item->info->str);
	//free(space[index].item->info);
	//free(space[index].item);
	for(int i = index + 1; i < table->csize1; i++)
	{
		space[i - 1] = space[i];
	}
	--table->csize1;
//free(space[table->csize1].key);
//free(space[table->csize1].par);
	space[table->csize1].item = NULL;
	//space[table->csize1].key = NULL;
	//space[table->csize1].par = NULL;	
	return 0;
}

int Space1_Remove1(int index, Table* table)
{
	KeySpace1* space = table->space1;
//	free(space[index].key);
	free(space[index].par);
	for(int i = index + 1; i < table->csize1; i++)
	{
		space[i - 1] = space[i];
	}
	--table->csize1;
	//free(space[table->csize1].key);
	//free(space[table->csize1].par);
	//space[table->csize1].item = NULL;
	return 0;
}

void Space1_Delete(Table* table)
{
	KeySpace1* space = table->space1;
	for(int i = 0; i < table->csize1; i++)
	{	
		free(space[i].item);
	}
	free(space);
}

void Space1_Erase(Table* table)
{
	Space1_Delete(table);
	table->space1 = Space1_Create(table->msize1);
	table->csize1 = 0;
}

void Space1_Print(Table* table)
{
	FILE* file = table->file;
	KeySpace1* space = table->space1;
	printf("\nSpace1:\n");
	for(int i = 0; i < table->csize1; i++)
	{

		int num1, num2;
		char* str = (char*)calloc(space[i].item->len + 1, sizeof(char));
		fseek(file, space[i].item->offset, SEEK_SET);
		fread(&num1, sizeof(int), 1, file);
		fread(&num2, sizeof(int), 1, file);
		fread(str, sizeof(char), space[i].item->len, file);
		
		printf("%d. key: %s  par: %s  item->release: %u  info: %d  %d  %s\n", i, space[i].key, space[i].par, space[i].item->release, num1, num2, str);
		free(str);
	}
	printf("\n");
}


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "structures.h"
#include "first.h"
#include "second.h"
#include "table.h"

Table* Table_Create()
{
	Table* table = (Table*)calloc(1, sizeof(Table));
	table->msize1 = 10;
	table->msize2 = 10;
	table->space1 = Space1_Create(table->msize1);
	table->space2 = Space2_Create(table->msize2);
	return table;
}

int Table_Delete(Table* table)
{
	Space2_Delete(table);
	for(int i = 0; i < table->csize1; i++)
	{
		free(table->space1[i].key);
		free(table->space1[i].par);
	}
	free(table->space1);
	free(table);
	return 0;
}

int Table_Delete1(Table* table)
{
	fclose(table->file);
	Table_Delete1(table);
	remove("info.bin");
	remove("table.bin");
	return 0;
}

char* Get_Str()
{
	char buf[256] = {0}, *res = NULL;
	int len = 0, n = 0;
	do
	{
		n = scanf("%255[^\n]", buf);
		if(n == -1)
		{
			if(!res)
			{
				return NULL;
			}
		}
		else if(n == 1)
		{
			int chunk_len = strlen(buf);
			int str_len = len + chunk_len;
			res = realloc(res, str_len + 1);
			memcpy(res + len, buf, chunk_len);
			len = str_len;
		}
		else
		{
			scanf("%*c");
		}
	}while(n > 0);
	if(len > 0)
	{
		res[len] = '\0';
	}
	else
	{
		res = calloc(1, sizeof(char));
	}
	return res;
}

int Get_Str(char** str)
{
	char* str1;
	do
	{
       		str1 = Get_Str1();
		if(!str1)
		{
			printf("EOF occured.\n");
			return -1;
		}
		if(!strlen(str1))
		{
			free(str1);
			continue;
		}
		break;
	}while(1);
	*str = str1;
	return 0;
}

int Get_Unsigned(unsigned* num)
{
	do
	{
		int check = scanf("%u", num);
		if(check == -1)
		{
			printf("EOF occured.\n");
			return -1;
		}
		if(!check)
		{
			printf("Wrong input, repeat.\n> ");
			scanf("%*s");
			continue;
		}
		break;
	}while(1);
	return 0;
}

int Get_Int(int* num)
{
	int check;
	do
	{
		check = scanf("%d", num);
		if(check == -1)
		{
			printf("EOF occured.\n");
			return -1;
		}
		if(check == 0)
		{
			printf("Wrong input, repeat.\n> ");
			scanf("%*s");
		}
	}while(check == 0);
	return 0;
}

int Table_Insert(char* key1, char* par, unsigned key2, Item* item, Table* table)
{
	if(Space2_Insert(key2, item, table))
	{
		printf("Something went wrong, Space2_Insert.\n");
		return -1;
	}
	if(Space1_Insert(key1, par, item, table))
	{
		printf("Something went wrong, Space1_Insert.\n");
		return -1;
	}
	return 0;
}

int Table_Print(Table* table)
{
	if(!table->csize1)
	{
		printf("Table is empty.\n");
		return 0;
	}
	Space1_Print(table);
	Space2_Print(table);
	return 0;
}

int Table_Remove1(int index, char* key1, unsigned key2, unsigned release, Table* table)
{
	if(Space1_Remove1(index, table))
	{
		free(key1);
		printf("Something went wrong, Space1_Remove.\n");
		return -1;
	}
	if(Space2_Release(key2, release, table))
	{
		free(key1);
		printf("Something went wrong, Space2_Release.\n");
		return -1;
	}
	return 0;
}

int Table_Remove2(unsigned key2, Table* table)
{
	int size;
	Node2** res = Space2_Search(key2, table, &size);
	if(!res)
	{
		printf("No such items.\n");
		return 0;
	}
	for(int i = 0; i < size; i++)
	{
		if(Space1_Search(res[i]->item->key1, table, 1) != -1)
		{
			printf("Parent item can not be removed.\n");
			free(res);
			return 0;
		}
		int index = Space1_Search(res[i]->item->key1, table, 0);
		if(index == -1)
		{
			printf("No such item, but it could be.\n");
			free(res);
			return -1;
		}
		if(Space1_Remove1(index, table))
		{
			free(res);
			printf("Something went wrong, Space1_Remove.\n");
			return -1;
		}
		if(Space2_Release(res[i]->key, res[i]->release, table))
		{
			printf("Something went wrong, Space2_Release.\n");
			free(res);
			return -1;
		}
	}
	free(res);
	return 0;
}

int Table_Load(Table* table)
{
	FILE* file = fopen("table.bin", "r+b");
	if (!file)
	{
		printf("File table.bin not found.\n");
		return 1;
	}
	table->file = fopen("info.bin", "r+b");
	if(!table->file)
	{
		fclose(file);
		printf("File info.bin not found.\n");
		return 1;
	}
	{
		fseek(file, 0, SEEK_SET);
		int size;
		fread(&size, sizeof(int), 1, file);

		for(int i = 0; i < size; ++i)
		{
			int len1, len2, len;
			char *key1, *par;
			long int offset;
			unsigned key2;

			if(!fread(&len1, sizeof(int), 1, file))
			{
				fclose(file);
				printf("Read 0 items, expected more.\n");
				return -1;
			}
			key1 = (char*)calloc(len1 + 1, sizeof(char));
			if(!key1)
			{
				printf("Not enough space.\n");
				fclose(file);
				return -1;
			}
			if(!fread(key1, sizeof(char), len1, file))
			{
				printf("Read 0 items, expected more.\n");
				fclose(file);
				return -1;
			}

			if(!fread(&len2, sizeof(int), 1, file))
			{	
				printf("Read 0 items, expected more.\n");
				fclose(file);
				return -1;
			}
			par = (char*)calloc(len2 + 1, sizeof(char));
			if(!par)
			{
				printf("Not enough space.\n");
				fclose(file);
				free(key1);
				return -1;
			}
			if(!fread(par, sizeof(char), len2, file))
			{	
				free(key1);
				fclose(file);
				printf("Read 0 items, expected more.\n");
				return -1;
			}

			if(!fread(&key2, sizeof(unsigned), 1, file))
			{
				free(par);	
				free(key1);
				fclose(file);
				printf("Read 0 items, expected more.\n");
				return -1;
			}
			if(!fread(&offset, sizeof(long int), 1, file))
			{	
				free(par);	
				free(key1);
				fclose(file);
				printf("Read 0 items, expected more.\n");
				return -1;
			}
			if(!fread(&len, sizeof(int), 1, file))
			{
				free(par);	
				free(key1);
				fclose(file);
				printf("Read 0 items, expected more.\n");
				return -1;
			}
			Item* item = (Item*)calloc(1, sizeof(Item));
			if(!item)
			{
				free(par);	
				free(key1);
				fclose(file);
				printf("Not enough space.\n");
				return -1;
			}
			item->offset = offset;
			item->len = len;
			item->key1 = key1;
			item->key2 = key2;
			if(Table_Insert(key1, par, key2, item, table))
			{
				free(item);
				free(par);	
				free(key1);
				fclose(file);
				printf("Table_Insert fault.\n");
				return -1;
			}
		}
	}
	fclose(file);
	return 0;
}

int Table_Save(Table* table)
{
	FILE* info_file = table->file;
//	fseek(info_file, 0, SEEK_SET);
//	FILE* table_file = fopen("table.bin", "rb");
	FILE* new_table = fopen("new_table.bin", "wb");
	FILE* new_info = fopen("new_info.bin", "wb");
	KeySpace1* space = table->space1;

	fwrite(&(table->csize1), sizeof(int), 1, new_table);
	for(int i = 0; i < table->csize1; i++)
	{
		int num1, num2, len = strlen(space[i].key);
		fwrite(&len, sizeof(int), 1, new_table);
		fwrite(space[i].key, sizeof(char), len, new_table);
		len = strlen(space[i].par);
		fwrite(&len, sizeof(int), 1, new_table);
		fwrite(space[i].par, sizeof(char), len, new_table);
		fwrite(&(space[i].item->key2), sizeof(unsigned), 1, new_table);
		long int offset = ftell(new_info);
		fwrite(&offset, sizeof(long int), 1, new_table);
		fwrite(&(space[i].item->len), sizeof(int), 1, new_table);
		char* str = (char*)calloc(space[i].item->len, sizeof(char));
		fseek(info_file, space[i].item->offset, SEEK_SET);
		fread(&num1, sizeof(int), 1, info_file);
		fread(&num2, sizeof(int), 1, info_file);
		fread(str, sizeof(char), space[i].item->len, info_file);
		fwrite(&num1, sizeof(int), 1, new_info);
		fwrite(&num2, sizeof(int), 1, new_info);
		fwrite(str, sizeof(char), space[i].item->len, new_info);
		free(str);
	}
	fclose(new_table);
	fclose(new_info);	
	Table_Delete(table);
	rename("new_table.bin", "table.bin");
	rename("new_info.bin", "info.bin");
	return 0;
}

#ifndef TABLE
#define TABLE

#define LENGTH 10

typedef struct Item
{
	long int offset;
	int len;

	unsigned release;
	struct Item* next;	// next from KeySpace2 by release
	unsigned key2;
	char* key1;
}Item;

typedef struct KeySpace1
{
	char* key;
	char* par;	
	struct Item* item;
}KeySpace1;

typedef struct Node2
{
	unsigned key;
	unsigned release;
	struct Item* item;
	struct Node2* next;
}Node2;

typedef struct KeySpace2
{
	struct Node2* node;
}KeySpace2;

typedef struct Table
{
	struct KeySpace1* space1;
	struct KeySpace2* space2;

	int msize1;		//size of the space
	int msize2;

	int csize1;		//size of taken space
	FILE* file;
}Table;

#endif

#ifndef FIRST_SPACE
#define FIRST_SPACE

struct KeySpace1* Space1_Create(int);

int Space1_Search(char*, struct Table*, int);

int Space1_Insert(char*, char*, struct Item*, struct Table*);

int Space1_Remove(char*, struct Table*);

int Space1_Remove1(int, struct Table*);

void Space1_Delete(struct Table*);

void Space1_Erase(struct Table*);

void Space1_Print(struct Table*);

struct Table* Space1_Subtable(char*, struct Table*);

#endif

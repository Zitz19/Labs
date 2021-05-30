#ifndef SECOND_SPACE
#define SECOND_SPACE

struct KeySpace2* Space2_Create(int);

unsigned Hash(unsigned);

struct Node2** Space2_Search(unsigned, struct Table*, int*);

int Space2_Insert(unsigned, struct Item*, struct Table*);

void Space2_Remove(unsigned, struct Table*);

void Space2_Print(struct Table*);

void Space2_Erase(struct Table*);

struct Table* Space2_Subtable(unsigned, struct Table*);

void Space2_Clear(struct Table*);

void Space2_Delete(struct Table*);

int Space2_Release(unsigned, unsigned, struct Table*);

#endif

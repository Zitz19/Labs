#ifndef TABLE_FUNCTIONS
#define TABLE_FUNCTIONS

struct Table* Table_Create();

int Table_Delete(struct Table*);

int Get_Str(char**);

int Get_Unsigned(unsigned*);

int Get_Int(int*);

int Table_Insert(char*, char*, unsigned, Item*, struct Table*);

int Table_Print(struct Table*);

int Table_Remove1(int, char*, unsigned, unsigned, struct Table*);

int Table_Remove2(unsigned, struct Table*);

int Table_Save(struct Table*);

int Table_Load(struct Table*);

#endif

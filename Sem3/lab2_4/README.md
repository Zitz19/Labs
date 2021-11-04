# Printed Circuit Board
> In this repository you can find a library for work with PCB, also you can try to do it using application program, sources of which is *./src/main.cpp* file.

## Description of class

> This is a variant of class with dynamic allocation of memory.

### Structure "Contact"

This class includes structure of contact, which is described with following data:
* *contactType **type*** - it is type of contact, can be *in* or *out*, initially *notStated*;
* *int **x*** - the first coordinate of a contact, can be any integer number, initially is zero;
* *int **y*** - the second coordinate, same as *x*;
* *unsigned short **numberOfContact*** - number of connected contact with this contact, when there are no such contact is **-1** (initially);

Contacts can be connected between itself, but it is possible, only if these contacts aren't connected with another contacts and these contacts are of different types (*in* and *out*);

### State of class

The class is described the following way:
* *const static unsigned short **Quota** - it is a value which defines how arrive of contacts will increase in a case of lack of space
* *unsigned short **maxNumber*** - max possible number of contacts, can be changed if there is no more space for new contacts.
* *Contact **contacts[maxNumber]*** - it is an array of contacts;
* *unsigned short **currentNumber*** - current number of contacts, initially is zero.

### Private Methods

For serviceable work of all public methods of the class there are these private methods:
1. *bool **isCorrectCoordinates** (int x, int y)* - returns true if there are not a contact with such coordinates, false in other situations;
2. *contactType **isCorrectType** (int t)* - checks if the *t* is **1** or **0** and returns a corresponding *contactType*, else calls exception;
3. *bool **isCorrectNumber** (short n)* - returns true if there is a contact with number *n*;
4. *bool **isCorrectConnection** (short c1, short c2)* - checks conditions for connection of two contacts.

### Public Methods

1. *operator **>>*** - you can use this operator for input a contact, it has checks for correct type;
2. *operator **<<*** - this operator can be used to print information as about PCB as about a Contact;
3. *operator **+=*** - this operator adds to PCB a specified contact;
4. ***establishConnect** (short c1, short c2)* - this method connects contacts with numbers *c1* and *c2* if it satisfies needed conditions;
5. *operator --* deletes last added contact;
6. *operator [short c]* allows you get information about contact with specified number;
7. *operator (short c1, short c2)* returns a length of track between two connected contacts;
8. ***groupOfContacts** (unsigned short)* returns a group of contacts with specified type;
9. *getCurrentNumber* just returns current number of contacts;
10. *getMaxNumber* returns max number of contacts.

Also, there are implementations of copying and moving constructor and operator **=**, but it seems like moving constructor is not necessary for this class.

And you should note that numbers of contacts don't define contacts, contacts are defined by coordinates and type, numbers only for your convenience.
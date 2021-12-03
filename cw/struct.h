#ifndef STRUCT_H
#define STRUCT_H

struct record {
    char person[32];
    char street[18];
    short int house;
    short int apt;
    char date[10];
};

typedef struct record2 {
    char person[32*2];
    char street[18*2];
    short int house;
    short int apt;
    char date[10*2];
} Record;

typedef struct node Node;
struct node {
    Record* pdata;
    Node* next;
};

typedef enum SORTTYPE {
	sortDate,
	sortStreet,
	sortDateStreet
} tSortType;

struct dict {
	char c;
	int n;
	char* code;
};

#endif // #ifndef STRUCT_H

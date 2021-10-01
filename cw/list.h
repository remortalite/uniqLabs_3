#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

#include "struct.h"

typedef Node List;

List *addList(List *head, Record *record) {
	List *new_node = calloc(1, sizeof(List));
	new_node->next = head;
	new_node->pdata = record;
	return new_node;
}
#endif

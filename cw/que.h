#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>

#include "struct.h"

typedef Node Qnode;

typedef struct _queue {
	Qnode *head;
	Qnode *tail;
} Que;

int isEmptyQ(Que que) {
	if (que.tail == que.head)
			return 1;
	return 0;
}

Que createQue() {
	Que que;
	que.head = NULL;
	que.tail = que.head;
	return que;
}

Que addQue(Que que, Record* record) {
	Qnode *new_node = calloc(1, sizeof(Qnode));
	new_node->pdata = record;
	// TODO: вынести из функции, используется только однажды
	if (que.head == NULL) {
		que.head = new_node;
		que.tail = new_node;
	} else {
		que.tail->next = new_node;
		que.tail = new_node;
	}
	return que;
}

int sizeQue(Que que) {
	Qnode* p = que.head;
	int size = 0;
	while (p != que.tail && p != NULL) {
		++size;
		p = p->next;
	}
	return size;
}

#endif

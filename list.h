#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h>

#ifndef PRINTNULL
#define PRINTNULL 1
#endif

#ifndef ISCHAR
#define ISCHAR 0
#endif

typedef struct _list_node {
	struct _list_node* next;
	long long int num;
} List;

List *addList(List *head, int num) {
	List *new_node = calloc(1, sizeof(List));
	new_node->next = head;
	new_node->num = num;
	return new_node;
}

void printList(List *head) {
	List *prev = head;
	for (; prev; prev = prev->next)
		printf(ISCHAR ? "%-c -> " : "%-d -> ", prev->num);
	if (PRINTNULL) {
		printf("NULL");
	} else {
		printf("\b\b\b   ");
	}
	printf("\n");
		
}

List *fillDecL(List *head, int N) {
	int i;
	for (i = 0; i < N; i++) {
		head = addList(head, i+1);
	}
	return head;
}

List *fillIncL(List *head, int N) {
	int i;
	for (i = 0; i < N; i++) {
		head = addList(head, N-i);
	}
	return head;
}

List *fillRandL(List *head, int N) {
	int i;
	for (i = 0; i < N; i++) {
		head = addList(head, rand() % (N*2));
	}
	return head;
}

void checkSumL(List *head) {
	List *prev = head;
	int checkSum = 0;
	for (; prev; prev = prev->next)
			checkSum += prev->num;
	printf("CheckSum: %d\n", checkSum);
}

void runNumberL(List *head) {
	int runnumbers = 1;
	List *prev = head;
	for (; prev && prev->next; prev = prev->next)
		if (prev->next->num < prev->num)
				runnumbers++;
	if (head == NULL) runnumbers = 0;
	printf("RunNumber: %d\n", runnumbers);
}

#endif

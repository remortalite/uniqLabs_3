#ifndef MERGE_SORT
#define MERGE_SORT

#include "list.h"
#include "que.h"

#include <stdio.h>
#include <stdlib.h>

int isStreetLessEq(Record* a, Record* b) {
	for (int i = 0; i < 18*2; ++i) {
		if (a->street[i] > b->street[i])
			return 0;
		if (a->street[i] < b->street[i])
			return 1;
	}
	return 2;
}

int isDateLessEq(Record* a, Record* b) {
	for (int i = 2; i >= 0; --i) {
		if (a->date[i*3] > b->date[i*3])
			return 0;
		if (a->date[i*3] < b->date[i*3])
			return 1;
		if (a->date[i*3+1] > b->date[i*3+1])
			return 0;
		if (a->date[i*3+1] < b->date[i*3+1])
			return 1;
	}
	return 2;
}

int isDateStreetLessEq(Record* a, Record* b) {
	int answer;
	answer = isDateLessEq(a, b);
	if (answer == 2)
    	answer = isStreetLessEq(a, b);
	return answer;
}

void fromLtoQ(List **list, Que *que) {
	if ((*que).head == NULL) {
		addQue(*que, NULL);
		(*que).head = *list; 
		(*que).tail = (*que).head; 
	} else {
		(*que).tail->next = *list; 
		(*que).tail = *list; 
	}
	(*list) = (*list)->next; 
}

void mergeSeries(List **a, int q, List **b, int r, Que *c, int (*funcComp)(Record*, Record*)) {
	while (q != 0 && r != 0) {
		if (funcComp((*a)->pdata, (*b)->pdata)) {
			fromLtoQ(a, c);
			q--;
		} else {
			fromLtoQ(b, c);
			r--;
		}
	}
	while (q > 0) {
		fromLtoQ(a, c);
		q--;
	}
	while (r > 0) {
		fromLtoQ(b, c);
		r--;
	}
}

void splitList(List **S, List **a, List **b, int N) {
	*a = *S;
	*b = (*S)->next;
	int n = 0;
	List *k = *a; 
	List *p = *b;

	while (p != NULL) {
		n++;
		k->next = p->next;
		k = p; 
		p = p->next;
	}
}

void mergeSort(List **S, int N, tSortType sortType) {
	int i, m, q, r;

	int p;
	List *a, *b;
	Que c0, c1;
	
	splitList(S, &a, &b, N);

	p = 1;
	while (p < N) {
		c0 = createQue();
		c1 = createQue();

		i = 0; m = N;
		while (m > 0) {
			q = (m >= p) ? p : m; 
			m = m - q;
			r = (m >= p) ? p : m;
			m = m - r;
			
			mergeSeries(&a, q, &b, r, i ? &c1 : &c0, 
					sortType == sortDate ? isDateLessEq : 
						sortType == sortStreet ? isStreetLessEq :
							isDateStreetLessEq);
			i = 1 - i;
		}
		a = c0.head; 
		b = c1.head;
		p = 2*p;
	}
	c0.tail->next = NULL;
	*S = c0.head; 
}

#endif

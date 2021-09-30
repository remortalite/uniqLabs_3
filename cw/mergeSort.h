#ifndef MERGE_SORT
#define MERGE_SORT

#include "list.h"
#include "que.h"

#include <stdio.h>
#include <stdlib.h>

int isStreetLessEq(Record a, Record b) {
	for (int i = 0; i < 18*2; ++i) {
		if (a.street[i] > b.street[i])
			return 0;
		if (a.street[i] < b.street[i])
			return 1;
	}
	return 1;
}

int fromLtoQ(List **list, Que *que) {
	int CM = 0;
	if ((*que).head == NULL) {
		Record rec0 = {0};
		addQue(*que, rec0);
		(*que).head = *list; 
		(*que).tail = (*que).head; 
	} else {
		(*que).tail->next = *list; 
		(*que).tail = *list; 
	}
	(*list) = (*list)->next; 
	return CM;
}

int mergeSeries(List **a, int q, List **b, int r, Que *c) {
	int CM = 0;
	while (q != 0 && r != 0) {
		CM++;
		if (isStreetLessEq((*a)->data, (*b)->data)) {
			fromLtoQ(a, c); CM++; CM++;
			q--;
		} else {
			fromLtoQ(b, c); CM++; CM++;
			r--;
		}
	}
	while (q > 0) {
		CM += fromLtoQ(a, c);
		q--;
	}
	while (r > 0) {
		CM += fromLtoQ(b, c);
		r--;
	}
	return CM;
}

int splitList(List **S, List **a, List **b, int N) {
	int CM = 0;

	*a = *S; CM++;
	*b = (*S)->next; CM++;
	int n = 0;
	List *k = *a; 
	List *p = *b;

	while (p != NULL) {
		n++;
		k->next = p->next; CM++;
		k = p; 
		p = p->next; CM++;
	}
	return CM;
}

int mergeSort(List **S, int N) {
	int CM = 0;
	int i, m, q, r;

	int p;
	List *a, *b;
	Que c0, c1;
	
	CM += splitList(S, &a, &b, N);

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
			
			CM += mergeSeries(&a, q, &b, r, i ? &c1 : &c0);
			i = 1 - i;
		}
		a = c0.head; 
		b = c1.head;
		p = 2*p;
	}
	c0.tail->next = NULL;
	*S = c0.head; 
	return CM;
}

#endif

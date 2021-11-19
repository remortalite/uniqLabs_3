#ifndef SEARCH_H
#define SEARCH_H

#include "struct.h"
#include "que.h"

#include <stdio.h>

int getYear(Record* rec) {
	if (rec && rec->date) {
		return (rec->date[6]-'0')*10+(rec->date[7]-'0');
	}
	return 0;
}

Que createQueSort(Que queSort, Que mergedQue, Record** indexArr, int idxStart, int size) {
	Qnode* p;
        p = mergedQue.head;

	for (int i = 0; i < idxStart; ++i)
		p = p->next;
	queSort.head = p;

	int year = getYear(indexArr[idxStart]);
	for (int i = idxStart; i < size; ++i, p = p->next) {
		if (getYear(indexArr[i]) != year) {
			queSort.tail = p;
			break;
		}
	}
	return queSort;
}

Que search(Que mergedQue, Record** indexArr, int size, int year) {
	Que que = createQue();
	int L = 0, R = size-1, m;
	while (L < R) {
		m = (L+R)/2;
		if (getYear(indexArr[m]) < year)
			L = m+1;
		else
			R = m;
	}
	if (getYear(indexArr[R]) == year) {
		printf("Найден:\n");
		Record* record = indexArr[R];
		que = createQueSort(que, mergedQue, indexArr, R, size);
	} else {
		printf("Не найден.\n");
	}
	return que;
}

#endif

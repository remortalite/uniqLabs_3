#include "struct.h"
#include "que.h"

#include <stdio.h>

int getYear(Record* rec) {
	if (rec && rec->date) {
		return (rec->date[6]-'0')*10+(rec->date[7]-'0');
	}
	return 0;
}

Que createQueSort(Que queSort, Record** indexArr, int idxStart, int size) {
	int year = getYear(indexArr[idxStart]);
	for (int i = idxStart; i < size; ++i) {
		if (getYear(indexArr[i]) != year)
			break;
		queSort = addQue(queSort, indexArr[i]);
	}
	return queSort;
}

Que search(Record** indexArr, int size, int year) {
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
		printf("%-32s %-18s %-6d %-6d %-10s\n",
                    record->person,
                    record->street,
                    record->house,
                    record->apt,
                    record->date
                    );

		que = createQueSort(que, indexArr, R, size);
	} else {
		printf("Не найден.\n");
	}
	return que;
}


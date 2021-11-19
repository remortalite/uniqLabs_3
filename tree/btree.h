#ifndef BTREE_H
#define BTREE_H

#ifndef M
#define M 2
#endif

#define YES 1
#define NO 0

typedef struct Page* pPage;

typedef struct Item {
	int data;
	pPage p;
} Item;

struct Page {
	int k;
	pPage p0;
	Item e[2*M];
};

Item* findBtree(int data, pPage a) {
	if (a == NULL) {
		return;
	} else {
		int L, R, i;
		L = 1;
		R = a.k + 1;
		while (L < R) {
			i = (L + R) / 2;
			if (a->e[i].data < data) L = i + 1;
			else R = i;
		}
		R = R - 1;
		Item* answer = NULL;
		if (R > 0 && a->e[R].data == data)
			answer = (a->e)+R;
		else {
			if (R == 0)
				answer = findBtree(data, a->p0);
			else
				answer = findBtree(data, a->e[R].p);
		}
		return answer;
	}
}

void addBtree(int data, pPage a, int rost, Item V) {
	if (a == NULL) {
		V.data = data;
		V.p = NULL;
		rost = YES;
	} else {
		
	}
}

#endif // #ifndef BTREE_H

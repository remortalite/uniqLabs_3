#ifndef BTREE_H
#define BTREE_H

#include "search.h"

#define YES 1
#define NO 0

typedef struct tree* pTree;
struct tree {
	pTree left;
	pTree right;
	pTree next;
	Record* pdata;
	int bal;
};

int getApt(Record* rec) {
	int apt = rec->apt;
	return apt;
}

pTree addDBtree(Record* pdata, pTree p) {
	int VR = YES;
	int HR = YES;
	pTree q;

	if (p == NULL) {
		p = calloc(1, sizeof(struct tree));
		p->pdata = pdata;
		p->left = NULL; p->right = NULL; p->next = NULL;
		p->bal = 0;
		VR = YES;
	}
	else {
		if (getApt(p->pdata) > getApt(pdata)) {
			p->left = addDBtree(pdata, p->left);
			if (VR == YES) {
				if (p->bal == 0) {
					q = p->left;
					p->left = q->right;
					q->right = p;
					p = q;
					q->bal = 1;
					VR = NO;
					HR = YES;			
				}
				else {
					p->bal = 0;
					HR = YES;
				}
			}
			else
				HR = NO;
		}
		else {
			if (getApt(p->pdata) < getApt(pdata)) {
				p->right = addDBtree(pdata, p->right);
				if (VR == YES) {
					p->bal = 1;
					VR = NO;
					HR = YES;
				}
				else {
					if (HR == YES) {
						if (p->bal > 0) {
							q = p->right;
							p->right = q->left;
							p->bal = 0;
							q->bal = 0;
							p->left = p;
							p = q;
							VR = YES; HR = NO;
						}
						else
							HR = NO;
					}
				}
			} else { // if ==
				q = p;
				while (q->next) q = q->next;
				q->next = calloc(1, sizeof(struct tree));
				q = q->next;
				q->pdata = pdata;
				q->left = NULL; q->right = NULL; q->next = NULL;
				p->bal = 0;
			}
		}
	}
	return p;
}

#endif // #ifndef BTREE_H

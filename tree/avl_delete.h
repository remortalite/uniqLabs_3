#ifndef AVL_DELETE_H
#define AVL_DELETE_H

#include "tree.h"
#include "avl.h"

int umen;

pVertex LL1(pVertex p) {
	pVertex q;

	q = p->left;
	if (q->bal == 0) {
		q->bal = 1;
		p->bal = -1;
		umen = NO;
	} else {
		q->bal = 0;
		p->bal = 0;
	}

	p->left = q->right;
	q->right = p;
	p = q;
	return p;
}

pVertex RR1(pVertex p) {
	pVertex q;

	q = p->right;
	if (q->bal == 0) {
		q->bal = -1;
		p->bal = 1;
		umen = NO;
	} else {
		q->bal = 0;
		p->bal = 0;
	}

	p->right = q->left;
	q->left = p;
	p = q;
	return p;
}

pVertex BL(pVertex p) {
	if (p->bal == -1)
		p->bal = 0;
	else {
		if (p->bal == 0) {
			p->bal = 1;
			umen = NO;
		} else {
			if (p->bal == 1) {
				if (p->right->bal >= 0)
					p = RR1(p);
				else
					p = RL(p);
			}
		}
	}
	return p;
}

pVertex BR(pVertex p) {
	if (p->bal == 1)
		p->bal = 0;
	else {
		if (p->bal == 0) {
			p->bal = -1;
			umen = NO;
		} else {
			if (p->bal == -1) {
				if (p->left->bal <= 0)
					p = LL1(p);
				else
					p = LR(p);
			}
		}
	}
	return p;
}

pVertex del(pVertex* q, pVertex r) {
	if (r->right != NULL) {
		r->right = del(q, r->right);
		if (umen == YES)
			r = BR(r);
	} else {
		(*q)->data = r->data;
		*q = r;
		r = r->left;
		umen = YES;
	}
	return r;
}

pVertex deleteAVL(int x, pVertex p) {
	pVertex q;
	if (p == NULL) {}
	else {
		if (x < p->data) {
			p->left = deleteAVL(x, p->left);
			if (umen == YES)
				p = BL(p);
		} else {
			if (x > p->data) {
				p->right = deleteAVL(x, p->right);
				if (umen == YES)
					p = BR(p);
			}
			else {
				q = p;
				if (q->left == NULL) {
					p = q->right;
					umen = YES;
				} else {
					if (q->right == NULL) {
						p = q->left;
						umen = YES;
					} else {
						q->left = del(&q, q->left);
						if (umen == YES)
							p = BL(p);
					}
				}
				free(q);
			}
		}
	}
	return p;
}


#endif // #ifndef AVL_DELETE_H

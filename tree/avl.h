#include "tree.h"

#define YES 1
#define NO 0

pVertex LL(pVertex p) {
	pVertex q;
	q = p->left;
	p->bal = 0;
	q->bal = 0;
	p->left = q->right;
	q->right = p;
	p = q;
	return p;
}

pVertex LR(pVertex p) {
	pVertex q, r;

	q = p->left;
	r = q->right;

	if (r->bal < 0)
		p->bal = 1;
	else
		p->bal = 0;

	if (r->bal > 0)
		q->bal = -1;
	else
		q->bal = 0;

	r->bal = 0;
	q->right = r->left;
	p->left = r->right;
	r->left = q;
	r->right = p;
	p = r;
	return p;
}

pVertex RR(pVertex p) {
	pVertex q;

	q = p->right;
	p->bal = 0;
	q->bal = 0;
	p->right = q->left;
	q->left = p;
	p = q;
	return p;
}

pVertex RL(pVertex p) {
	pVertex q, r;

	q = p->right;
	r = q->left;

	if (r->bal > 0)
		p->bal = -1;
	else
		p->bal = 0;

	if (r->bal < 0)
		q->bal = 1;
	else
		q->bal = 0;

	r->bal = 0;
	p->right = r->left;
	q->left = r->right;
	r->left = p;
	r->right = q;
	p = r;
	return p;
}

int rost;

pVertex addAVL(int data, pVertex p) {
	if (p == NULL) {
		p = createVertex(data);
		p->bal = 0;
		rost = YES;
	}
	else {
		if (p->data > data) {
			p->left = addAVL(data, p->left);
			if (rost == YES) {
				if (p->bal > 0) {
					p->bal = 0;
					rost = NO;
				}
				else {
					if (p->bal == 0) {
						p->bal = -1;
						rost = YES;
					} else {
						if (p->left->bal < 0) {
							p = LL(p);
							rost = NO;
						}
						else {
							p = LR(p);
							rost = NO;
						}
					}
				}
			}
		}
		else {
			if (p->data < data) {
				p->right = addAVL(data, p->right);
				if (rost == YES) {
					if (p->bal < 0) {
						p->bal = 0;
						rost = NO;
					}
					else {
						if (p->bal == 0) {
							p->bal = 1;
							rost = YES;
						} else {
							if (p->right->bal > 0) {
								p = RR(p);
								rost = NO;
							}
							else {
								p = RL(p);
								rost = NO;
							}
						}
					}
				}
			}
			else {
			}
		}
	}
	return p;
}

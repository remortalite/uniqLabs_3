#ifndef BTREE_H
#define BTREE_H

#define YES 1
#define NO 0

pVertex addDBtree(int data, pVertex p) {
	int VR = YES;
	int HR = YES;
	pVertex q;

	if (p == NULL) {
		p = createVertex(data);
		p->bal = 0;
		VR = YES;
	}
	else {
		if (p->data > data) {
			p->left = addDBtree(data, p->left);
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
			if (p->data < data) {
				p->right = addDBtree(data, p->right);
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
			}
		}
	}
	return p;
}

#endif // #ifndef BTREE_H

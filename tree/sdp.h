pVertex SDPrec(int data, pVertex p) {
        if (p == NULL) {
                p = calloc(sizeof(tVertex), 1);
                p->data = data;
                p->left = NULL; p->right = NULL;
        } else {
                if (data < p->data)
                        p->left = SDPrec(data, p->left);
                else {
                        if (data > p->data)
                                p->right = SDPrec(data, p->right);
                        else {
                                //printf("Exists\n");;
                        }
                }
        }
        return p;
}


struct node {
        struct node *left;
        struct node *right;
        int i, j;
};

struct node* alloc(void);

void dealloc(struct node*);


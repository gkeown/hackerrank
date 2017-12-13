/* TREE FUNCTIONALITY */
typedef struct TNode {
    int data;
    struct TNode *left;
    struct TNode *right;
} TNode;

TNode * new_node(int data);
int height(TNode *node);

/* depth first */
void print_inorder(TNode *node);
void print_preorder(TNode *node);
void print_postorder(TNode *node);

/* breadth first */
void print_levels(TNode *node);

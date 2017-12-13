/* STACK FUNCTIONALITY */
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

StackNode * create_new_node(int data);
void push(StackNode **root, int data);
int pop(StackNode **root);
int peek(StackNode *root);

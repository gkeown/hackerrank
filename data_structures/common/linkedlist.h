/* LINKED LIST FUNCTIONALITY */
typedef struct Node {
    int data;
    struct Node *next;
} Node;

void insert_elem(Node **headRef, int data, int pos);
void remove_elem(Node **headRef, int pos);
void printlist(Node *head);

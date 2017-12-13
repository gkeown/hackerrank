#include <stdlib.h>
#include <stdio.h>
#include "../common/tree.h"

#define MAX_Q_SIZE 500

TNode *
new_node(int data)
{
    TNode *node = (TNode *) malloc(sizeof(TNode));
    node->left = NULL;
    node->right = NULL;
    node->data = data;
    return (node);
}

void
print_inorder(TNode *node)
{
    if (node == NULL) {
        return;
    }

    print_inorder(node->left);
    printf("%d ", node->data);
    print_inorder(node->right);
}

void
print_preorder(TNode *node)
{
    if (node == NULL) {
        return;
    }

    printf("%d ", node->data);
    print_preorder(node->left);
    print_preorder(node->right);
}

void
print_postorder(TNode *node)
{
    if (node == NULL) {
        return;
    }

    print_postorder(node->left);
    print_postorder(node->right);
    printf("%d ", node->data);
}

int
height(TNode *node)
{
    if (node == NULL) {
        return (0);
    }

    int lheight = height(node->left);
    int rheight = height(node->right);

    if (lheight > rheight) {
        return (lheight+1);
    } else {
        return (rheight+1);
    }
}

void
print_given_level(TNode *node, int level)
{
    if (node == NULL) {
        return;
    } else if (level == 1) {
        printf("%d ", node->data);
    } else {
        /* print lowest level first */
        print_given_level(node->left, level-1);
        print_given_level(node->right, level-1);
    }
}

void
print_levels(TNode *node)
{
    int i = 1;
    int levels = height(node);
    while (i <= levels) {
        print_given_level(node, i);
        i++;
    }
}

/* UTILITY FUNCTIONS */
TNode **
createQueue(int *front, int *rear)
{
    TNode **queue = (TNode **) malloc(sizeof(TNode *) * MAX_Q_SIZE);
    *front = *rear = 0;
    return (queue);
}

void
enQueue(TNode **queue, int *rear, TNode *new_node)
{
    queue[*rear] = new_node;
    (*rear)++;
}

TNode *
deQueue(TNode **queue, int *front)
{
    (*front)++;
    return queue[*front - 1];
}

void
print_levels_queue(TNode *node)
{
    /* create a queue to store tree nodes */
    int front, rear;
    TNode **queue = createQueue(&front, &rear);

    while (node) {
        
        /* print current node's value first */
        printf("%d ", node->data);

        /* enqueue its children */
        enQueue(queue, &rear, node->left);
        enQueue(queue, &rear, node->right);

        /* dequeue the next node to be processed */
        node = deQueue(queue, &front);
    }
    return;
}

void
test_binary_tree(void)
{
    TNode *root = new_node(1);;
    root->left = new_node(2);
    root->right = new_node(3);
    root->left->left = new_node(4);
    root->left->right = new_node(5); 

    /* depth first */
    printf("print pre-order depth first: ");
    print_preorder(root);
    printf("\n");
    printf("print in-order depth first: ");
    print_inorder(root);
    printf("\n");
    printf("print post-order depth first: ");
    print_postorder(root);
    printf("\n");

    /* breadth first */
    printf("print breadth first: ");
    print_levels(root);
    printf("\n");

    /* print breadth first using queue rather than recursion */
    printf("print breadth first using queue: ");
    print_levels_queue(root);
    printf("\n");

    /* height of tree */
    printf("height of tree = %d\n", height(root));
}

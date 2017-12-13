#include <stdlib.h>
#include <stdio.h>

typedef struct TNode {
    int data;
    struct TNode *left;
    struct TNode *right;
} TNode;

int height(TNode *node);
TNode * new_node(int data);
void print_levels(TNode *node);

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

int
main(int argc, char *argv[])
{
    TNode *root = new_node(1);;
    root->left = new_node(2);
    root->right = new_node(3);
    root->left->left = new_node(4);
    root->left->right = new_node(5); 

    /* depth first */
    print_preorder(root);
    printf("\n");
    print_inorder(root);
    printf("\n");
    print_postorder(root);
    printf("\n");

    /* breadth first */
    printf("print breadth first: ");
    print_levels(root);
    printf("\n");

    /* height of tree */
    printf("height of tree = %d\n", height(root));
    
    return (0);
}

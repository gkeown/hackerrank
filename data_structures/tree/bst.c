#include <stdio.h>
#include <stdlib.h>
#include "../common/tree.h"

TNode *
search(TNode *node, int value) {
    TNode *result = NULL;

    if (node == NULL) {
        return (NULL);
    }

    if (node->data == value) {
        result = node;
    } else if (node->data > value) {
        result = search(node->left, value);
    } else {
        result = search(node->right, value);
    }

    return (result);
}

TNode *
insert(TNode *node, int value) {

    /* insert here */
    if (node == NULL) {
        return (new_node(value));
    }

    if (value < node->data) {
        /* set left node to value if at relevant leaf */
        node->left = insert(node->left, value);
    } else {
        /* set right node to value if at relevant leaf */
        node->right = insert(node->right, value);
    }

    return (node);
}

TNode *
find_smallest_value(TNode *root)
{
    if (root == NULL) {
        return (NULL);
    }

    /* traverse the left side of the tree until no more left leaves */
    if (root->left != NULL) {
        root = find_smallest_value(root->left);
    }

    return (root);
}

/* returns the new root */
TNode *
delete(TNode *root, int value)
{

    /* at leaf or empty tree */
    if (root == NULL) {
        return (NULL);
    }
 
	if (value < root->data) {
		/* value is in left branch */
		root->left = delete(root->left, value);
	} else if (value > root->data) {
		/* value is in right branch */
		root->right = delete(root->right, value);
	} else if (root->data == value) {

        TNode *tmp = NULL;

        /* found the node to delete, check if it has any children */
        if ((root->left == NULL)) {
            /* node has one or zero children */
            tmp = root->right;
            free(root);
            /* may be NULL */
            return (tmp);
        } else if (root->right == NULL) {
            /* node has one or zero children */
            tmp = root->left;
            free(root);
            /* may be NULL */
            return (tmp);
        }

        /* otherwise the node has 2 children - the new parent should be the next largest value (smallest in right branch) */
        tmp = find_smallest_value(root->right);

        /* copy this value to the current node */
        root->data = tmp->data;

        /* delete the node that formerly hosted this value */
        root->right = delete(tmp, tmp->data);

        /* delete the node that formerly hosted this value by cycling through the left side of the tree */
        // root->right = delete(root->right, tmp->data);
    }

    return (root);
}

void
test_bst(void)
{
    // create a BST
    TNode *root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Tree:\n");
    print_levels(root);

    root = delete(root, 20);
    printf("Tree after deletion:\n");
    print_levels(root);

    root = delete(root, 30);
    printf("Tree after deletion:\n");
    print_levels(root);

    root = delete(root, 50);
    printf("Tree after deletion:\n");
    print_levels(root);
}

#include <stdio.h>
#include <stdlib.h>
#include "../common/tree.h"
#include <limits.h>

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

TNode *
find_largest_value(TNode *root) {

    if (root == NULL) {
        return (NULL);
    }

    /* traverse the right side of the tree until no more left leaves */
    if (root->right != NULL) {
        root = find_largest_value(root->right);
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
find_before_after_value(TNode *root, int value, TNode **pre, TNode **suc)
{

    /* past leaf */
    if (root == NULL) {
        return;
    }

    if (root->data == value) {
        /* find the predecessor - largest node in the left branch */
        if (root->left) {
            *pre = find_largest_value(root->left);
        }

        /* find the successor - smallest node in the right branch */
        if (root->right) {
            *suc = find_smallest_value(root->right);
        }
        return;
    }

    if (value < root->data) {
        /* root is the successor */
        *suc = root;

        /* find the predecessor */
        find_before_after_value(root->left, value, pre, suc);
    } else if (value > root->data) {
        /* root is the predecessor */
        *pre = root;

        /* find the successor */
        find_before_after_value(root->right, value, pre, suc);
    }
}

int
isBSTUtil(TNode* node, int min, int max)
{
	/* an empty tree is BST */
	if (node == NULL) {
		return 1;
	}

    printf("check %d > %d and < %d\n", node->data, min, max);

    /* false if this node violates the min/max constraint */
    if (node->data < min || node->data > max) {
        return 0;
    }

    /* otherwise check the subtrees recursively,
       tightening the min or max constraint */
    return ((isBSTUtil(node->left, min, node->data - 1)) &&  // Allow only distinct values
            (isBSTUtil(node->right, node->data + 1, max)));  // Allow only distinct values
}

int
isBST(TNode *node)
{
	return (isBSTUtil(node, INT_MIN, INT_MAX));
}

/* this is the wrong way to do this */
int
check_is_bst(TNode *root) {

    int is_bst = 1;

    /* empty tree is a BST */
    if (root == NULL) {
        return (1);
    }

    if (root->left != NULL) {
        if (root->data > root->left->data) {
            /* tree is still valid, check the next node */
            is_bst = check_is_bst(root->left);
            if (!is_bst) {
                return (0);
            }
        } else {
            /* not a BST */
            return (0);
        }
    }

    /* only check the right node if the left node is still valid */
    if (root->right != NULL) {
        if (root->data <= root->right->data) {
            /* tree is still valid, check the next node */
            is_bst = check_is_bst(root->right);
            if (!is_bst) {
                return (0);
            }
        } else {
            /* not a BST */
            return (0);
        }
    }

    return (is_bst);
}

TNode *
get_successor(TNode *root, TNode *node)
{
    /* sucessor in node's right branch */
    if (node->right) {
       return (find_smallest_value(node->right)); 
    }

    TNode *succ = NULL;

    /* set succ to current root - this will change if other branches are closer to value */
    while (root != NULL) {
        if (node->data < root->data) {
            /* value is in left branch */
            printf("%d < %d, update successor to root\n", node->data, root->data);
            succ = root;
            root = root->left;
        } else if (node->data >= root->data) {
            /* value is in right branch */
            printf("%d >= %d\n", node->data, root->data);
            root = root->right;
        }
    }

    return (succ);
}

TNode *
lowest_common_ancestor(TNode *root, int value1, int value2)
{
    while (root != NULL) {
        if (value1 < root->data && value2 < root->data) {
            /* value is in left branch */
            root = root->left;
        } else if (value1 > root->data && value2 > root->data) {
            /* value is in right branch */
            root = root->right;
        } else {
            /* values have taken different branches */
            break;
        }
    }

    return (root);
}

TNode *
lowest_common_ancestor_recursive(TNode *root, int value1, int value2)
{
    /* empty tree */
    if (root == NULL) {
        return (NULL);
    }

    if (value1 < root->data && value2 < root->data) {
        return (lowest_common_ancestor_recursive(root->left, value1, value2));
    }

    if (value1 > root->data && value2 > root->data) {
        return (lowest_common_ancestor_recursive(root->right, value1, value2));
    }

    return (root);
}

void
test_bst1(void)
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

/* http://www.geeksforgeeks.org/inorder-predecessor-successor-given-key-bst/ */
void
test_bst2(void)
{
   /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    TNode *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Tree:\n");
    print_levels(root);

	TNode *pre = NULL, *suc = NULL;

    find_before_after_value(root, 50, &pre, &suc);
	printf("50 - pre: %d suc: %d\n", (pre) ? pre->data : -1, (suc) ? suc->data : -1);

    TNode *pre1 = NULL, *suc1 = NULL;

    find_before_after_value(root, 35, &pre1, &suc1);
	printf("35 - pre: %d suc: %d\n", (pre1) ? pre1->data : -1, (suc1) ? suc1->data : -1);
}

/* https://www.geeksforgeeks.org/a-program-to-check-if-a-binary-tree-is-bst-or-not/ */
void
test_bst3(void)
{
   /* Let us create following BST
              50
           /     \
          30      70
         /  \    /  \
       20   40  60   80 */
    TNode *root = NULL;
    root = insert(root, 50);
    insert(root, 30);
    insert(root, 20);
    insert(root, 40);
    insert(root, 70);
    insert(root, 60);
    insert(root, 80);

    printf("Tree:\n");
    print_levels(root);

    int res = isBST(root);
    printf("Tree is %s BST.\n", (res) ? "a" : "not a");
    
    
    /* create a non BST */ 
    TNode *non_bst = new_node(40);
    non_bst->left = new_node(30);
    non_bst->right = new_node(50);
    non_bst->left->left = new_node(20);
    non_bst->left->right = new_node(60);

    printf("Tree:\n");
    print_levels(non_bst);

    res = isBST(non_bst);
    printf("Tree is %s BST.\n", (res) ? "a" : "not a");
}

/* https://www.geeksforgeeks.org/inorder-successor-in-binary-search-tree/ */
void
test_bst4(void)
{
    TNode *root = NULL, *temp;

    //creating the tree given in the above diagram
    root = insert(root, 20);
    root = insert(root, 8);
    root = insert(root, 22);
    root = insert(root, 4);
    root = insert(root, 12);
    root = insert(root, 10);  
    root = insert(root, 14);    
    temp = root->left->right->right; 

    printf("Tree:\n");
    print_levels(root);

    TNode *succ = get_successor(root, temp);
    if (succ) {
        printf("Successor of %d = %d\n", temp->data, succ->data);
    }

    temp = root->left->left;
    succ = get_successor(root, temp);
    if (succ) {
        printf("Successor of %d = %d\n", temp->data, succ->data);
    }
}

/* https://www.geeksforgeeks.org/lowest-common-ancestor-in-a-binary-search-tree/ */
void
test_bst5(void)
{
    // Let us construct the BST shown in the above figure
    TNode *root              = new_node(20);
    root->left               = new_node(8);
    root->right              = new_node(22);
    root->left->left         = new_node(4);
    root->left->right        = new_node(12);
    root->left->right->left  = new_node(10);
    root->left->right->right = new_node(14);

    int n1 = 10, n2 = 14;
    TNode *res = lowest_common_ancestor(root, n1, n2);
    printf("LCA of %d and %d is %d \n", n1, n2, res->data);

    n1 = 14, n2 = 8;
    res = lowest_common_ancestor(root, n1, n2);
    printf("LCA of %d and %d is %d \n", n1, n2, res->data);

    n1 = 10, n2 = 22;
    res = lowest_common_ancestor(root, n1, n2);
    printf("LCA of %d and %d is %d \n", n1, n2, res->data);

    printf("=======================\n");

    /* recursive */
    n1 = 10, n2 = 14;
    res = lowest_common_ancestor_recursive(root, n1, n2);
    printf("LCA of %d and %d is %d \n", n1, n2, res->data);

    n1 = 14, n2 = 8;
    res = lowest_common_ancestor_recursive(root, n1, n2);
    printf("LCA of %d and %d is %d \n", n1, n2, res->data);

    n1 = 10, n2 = 22;
    res = lowest_common_ancestor_recursive(root, n1, n2);
    printf("LCA of %d and %d is %d \n", n1, n2, res->data);
}

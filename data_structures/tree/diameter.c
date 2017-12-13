#include <stdlib.h>
#include <stdio.h>
#include "../common/tree.h"

int
max(int a, int b)
{
	return ((a >= b) ? a : b);
}

int
find_diameter(TNode *node)
{
	int lheight = 0, rheight = 0;
	int current_node_diameter = 0;
	int lower_left_diameter = 0;
	int lower_right_diameter = 0;
	int max_diameter = 0;

	/* reached the end of this branch */
	if (node == NULL) {
		return (0);
	}

	/* calculate diameter of current node */
	lheight = height(node->left);
	rheight = height(node->right);
	current_node_diameter = lheight + rheight + 1; // include current node

	/* find the diameter of the lower branches */
	lower_left_diameter = find_diameter(node->left);
	lower_right_diameter = find_diameter(node->right);
	max_diameter = max(lower_left_diameter, lower_right_diameter);

	/* return the largest diameter found to this point */
	if (current_node_diameter > max_diameter) {
		max_diameter = current_node_diameter;
	}	

	return (max_diameter);
}

void
test_diameter(void)
{
	/*
	 * Constructed binary tree is 
	 *	   	   1
	 *  	 /  \
	 *	    2    3
	 *     /  \   \
	 *    4    5   6
	 *        /
	 *       7
	 */
	TNode *root 	  = new_node(1);
	root->left        = new_node(2);
	root->right       = new_node(3);
	root->left->left  = new_node(4);
	root->left->right = new_node(5);
	root->right->right = new_node(6);
	root->left->right->left = new_node(7);

	printf("diameter of tree is %d\n", find_diameter(root));
}

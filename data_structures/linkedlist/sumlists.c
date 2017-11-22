#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void
push(Node **head, int data) {
    Node *current = (*head);
    Node *new_node = (Node *) malloc(sizeof(Node));
    new_node->data = data;
    new_node->next = NULL;
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    new_node->next = current;
    *head = new_node;
}

void
pop(Node **head) {
	Node *current = (*head);
	
	if (current != NULL) {
		*head = current->next;
		free(current);
	}
}

void
printlist(Node *head) {
    Node *current = head;
    int i = 0;
    while (current != NULL) {
        if (current->next != NULL) {
            printf("%d -> ", current->data);
        } else {
            printf("%d.\n", current->data);   
        }
        current = current->next;
        i++;
    }
    printf("len = %d\n", i);
}

void
swap_list_pos(Node **head, int pos1, int pos2) {
    Node *current = *head;
    Node *node1 = NULL, *prev1 = NULL; // *next1 = NULL;
    Node *node2 = NULL, *prev2 = NULL; // *next2 = NULL;
    
    if (current == NULL) {
        printf("no elements to be found\n");
        return;
    }
    
    int i = 0;
    
    // find first node details
    while (current != NULL && (i != pos1)) {
        // record the previous element;
        prev1 = current;
        current = current->next;
        i++;
    }
    
    if (current == NULL) {
        printf("could not find pos1\n");
        return;
    }
    
    // record the next element
    node1 = current;

    // reset tracking variables
    i = 0;
    current = *head;
    
    // find second node details
    while (current != NULL && (i != pos2)) {
        // record the previous element;
        prev2 = current;
        current = current->next;
        i++;
    }
    
    if (current == NULL) {
        printf("could not find pos2\n");
        return;
    }
    
    // record the next element
    node2 = current;
    
    // update the previous elements if they exist
    if (prev1) {
        prev1->next = node2;
    } else {
        // node1 was previously head node, update head
        *head = node2;
    }
    
    if (prev2) {
        prev2->next = node1;
    } else {
        // node2 was previously the head node, update head
        *head = node1;
    }
    
    Node *tmp; 
    tmp = node1->next;
    node1->next = node2->next;
    node2->next = tmp;

}

void
reverselist(Node **head)
{
	Node *current = *head;
	Node *next = NULL;
	Node *prev = NULL;
	
	while (current != NULL) {
	    
	    // record the next Node
	    next = current->next;
	    
	    // set next to prev
	    current->next = prev;
	    
	    // set prev to current
		prev = current;
		
		// move to the next node
		current = next;
	}
	*head = prev;
}

void
insert_elem(Node **headRef, int data, int pos)
{
    Node *current = *headRef;
    Node *prev = NULL, *new_node = NULL;
    int i = 0;

    new_node = malloc(sizeof(*new_node));
    new_node->data = data;
    new_node->next = NULL;

    /* this is the first element in the list to be added */
    if (current == NULL) {
        *headRef = new_node;
        return;
    }

    /* user inserting element at head */
    if (pos == 0) {
        new_node->next = current;
        *headRef = new_node;
        return;
    }

    /* otherwise insert element at position provided */
    while (current != NULL && i != pos) {
        prev = current;
        current = current->next;
        i++;
    }

    prev->next = new_node;
    new_node->next = current;
}

void
remove_elem(Node **headRef, int pos)
{
    Node *current = *headRef;
    Node *prev = NULL;
    int i = 0;

    /* nothing to be removed */
    if (current == NULL) {
        return;
    }

    /* user requesting that head element is removed */
    if (pos == 0) {
        *headRef = current->next;
        free(current);
        return;
    }

    /* cycle through the list to removed the correct element */
    while (current != NULL && i != pos) {
        prev = current;
        current = current->next;
        i++;
    }

    if (i != pos) {
        printf("element %d does not exist, list len %d\n", pos, i);
        return;
    }

    prev->next = current->next;
    free(current);
}

void
sum_lists(Node *list1, Node *list2, Node **resHeadRef) {
    Node *ptr1 = list1, *ptr2 = list2, *prev = NULL;
    int carry = 0, res = 0;
    int set_head = 0;

    if (list1 == NULL || list2 == NULL) {
        printf("sum_lists: empty list, return\n");
        return;
    }

    /* iterate through lists at same pace */
    while (ptr1 != NULL || ptr2 != NULL || carry != 0) {

        /* create a new node to store the result */
        Node *res_node = (Node *) malloc(sizeof(Node));
        if (!set_head) {
            /* set the head of the resultant list */
            *resHeadRef = res_node; 
            prev = res_node;
            set_head = 1;
        } else {
            prev->next = res_node;
            prev = res_node;
        }

        /* need to consider the carry bit from previous added digits */
        if (ptr1 && ptr2) {
            res = ptr1->data + ptr2->data + carry;
        } else if (ptr1) {
            res = ptr1->data + carry;
        } else if (ptr2) {
            res = ptr2->data + carry;
        } else {
            res = carry;
        }

        /* reset carry bit for next calculation */
        carry = 0;

        /* set carry bit if applicable */
        if (res >= 10) {
            carry = 1;
        }
        res_node->data = res % 10;

        /* move to next element */
        if (ptr1) {
            ptr1 = ptr1->next;
        }

        if (ptr2) {
            ptr2 = ptr2->next;
        }
    }
}

int main() {
	Node *list1 = NULL;
	Node *list2 = NULL;

    insert_elem(&list1, 7, 0);
    insert_elem(&list1, 5, 1);
    insert_elem(&list1, 9, 2);
    insert_elem(&list1, 9, 3);
    insert_elem(&list1, 9, 4);
	printlist(list1);

	insert_elem(&list2, 8, 0);
	insert_elem(&list2, 4, 1);
	printlist(list2);

    Node *result = NULL;
    sum_lists(list1, list2, &result);
    printlist(result);

	return 0;
}

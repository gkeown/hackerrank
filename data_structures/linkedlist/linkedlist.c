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

int main() {
	Node *list1 = NULL;
	Node *list2 = NULL;
	
	push(&list1, 10);
	push(&list1, 20);
	push(&list1, 30);
	push(&list1, 50);
	push(&list1, 25);

	printlist(list1);

	insert_elem(&list2, 15, 0);
	insert_elem(&list2, 25, 1);
	insert_elem(&list2, 35, 2);
	insert_elem(&list2, 35, 99);
	insert_elem(&list2, 55, 1);
	insert_elem(&list2, 95, 0);

	printlist(list2);

    remove_elem(&list2, 0);
    remove_elem(&list2, 1);
    remove_elem(&list2, 3);
    remove_elem(&list2, 6);

	printlist(list2);
	
	return 0;
}

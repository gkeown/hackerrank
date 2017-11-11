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

int main() {
	Node *list1 = NULL;
	Node *list2 = NULL;
	
	push(&list1, 10);
	push(&list1, 20);
	push(&list1, 30);
	push(&list1, 50);
	push(&list1, 25);

	push(&list2, 15);
	push(&list2, 25);
	push(&list2, 35);
	push(&list2, 55);
	push(&list2, 95);
	
    // printlist(head);
    // swap_list_pos(&head, 0, 1);
	// swap_list_pos(&head, 3, 0);
    // printlist(head);
	// pop(&head);
	// pop(&head);
	// reverselist(&head);
	
	printlist(list1);
	printlist(list2);
	
	return 0;
}

/* http://www.geeksforgeeks.org/reverse-a-list-in-groups-of-given-size/ */
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

int
listlen(Node *head, int print) {
    Node *current = head;
    int len = 0;
    while (current != NULL) {
        if (print) {
            if (current->next != NULL) {
                printf("%d -> ", current->data);
            } else {
                printf("%d.\n", current->data);
            }
        }
        current = current->next;
        len++;
    }
    return (len);
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

Node *
reverselistsection(Node *headRef, int k)
{
    Node *current = headRef;
    Node *prev = NULL, *next = NULL;
    int i = 0;

    if (current == NULL) {
        // nothing to modify
        return (headRef);
    }

    // reverse section of the list
    while (current != NULL && i != k) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
        i++;
    }

    // after that section of the list has been reversed, recurively call the next section, the previous
    // head should point to the next part of the list
    if (current) {
        headRef->next = reverselistsection(current, k);
    }

    // last element processed is the new head of this section of the list
    headRef = prev;
    return (headRef);
}

int main() {
	Node *list1 = NULL;
	Node *list2 = NULL;
	
	push(&list1, 50);
	push(&list1, 40);
	push(&list1, 30);
	push(&list1, 20);
	push(&list1, 10);

	push(&list1, 65);
	push(&list1, 55);
	push(&list1, 45);
	push(&list1, 35);
	push(&list1, 15);

	listlen(list1, 1);

    // reverses the list in sections of 4
    list1 = reverselistsection(list1, 4);
    listlen(list1, 1);
}

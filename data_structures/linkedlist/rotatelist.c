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
rotate_list(Node **headRef, int rotate)
{
    Node *head = *headRef;
    Node *current = head;
    Node *prev_tail = NULL, *prev = NULL;

    if (head == NULL || rotate == 0) {
        printf("list is empty\n");
        return;
    }

    while (current != NULL) {
        prev_tail = current;
        current = current->next;
    }

    /* point the previous tail element to the current head element */
    prev_tail->next = head;
    current = head;

    /* rotate through the list to find the new head */
    for (int i = 0; i < rotate; i++) {
        prev = current;
        current = current->next;
    }

    /* prev is the new tail */
    prev->next = NULL;
    *headRef = current;
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

    printf("rotate by 4\n");
    rotate_list(&list1, 4);
    listlen(list1, 1);

    printf("rotate by 1\n");
    rotate_list(&list1, 1);
    listlen(list1, 1);

    printf("rotate by 15\n");
    rotate_list(&list1, 15);
    listlen(list1, 1);
}

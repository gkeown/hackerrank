/* http://www.geeksforgeeks.org/detect-and-remove-loop-in-a-linked-list/ */
#include <stdio.h>	
#include <stdlib.h>
#include <stdbool.h>

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
remove_loop(Node *node_in_loop, Node **headRef)
{
    Node *current = *headRef;
    Node *loop_node = NULL;
    Node *prev = NULL;
    bool first_entry_found = false;

    if (*headRef == NULL || node_in_loop == NULL) {
        printf("remove_loop: NULL failure\n");
        return;
    }

    /* loop through entire list until we find a node equal to first entry in loop */
    while (current != NULL) {
        
        loop_node = node_in_loop;
        if (current == loop_node) {
            printf("loop is one entry pointing to itself\n");
            current->next = NULL;
            break;
        }


        /* record previous entry as it may be causing the loop */
        prev = loop_node;
        loop_node = loop_node->next;

        /* check current node against nodes in the loop */
        while (loop_node != node_in_loop) {

            /* we have found the first node in the loop */
            if (current == loop_node) {
                printf("first entry in the loop is %d\n", current->data);
                first_entry_found = true;
                break;
            }
            prev = loop_node;
            loop_node = loop_node->next;
        }

        if (first_entry_found) {
            printf("found first entry, now remove the pointer that is pointing to it\n");
            break;
        }
        
        current = current->next;
    }

    /* loop through entries until we find the entry pointing at first in loop */
    if (prev) {
        printf("change next pointer of entry %d\n", prev->data);
        prev->next = NULL;
    }
}

bool
detect_and_remove_loop(Node **headRef)
{
    Node *head = *headRef;
    Node *slow = NULL, *fast = NULL;

    /* nothing to do */
    if (head == NULL) {
        return (false);
    }


    slow = head;
    fast = head->next;

    /* if there is a loop present, fast will catch up with slow eventually */
    while (slow && fast && fast->next) {

        if (slow->data == fast->data) {
            remove_loop(slow, headRef);
            return (true);
        }

        fast = fast->next->next;
        slow = slow->next;
    }

    return (false);
}


int main() {
	Node *list1 = NULL;
	Node *list2 = NULL;
	
	push(&list1, 50);
	push(&list1, 40);
	push(&list1, 30);
	push(&list1, 20);
	push(&list1, 10);

    // create a loop for testing
    printf("%d -> %d\n", list1->next->next->next->data, list1->next->data);
    list1->next->next->next->next = list1->next;

    // detect and remove loop
    bool loop_removed = detect_and_remove_loop(&list1);
    if (loop_removed) {
        printf("found and removed loop\n");
        listlen(list1, 1);
    }
}

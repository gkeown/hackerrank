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

Node *
mergelist3(Node *list1, Node *list2)
{
    Node *mergedhead = NULL;
    int list1_size = listlen(list1, 0);
    int list2_size = listlen(list2, 0);

    int size = list1_size + list2_size;
    Node *prev = NULL;
    Node *iter = NULL, *iter2 = NULL;

    // populate a dummy list - first with list1
    iter = list1;
    while (iter != NULL) {
        Node *new_node = (Node *) malloc(sizeof(Node));
        new_node->data = iter->data;
        if (prev == NULL) {
            mergedhead = new_node;
        } else {
            prev->next = new_node;
        } 
        prev = new_node;
        iter = iter->next;
    }

    // then add the elements in list2 to appropriate positions
    iter = list2;
    prev = NULL;
    while (iter != NULL) {
        Node *new_node = (Node *) malloc(sizeof(Node));
        new_node->data = iter->data;

        // compare the new element with those already in the merged list
        iter2 = mergedhead;
        int pos = 0;
        prev = NULL;

        while (iter2 != NULL) {
            if (new_node->data > iter2->data) { 
                prev = iter2;
                iter2 = iter2->next;
            } else {
                break;
            }
            pos++;
        }

        if (pos == 0) {
            // update the head of the list
            mergedhead = new_node;
        } else {
            prev->next = new_node;
        }
        new_node->next = iter2;

        iter = iter->next;
    }

    return (mergedhead);
}

void
splitlist(Node *source, Node **front, Node **back)
{
    Node *slow = NULL;
    Node *fast = NULL;

    if (source == NULL || source->next == NULL) {
        *front = source;
        *back = NULL;
        return;
    }

    /* used to iterate through the list */
    slow = source;
    fast = source->next;

    // find the middle element
    while (fast != NULL) {
        fast = fast->next;

        /* fast skips an element until end of list is reached */
        if (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }
    }

    /* slow->next is the middle element */
    *front = source;
    *back = slow->next;
    slow->next = NULL;
}

Node* mergelist(Node *front, Node* back)
{
	Node* result = NULL;

    // if one of the lists is empty, return the other list
	if (front == NULL) {
		return (back);
	} else if (back == NULL) {
		return (front);
	}

    /* determine next element and then move on recursively */
	if (front->data <= back->data) {
		result = front;
		result->next = mergelist(front->next, back);
	} else {
		result = back;
		result->next = mergelist(front, back->next);
	}

	return (result);
}

void
mergeSort(Node **headRef)
{
    Node *head = *headRef;
    Node *front = NULL;
    Node *back = NULL;

    // already sorted if empty or only 1 in size
    if (head == NULL || head->next == NULL) {
        return;
    }

    // divide and conquer
    splitlist(head, &front, &back);

    // recursively sort the split lists
    mergeSort(&front);
    mergeSort(&back);

    *headRef = mergelist(front, back);
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

    mergeSort(&list1);
    listlen(list1, 1);
}

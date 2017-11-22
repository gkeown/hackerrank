#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    /* data now is a generic pointer */
    void *data;
    struct Node *next;
} Node;

/* data size is provided in bytes */
void
push(Node **head, void *data, int data_size) {
    Node *current = (*head);
    Node *new_node = (Node *) malloc(sizeof(Node));

    /* alloc appropriiate amount of memory for data pointer */
    new_node->data = malloc(data_size);
    new_node->next = NULL;

    /* fill in the data byte by byte */
    for (int i = 0; i < data_size; i++) {
        /* dereference each bytes and assign to new node's dereferenced data pointer */
        *(char *)(new_node->data + i) = *(char *)(data + i);
    }
    
    if (*head == NULL) {
        *head = new_node;
        return;
    }
    
    new_node->next = current;
    *head = new_node;
}


/* provide a function pointer to print list correctly */
void
printlist(Node *head, void (*fptr)(void *)) {
    Node *current = head;
    int i = 0;
    while (current != NULL) {
        /* call function pointer and provide parameter value */
        (*fptr) (current->data);
        current = current->next;
        i++;
    }
    printf("\n");
}

void
printInt(void *value) {
    /* dereference data pointer and cast to int */
    printf("%d ", *(int *) value);
}

void
printFloat(void *value) {
    /* dereference data pointer and cast to float */
    printf("%f ", *(float *) value);
}

int
main()
{
	Node *list1 = NULL;
	Node *list2 = NULL;
	
    /* create int array and print */
    int iarray[5] = {10, 20, 30, 40, 50};
    for (int i = 0; i < 5; i++) {
        push(&list1, &iarray[i], sizeof(int));
    }
	printlist(list1, printInt);

    /* create float array and print */
    float farray[5] = {10.1, 20.2, 30.3};
    for (int i = 0; i < 3; i++) {
        push(&list2, &farray[i], sizeof(float));
    }
	printlist(list2, printFloat);

	return 0;
}

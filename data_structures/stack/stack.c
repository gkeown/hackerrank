#include <stdio.h>
#include <stdlib.h>
#include "../common/stack.h"

int
isEmpty(StackNode *root)
{
    if (root == NULL) {
        return (1);
    }

    return (0);
}

StackNode *
create_new_node(int data)
{
    StackNode *new_node = (StackNode *) malloc(sizeof(StackNode));
    new_node->data = data;
    new_node->next = NULL;
    return (new_node);
}

void
push(StackNode **root, int data)
{
    StackNode *new_node = create_new_node(data);

    /* otherwise new element points to the previous root */
    new_node->next = *root; // this could be NULL
    *root = new_node;

//    printf("pushed %d to stack\n", new_node->data);
}

int
pop(StackNode **root)
{
    int result = 0;
    StackNode *top = *root;

    if (isEmpty(top)) {
        printf("nothing to pop\n");
        return (-1);
    }

    result = top->data;
    *root = top->next;
    free(top);

    return (result);
}

int
peek(StackNode *root)
{
    int result = 0;

    if (root == NULL) {
        printf("Nothing to peek at, stack empty\n");
        return (-1);
    }

    return (root->data);
}

void
reverse(char *string)
{
    StackNode *stack = NULL;
    int i = 0;

    for (i = 0; string[i]; i++) {
        push(&stack, string[i]); 
    }

    i = -1;
    while (!isEmpty(stack)) {
        string[++i] = pop(&stack);
    }

    printf("result = %s\n", string);
}

// int
// main(int argc, char *argv[])
// {
//    StackNode *stack = NULL;

//    push(&stack, 10);
//    push(&stack, 20);
//    push(&stack, 30);

//    printf("top element: %d\n", peek(stack));

//    printf("%d\n", pop(&stack));
//    printf("%d\n", pop(&stack));
//    printf("%d\n", pop(&stack));
//    pop(&stack);

//    char str[] = "test string";
//    printf("Reversing %s\n", str);
//    reverse(str);


//    return (0);
// }

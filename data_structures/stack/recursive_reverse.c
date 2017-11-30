#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

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
reversestring(StackNode **stack, char *string)
{
    int i = 0;

    if (!string[i]) {
        // we are at the end of the string
        printf("End of the string, return\n");
        return;
    }

    /* push the current character to the stack and move onto the next */
    push(stack, string[i]);
    reversestring(stack, &string[i] + 1);

    /* when we get to here, all items have been added to the stack */
    printf("%c", pop(stack));
}

void
insert_at_bottom(StackNode **stack, int item)
{
    if (isEmpty(*stack)) {
        push(stack, item); 
    } else {
        int temp = pop(stack);
        /* push item to the back of the stack, popping all other elements along the way */
        insert_at_bottom(stack, item);
        push(stack, temp);
    }
}

void
reverse(StackNode **stack)
{
    if (isEmpty(*stack)) {
        printf("Reached end of stack\n");
        return;
    }

    /* pop all of the elements off current list */
    int temp = pop(stack);
    reverse(stack);

    /* push temporary element back onto the stack once all of the elements have been popped off in reverse order */
    insert_at_bottom(stack, temp);
}

int
main(int argc, char *argv[])
{
    StackNode *stack = NULL;

    push(&stack, 4);
    push(&stack, 3);
    push(&stack, 2);
    push(&stack, 1);

    StackNode *iter = stack;
    while (iter != NULL) {
        printf("%d ", iter->data);
        iter = iter->next;
    }
    printf("\n");

    reverse(&stack);

    while (!isEmpty(stack)) {
        printf("%d ", pop(&stack));
    }
    printf("\n");

    return (0);
}

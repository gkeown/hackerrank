#include <stdio.h>
#include <stdlib.h>

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct Queue {
    StackNode *stack1;
    StackNode *stack2;
} Queue;

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

void
enqueue(StackNode **stack, int data)
{
    StackNode *new_stack = NULL;

    /* push everything from the stack onto a new stack */
    while (!isEmpty(*stack)) {
        int value = pop(stack);
        push(&new_stack, value);
        printf("remove %d\n", value);
    }

    /* add new element to the original stack */
    push(stack, data);
    printf("add %d\n", data);

    /* re-add elements to original stack */
    while (!isEmpty(new_stack)) {
        int value = pop(&new_stack);
        push(stack, value);
        printf("add %d\n", value);
    }
}

int
dequeue(StackNode **stack)
{
    int res = 0;

    if (isEmpty(*stack)) {
        printf("Stack is empty\n");
        return (-1);
    }

    res = pop(stack);
    return (res);
}

/* the end of the stack is the head of the queue */
void
enqueue2(StackNode **stack, int data)
{
    printf("Adding %d to stack1\n", data);
    push(stack, data);
}

int
dequeue2(StackNode **stack, StackNode **stack2)
{
    StackNode *new_stack = NULL;
    int data = 0;

    if (isEmpty(*stack) && isEmpty(*stack2)) {
        printf("Stack is empty\n");
        return (-1);
    }

    /* pop element from stack 2 if items exist */
    if (!isEmpty(*stack2)) {
        int value = pop(stack2);
        printf("items on stack 2, pop %d\n", value);
        return (value);
    }

    /* otherwise push all element on stack 1 to stack 2 */
    while (!isEmpty(*stack)) {
        int value = pop(stack);
        push(stack2, value);
        printf("move %d to queue 2\n", value);
    }

    data = pop(stack2);
    printf("popped %d\n", data);
    return (data);
}

int
main(int argc, char *argv[])
{
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->stack1 = NULL;
    queue->stack2 = NULL;

//    enqueue(&stack, 10);
//    enqueue(&stack, 20);
//    enqueue(&stack, 30);
//    enqueue(&stack, 40);
//    enqueue(&stack, 50);

//    printf("%d\n", dequeue(&stack));
//    printf("%d\n", dequeue(&stack));
//    printf("%d\n", dequeue(&stack));
//    printf("%d\n", dequeue(&stack));
//    printf("%d\n", dequeue(&stack));

    enqueue2(&queue->stack1, 10);
    enqueue2(&queue->stack1, 20);
    enqueue2(&queue->stack1, 30);
    enqueue2(&queue->stack1, 40);
    enqueue2(&queue->stack1, 50);

    printf("%d\n", dequeue2(&queue->stack1, &queue->stack2));
    printf("%d\n", dequeue2(&queue->stack1, &queue->stack2));
    printf("%d\n", dequeue2(&queue->stack1, &queue->stack2));
    enqueue2(&queue->stack1, 100);
    printf("%d\n", dequeue2(&queue->stack1, &queue->stack2));
    printf("%d\n", dequeue2(&queue->stack1, &queue->stack2));
    printf("%d\n", dequeue2(&queue->stack1, &queue->stack2));

    return (0);
}

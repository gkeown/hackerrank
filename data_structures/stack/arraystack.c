#include <stdio.h>
#include <stdlib.h>

// A structure to represent a stack
typedef struct Stack
{
    int top;
    unsigned capacity;
    int* array;
} Stack;

int
is_stack_full(Stack *stack)
{
    if (stack->top == stack->capacity-1) {
        return (1);
    }
    return (0);
}

int
is_stack_empty(Stack *stack)
{
    if (stack->top == -1) {
        return (1);
    }
    return (0);
}

void
push(Stack *stack, int data)
{
    if (is_stack_full(stack)) {
        printf("stack is full\n");
        return;
    }

    /* increment the number of elements in the stack */
    stack->array[++stack->top] = data;
}

int
pop(Stack *stack)
{
    int head_val = -1;

    if (is_stack_empty(stack)) {
        printf("Nothing to pop\n");
        return (head_val);
    }

    head_val = stack->array[stack->top--];

    return (head_val);
}

int
main(int argc, char *argv[])
{
    /* create a stack of size capacity */
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->capacity = 10;
    stack->array = (int *) malloc(sizeof(int) * stack->capacity);
    stack->top = -1;

    push(stack, 10);
    push(stack, 15);
    push(stack, 20);

    int result = 0;
    while (result != -1) {
        result = pop(stack);
        printf("%d\n", result);
    }


    return (0);
}

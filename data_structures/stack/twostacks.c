/* http://www.geeksforgeeks.org/?p=18754 */

#include <stdio.h>
#include <stdlib.h>

// A structure to represent a stack
typedef struct Stack
{
    int top1;
    int top2;
    unsigned capacity;
    int* array;
} Stack;

int
is_stack1_full(Stack *stack)
{
    if (stack->top1 == stack->capacity-1) {
        return (1);
    }

    /* check if stack overlaps with the second stack */
    if ((stack->top1 + 1) == stack->top2) {
        return (1);
    }

    return (0);
}

int
is_stack2_full(Stack *stack)
{
    if (stack->top2 == -1) {
        return (1);
    }

    /* check if stack overlaps with the forst stack */
    if ((stack->top2 - 1) == stack->top1) {
        return (1);
    }

    return (0);
}

int
is_stack1_empty(Stack *stack)
{
    if (stack->top1 == -1) {
        return (1);
    }
    return (0);
}

int
is_stack2_empty(Stack *stack)
{
    /* we are at the right most position */
    if (stack->top2 == stack->capacity) {
        return (1);
    }
    return (0);
}

void
push1(Stack *stack, int data)
{
    if (is_stack1_full(stack)) {
        printf("stack 1 is full, failed to push %d to index %d\n", data, stack->top1 + 1);
        return;
    }

    /* increment the number of elements in the stack */
    stack->array[++stack->top1] = data;
}

void
push2(Stack *stack, int data)
{
    if (is_stack2_full(stack)) {
        printf("stack 2 is full, failed to push %d to index %d\n", data, stack->top2 - 1);
        return;
    }

    /* increment the number of elements in the stack */
    stack->array[--stack->top2] = data;
}

int
pop1(Stack *stack)
{
    int head_val = -1;

    if (is_stack1_empty(stack)) {
        printf("Nothing to pop\n");
        return (head_val);
    }

    head_val = stack->array[stack->top1--];

    return (head_val);
}

int
pop2(Stack *stack)
{
    int head_val = -1;

    if (is_stack2_empty(stack)) {
        printf("Nothing to pop in stack2\n");
        return (head_val);
    }

    head_val = stack->array[stack->top2++];

    return (head_val);
}

int
main(int argc, char *argv[])
{
    /* create a stack of size capacity */
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    stack->capacity = 10;
    stack->array = (int *) malloc(sizeof(int) * stack->capacity);
    stack->top1 = -1;
    stack->top2 = stack->capacity;

    push1(stack, 10);
    push1(stack, 20);
    push1(stack, 30);

    push2(stack, 80);
    push2(stack, 90);
    push2(stack, 100);
    push2(stack, 110);

    push1(stack, 49);
    push1(stack, 50);
    push1(stack, 60);
    push1(stack, 70);

    push1(stack, 999);
    push2(stack, 999);

    /* pop elements in stack1 */
    int result = 0;
    while (result != -1) {
        result = pop1(stack);
        printf("%d\n", result);
    }

    /* pop elements in stack2 */
    result = 0;
    while (result != -1) {
        result = pop2(stack);
        printf("%d\n", result);
    }

    return (0);
}

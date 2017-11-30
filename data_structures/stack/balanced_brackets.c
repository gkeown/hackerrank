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

int
is_match(char bracket1, char bracket2) {
    int res = 0;

    switch (bracket1) {
        case '{':
            if (bracket2 == '}') {
                res = 1;
            }
            break;
        case '(':
            if (bracket2 == ')') {
                res = 1;
            }
            break;
        default:
            printf("Not an opening bracket\n");
    }

    if (res == 0) {
        printf("No match - %c %c\n", bracket1, bracket2);
    }

    return (res);
}

int
is_balanced(char *exp)
{
    int res = 0;
    StackNode *stack = NULL;
    int i = 0;

    if (exp == NULL) {
        printf("No expression to evaluate\n");
        return (0);
    }

    for (i = 0; exp[i]; i++) {
        switch (exp[i]) {
            /* push opening brackets onto the stack */
            case '{':
            case '(':
                push(&stack, exp[i]);
                break;
            /* pop closing brackets off the stack */
            case ')':
            case '}':
                /* not balanced if closing bracket matches nothing on stack */
                if (isEmpty(stack)) {
                    printf("Nothing on stack to compare %c\n", exp[i]);
                    return (0);
                }

                /* check if closing bracket matches last pushed opening bracket */
                if (!is_match(pop(&stack), exp[i])) {
                    return (0);
                }
                break;
        }
    }

    /* check if opening brackets still left on stack */
    if (!isEmpty(stack)) {
        printf("Following items still remain on stack: ");
        while (!isEmpty(stack)) {
            printf("%c ", pop(&stack));        
        }
        printf("\n");
        return (0);
    }

    return (1);
}

int
main(int argc, char *argv[])
{
    int res = 0;
    char exp[] = "for { int i = 0; if (i == 0) { printf(\"success\");}}";
    printf("%s is %s\n", exp, is_balanced(exp) ? "balanced" : "not balanced");

    char exp2[] = "for { int i = 0; if (i == 0)  printf(\"success\");}}";
    printf("%s is %s\n", exp2, is_balanced(exp2) ? "balanced" : "not balanced");

    char exp3[] = "{({{})}}";
    printf("%s is %s\n", exp3, is_balanced(exp3) ? "balanced" : "not balanced");

    char exp4[] = "{{{({})}";
    printf("%s is %s\n", exp4, is_balanced(exp4) ? "balanced" : "not balanced");

    return (0);
}

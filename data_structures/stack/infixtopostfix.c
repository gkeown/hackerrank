/* http://www.geeksforgeeks.org/stack-set-2-infix-to-postfix/ */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
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

    // printf("pushed %c to stack\n", new_node->data);
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

	// printf("popped %c\n", result);

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
is_operand(char ch)
{
    int result = 0;
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
        result = 1;
    }

    return (result);
}

int
get_precedence(char op)
{
    int precedence = 0;
    switch (op) {
        case '+':
        case '-':
            precedence = 1;
            break;
        case '*':
        case '/':
            precedence = 2;
            break;
        case '^':
            precedence = 3;
            break;
        default:
            precedence = -1;
            break;
    }
    return (precedence);
}

int
infix_to_postfix(char *exp)
{
    StackNode *stack = NULL;
    int i, k;

    if (exp == NULL) {
        return (-1);
    }

    /* scan the infix expression from left to right */
    for (i = 0, k = -1; exp[i]; i++) {

        /* if scanned character is an operand then output the value */
        if (is_operand(exp[i])) {
            exp[++k] = exp[i];
        } else if (exp[i] == '(') {
            push(&stack, exp[i]);
        } else if (exp[i] == ')') {
            /* pop from the stack until a matching '(' is encountered */
            while (!isEmpty(stack) && (peek(stack) != '(')) {
				exp[++k] = pop(&stack);
            }

            /* need to pop the '(' after all other operators */
            if (!isEmpty(stack) && (peek(stack) != '(')) {
                return (-1);
			} else {
				pop(&stack);
			}
        } else {

            /* if the precedence of an operator is greater than one on the stack, push to stack */
            while (!isEmpty(stack) && get_precedence(exp[i]) <= get_precedence(peek(stack))) {
                exp[++k] = pop(&stack);
            }
            push(&stack, exp[i]);
        }
    }

    // pop all the operators from the stack
    while (!isEmpty(stack))
        exp[++k] = pop(&stack);
 
    exp[++k] = '\0';
}

/* Algorithm:
 * 1) Create a stack to store operands (or values).
 * 2) Scan the given expression and do following for every scanned element.
 * …..a) If the element is a number, push it into the stack
 * …..b) If the element is a operator, pop operands for the operator from stack. Evaluate the operator and push the result back to the stack
 * 3) When the expression is ended, the number in the stack is the final answer
 */
int
evaluate_postfix(char *exp)
{
	int result = 0;

	if (exp == NULL) {
		printf("Nothing to process\n");
		return (-1);
	}

	/* stack to push numbers onto and pop numbers off */
	StackNode *stack = NULL;

	/* process each character in the expression */
	for (int i = 0; exp[i]; i++) {

		/* push numbers onto the stack */
		if (isdigit(exp[i])) {
            push(&stack, exp[i] - '0');
		} else {
			/* pop two operands from the stack */
			int operand1 = pop(&stack);
			int operand2 = pop(&stack);

			if (operand1 == -1 || operand2 == -1) {
				printf("Error: less than two operands\n");
				return (-1);
			}

			/* convert the ASCII to operator */
			switch (exp[i]) {
                case '+':
                    push(&stack, operand2 + operand1);
                    break;
                case '-':
                    push(&stack, operand2 - operand1);
                    break;
                case '*':
                    push(&stack, operand2 * operand1);
                    break;
                case '/':
                    push(&stack, operand2 / operand1);
                    break;
                default:
                    printf("Not an operator, should not be possible.\n");
            }
		}
	}

	/* pop the remaining element from the stack? */
	return (peek(stack) ? pop(&stack) : -1);
}

int
main(int argc, char *argv[])
{
    char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
	printf("infix: %s\n", exp);
    infix_to_postfix(exp);
    printf("postfix: %s\n", exp);

    char exp2[] = "231*+9-";
    printf("Value of %s = %d\n", exp2, evaluate_postfix(exp2));

    return (0);
}

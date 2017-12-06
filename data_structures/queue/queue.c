#include <stdio.h>
#include <stdlib.h>

/* linked list implementation */
typedef struct QNode {
    int data;
    struct QNode *next;
} QNode;

/* queue structure */
typedef struct Queue {
    QNode *front;
    QNode *back;
} Queue;

QNode *
init_node(int data)
{
    QNode *new_node = (QNode *) malloc(sizeof(QNode));
    new_node->data = data;
    new_node->next = NULL;

    return (new_node);
}

Queue *
init_queue(void) {
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->front = NULL;
    queue->back = NULL;
}

void
enqueue(Queue *queue, int value)
{
    QNode *node = init_node(value);

    /* if the queue is empty the set node to front and back */
    if (queue->front == NULL) {
        queue->front = node;
        queue->back = node;
        return;
    }

    /* otherwise set new back element */
    queue->back->next = node;
    queue->back = node;
}

QNode *
dequeue(Queue *queue)
{
    int value = 0;
    QNode *node = NULL;

    if (queue == NULL || queue->front == NULL) {
        printf("queue empty or not initialised\n");
        return (NULL);
    }

    node = queue->front;
    queue->front = queue->front->next;

    /* queue is empty, set back element to NULL also */
    if (queue->front == NULL) {
        queue->back = NULL;
    }

    return (node);
}

int
main(int argc, char *argv[])
{
    Queue *queue = init_queue();    
    QNode *node = NULL;
    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    while (node = dequeue(queue)) {
        printf("%d\n", node->data);
    }

    return (0);
}

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

void
push(Queue **queue, int data)
{
    Queue *new_queue = NULL;
    QNode *node = NULL;

    /* if queue is empty, enqueue element */
    if ((*queue)->front == NULL) {
        enqueue(*queue, data);
        return;
    }

    /* otherwise create a new queue, initialise top of queue to new element, then dequeue the previous queue */
    new_queue = init_queue();
    enqueue(new_queue, data);

    while ((*queue)->front != NULL) {
        node = dequeue(*queue);
        enqueue(new_queue, node->data);
    }
    free(*queue);
    *queue = new_queue;
}

QNode *
pop(Queue *queue)
{
    QNode *node = NULL;

    node = dequeue(queue);

    return (node);
}

void
push2(Queue *queue, int data)
{
    /* the top of the stack is the tail of the queue */
    enqueue(queue, data);
}

QNode *
pop2(Queue **queue)
{
    Queue *new_queue = NULL;
    QNode *node = NULL;

    if ((*queue)->front == NULL) {
        printf("Nothing on queue\n");
        return (NULL);
    }

    /* pop all of the elements on the queue until only the tail element remains */
    new_queue = init_queue();
    while ((*queue)->front != (*queue)->back) {
        /* add all of the elements but the tail element onto new queue */
        node = dequeue(*queue);
        if (node != NULL) {
            enqueue(new_queue, node->data);
        }
    }

    /* return the final element as the head of the queue */
    node = (*queue)->front;
    free(*queue);

    /* set queue to the new queue without the final element */
    *queue = new_queue;
    return (node);
}

int
main(int argc, char *argv[])
{
    Queue *queue = init_queue();    

    push2(queue, 10);
    push2(queue, 20);
    push2(queue, 30);

    QNode *node = queue->front;
    while (node != NULL) {
        node = pop2(&queue);
        if (node != NULL) {
            printf("%d ", node->data);
        }
    }
    printf("\n");

    return (0);
}

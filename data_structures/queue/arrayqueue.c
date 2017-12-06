#include <stdio.h>
#include <stdlib.h>

typedef struct Queue {
    int front;
    int back;
    int size;
    int max_size;
    int *array;
} Queue;

Queue *
init_queue(int size)
{
    Queue *queue = (Queue *) malloc(sizeof(Queue));
    queue->front = 0;
    queue->back = 0;
    queue->size = 0;
    queue->max_size = size;
    queue->array = malloc(sizeof(int) * queue->max_size);
    return (queue);
}

void
enqueue(Queue *queue, int data)
{
    /* add first element and initialise front and back to value */
    if (queue->size == 0) {
        queue->array[queue->front] = data;
        queue->array[queue->back] = data;
        queue->size++;
        printf("adding %d to front/back\n", data);
        return;
    }

    /* don't add if queue is full */
    if (queue->size >= queue->max_size) {
        return;
    }

    /* use a circular queue to set next element */
    queue->back = (queue->back + 1) % queue->max_size;
    queue->array[queue->back] = data;
    queue->size++;
    printf("adding %d to back elem: %d\n", data, queue->back);
}

int
dequeue(Queue *queue)
{
    int data = 0;

    if (queue->size == 0) {
        printf("Nothing to dequeue\n");
        return (-1);
    }

    /* return front of queue data */
    data = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->max_size;
    queue->size--;    

    /* if size is now empty, then front and back should be the same */
    if (queue->size == 0) {
        queue->back = queue->front;
    }

    return (data);
}

int
main(int argc, char *argv[])
{
    Queue *queue = init_queue(10);

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);
    enqueue(queue, 40);
    enqueue(queue, 60);
    enqueue(queue, 90);

    printf("dequeuing %d\n", dequeue(queue));
    printf("dequeuing %d\n", dequeue(queue));
    printf("dequeuing %d\n", dequeue(queue));
    
    enqueue(queue, 70);
    enqueue(queue, 20);
    enqueue(queue, 80);
    enqueue(queue, 70);
    enqueue(queue, 20);
    enqueue(queue, 90);

    int i = 0;
    while (queue->size != 0) {
        printf("%d ", dequeue(queue));
        i++;
    }
    printf("\n");

    return (0);
}

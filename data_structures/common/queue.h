/* QUEUE FUNCTIONALITY */
typedef struct QNode {
        int data;
            struct QNode *next;
} QNode;

typedef struct Queue {
        QNode *front;
            QNode *back;
} Queue;

QNode * init_node(int data);
Queue * init_queue(void);
void enqueue(Queue *queue, int value);
QNode * dequeue(Queue *queue);

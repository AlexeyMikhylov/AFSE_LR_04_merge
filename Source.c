#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//кольцевая очередь
typedef struct {
    int data[MAX_SIZE];
    int front, rear;
} Queue;

//Инициализация очереди
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isFull(Queue* q) {
    return (q->rear + 1) % MAX_SIZE == q->front;
}

int isEmpty(Queue* q) {
    return q->front == -1;
}

//добавление элемента в очередь
void enqueue(Queue* q, int value) {
    if (isFull(q)) {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q)) {
        q->front = 0;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->data[q->rear] = value;
}

//удаление очереди
int dequeue(Queue* q)
{
    if (isEmpty(q))
    {
        printf("Queue is empty\n");
        return -1;
    }
    int value = q->data[q->front];
    
    if (q->front == q->rear)
    {
        q->front = -1;
        q->rear = -1;
    }
    else
    {
        q->front = (q->front + 1) % MAX_SIZE;
    }
    return value;
}

int main()
{
    //открытие файла
    FILE* file = fopen("input.txt", "r");
    if (!file) {
        printf("Unable to open file\n");
        return 1;
    }

    //инициализация очереди
    Queue q;
    initQueue(&q);

    //заполнение очереди
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        enqueue(&q, num);
    }

    fclose(file);

    // Пример вывода содержимого очереди
    printf("Raw Queue:\n\n");
    while (!isEmpty(&q)) {
        printf("%d ", dequeue(&q));
    }

    printf("\n\n");
    return 0;
}
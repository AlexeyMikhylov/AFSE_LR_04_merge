#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//кольцевая очередь
typedef struct
{
    int data[MAX_SIZE];
    int front, rear;
} Queue;

//Инициализация очереди
void initQueue(Queue* q)
{
    q->front = -1;
    q->rear = -1;
}

int isFull(Queue* q)
{
    return (q->rear + 1) % MAX_SIZE == q->front;
}

int isEmpty(Queue* q)
{
    return q->front == -1;
}

//добавление элемента в очередь
void enqueue(Queue* q, int value)
{
    if (isFull(q))
    {
        printf("Queue is full\n");
        return;
    }
    if (isEmpty(q))
    {
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

//
void merge(Queue* q, int left, int mid, int right)
{
    int size1 = mid - left + 1;
    int size2 = right - mid;

    //int L[size1], R[size2];
    int* L = (int*)malloc(size1 * sizeof(int));
    int* R = (int*)malloc(size2 * sizeof(int));

    for (int i = 0; i < size1; i++)
    {
        L[i] = q->data[(left + i) % MAX_SIZE];
    }
    for (int j = 0; j < size2; j++)
    {
        R[j] = q->data[(mid + 1 + j) % MAX_SIZE];
    }

    int i = 0, j = 0, k = left;
    while (i < size1 && j < size2)
    {
        if (L[i] <= R[j])
        {
            q->data[k % MAX_SIZE] = L[i];
            i++;
        }
        else
        {
            q->data[k % MAX_SIZE] = R[j];
            j++;
        }
        k++;
    }

    while (i < size1)
    {
        q->data[k % MAX_SIZE] = L[i];
        i++;
        k++;
    }

    while (j < size2)
    {
        q->data[k % MAX_SIZE] = R[j];
        j++;
        k++;
    }
}

void mergeSortUtil(Queue* q, int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        mergeSortUtil(q, left, mid);
        mergeSortUtil(q, mid + 1, right);
        merge(q, left, mid, right);
    }
}

void mergeSort(Queue* q)
{
    mergeSortUtil(q, q->front, q->rear);
}
//

void fillQueue(Queue* q)
{
    //открытие файла
    FILE* file = fopen("input.txt", "r");
    if (!file)
    {
        printf("Unable to open file\n");
        return 1;
    }

    //заполнение очереди
    int num;
    while (fscanf(file, "%d", &num) == 1)
    {
        enqueue(&q, num);
    }

    fclose(file);
}

/*void printQueue(Queue* q, char message[64])
{
    printf("%s:\n\n", message);
    while (!isEmpty(&q))
    {
        printf("%d ", dequeue(&q));
    }
}*/

void printQueue(Queue q, char message[64])
{
    printf("%s:\n\n", message);
    int i = q.front;
    while (i % MAX_SIZE != q.rear) {
        printf("%d ", q.data[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("%d\n\n", q.data[q.rear]);
}

int main()
{
    //открытие файла
    FILE* file = fopen("input.txt", "r");
    if (!file)
    {
        printf("Unable to open file\n");
        return 1;
    }

    //инициализация очереди
    Queue q;
    initQueue(&q);

    //заполнение очереди
    int num;
    while (fscanf(file, "%d", &num) == 1)
    {
        enqueue(&q, num);
    }

    fclose(file);
    printQueue(q, "Raw queue");
    
    mergeSort(&q);
    printQueue(q, "Sorted queue");

    printf("\n\n");
    return 0;
}
//!!!
// 
// 
// 
// 
// 
// 
// 
// 
// Look branch "_v2"
// 
// 
// 
// 
// 
// 
// 
// 
// 
//!!!

#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct {
    int data[MAX_SIZE];
    int front, rear;
} Queue;

void initQueue(Queue* q) {
    q->front = q->rear = -1;
}

void enqueue(Queue* q, int value) {
    if ((q->front == 0 && q->rear == MAX_SIZE - 1) || (q->rear == (q->front - 1) % (MAX_SIZE - 1))) {
        printf("Queue is full\n");
        return;
    }

    if (q->front == -1) {
        q->front = q->rear = 0;
        q->data[q->rear] = value;
    }
    else {
        q->rear = (q->rear + 1) % MAX_SIZE;
        q->data[q->rear] = value;
    }
}

int dequeue(Queue* q) {
    if (q->front == -1) {
        printf("Queue is empty\n");
        return -1;
    }

    int value = q->data[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    }
    else {
        q->front = (q->front + 1) % MAX_SIZE;
    }

    return value;
}

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    //sortedArray = (int*)malloc(ammount * sizeof(int));
    int* L = (int*)malloc(n1 * sizeof(int));
    int* R = (int*)malloc(n2 * sizeof(int));
    //int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

int main() {
    FILE* file;
    int num;
    Queue q;
    initQueue(&q);

    // Открываем файл для чтения
    file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    // Считываем числа из файла в кольцевую очередь
    while (fscanf(file, "%d", &num) != EOF) {
        enqueue(&q, num);
    }

    fclose(file);

    // Переношу числа из очереди в массив
    int arr[MAX_SIZE];
    int i = 0;
    while (q.front != -1) {
        arr[i] = dequeue(&q);
        i++;
    }

    // Сортировка методом слияния
    mergeSort(arr, 0, i - 1);

    // Вывод отсортированных чисел
    printf("Sorted arrat:\n");
    for (int j = 0; j < i; j++) {
        printf("%d ", arr[j]);
    }
    printf("\n");

    return 0;
}
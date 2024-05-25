#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

//красно-черное дерево
typedef enum Color
{
    RED,
    BLACK
} Color;

typedef struct Tree
{
    int value;
    Color color;
    struct Node* left, * right, * parent;
} Node;

//создание нового красного потомка
Node* createNode(int value)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->color = RED;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->parent = NULL;
    return newNode;
}

//Добавление потомка
void insert(Node** root, int data)
{
    Node* current = *root;
    Node* parent = NULL;

    //пока текущий узел не равен нулю
    while (current != NULL)
    {
        parent = current;

        //меньшее число вставляем слева)
        if (data < current->value)
        {
            current = current->left;
        }
        else //большее справа
        {
            current = current->right;
        }
    }

    //добавляем потомка
    Node* newNode = createNode(data);
    newNode->parent = parent;

    //если нет родителя, то потомок = первый узел
    if (parent == NULL)
    {
        *root = newNode;
    } //иначе вставка слева, если потомок меньше предка
    else if (data < parent->value)
    {
        parent->left = newNode;
    }
    else //справа, если больше
    {
        parent->right = newNode;
    }
}

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

//Сортировка очередей
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

//разделеие очереди на половины
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

//сортировка очереди слиянием
void mergeSort(Queue* q)
{
    mergeSortUtil(q, q->front, q->rear);
}

//Вывод очереди на экран
void printQueue(Queue q, char message[64])
{
    printf("%s:\n\n", message);
    int i = q.front;
    while (i % MAX_SIZE != q.rear)
    {
        printf("%d ", q.data[i]);
        i = (i + 1) % MAX_SIZE;
    }
    printf("%d\n\n", q.data[q.rear]);
}

//Заполнение дерева очередью
void fillRBTree(Node** root, Queue q)
{
    int i = q.front;
    while (i % MAX_SIZE != q.rear)
    {
        insert(root, q.data[i]);
        i = (i + 1) % MAX_SIZE;
    }
    insert(root, q.data[q.rear]);
}

//Вывод дерева
void printTree(Node* root)
{
    if (root == NULL)
        return;

    printTree(root->left);

    printf("%d ", root->value);

    printTree(root->right);
}

int main()
{
    //инициализация очереди
    Queue q;
    initQueue(&q);

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

    //вывод очереди
    printQueue(q, "Raw queue");
    
    //сортировка очереди
    mergeSort(&q);

    //вывод очереди
    printQueue(q, "Sorted queue");

    //инициализируем дерево
    Node* peak = NULL;

    //заполняем дерево 
    fillRBTree(&peak, q);

    //вывод дерева
    printf("Red and Black Tree:\n\n");
    printTree(peak);

    printf("\n\n");
    return 0;
}
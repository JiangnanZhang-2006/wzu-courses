#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct QNode {
    ElementType data;
    struct QNode* next;
} QNode;

typedef struct {
    QNode* front;  // 队头指针
    QNode* rear;   // 队尾指针
    int size;      // 队列长度
} LinkQueue;

typedef struct {
    LinkQueue* queue;  // 用于存储时间戳的队列
} RecentCounter;

typedef struct {
    LinkQueue* q1;  // 主队列
    LinkQueue* q2;  // 辅助队列
} MyStack;

typedef enum { OK = 1, ERROR = 0 } Status;

/* 需要你实现的函数 */
LinkQueue* InitQueue(void);

/* 其他操作函数声明（本题不需要实现） */
int IsEmpty(const LinkQueue* Q);
int GetSize(const LinkQueue* Q);
Status EnQueue(LinkQueue* Q, ElementType x);
Status DeQueue(LinkQueue* Q, ElementType* x);
Status GetFront(const LinkQueue* Q, ElementType* x);
void Clear(LinkQueue* Q);
void PrintQueue(const LinkQueue* Q);
void DestroyQueue(LinkQueue** pQ);
Status ConcatQueue(LinkQueue* Q1, LinkQueue* Q2);
Status SplitQueue(LinkQueue* Q, int k, LinkQueue* Q1, LinkQueue* Q2);
Status RemoveDuplicates(LinkQueue* Q);
Status SortQueue(LinkQueue* Q);
Status SplitByParity(LinkQueue* Q, LinkQueue* Qodd, LinkQueue* Qeven);
Status InterleaveQueue(LinkQueue* Q1, LinkQueue* Q2, LinkQueue* Q3);
int HotPotato(LinkQueue* Q, int num);
void PrintPascalTriangle(int n);

RecentCounter* RecentCounterCreate(void);             // 创建统计器
int            RecentCounterPing(RecentCounter* obj, int t); // 记录请求
void           RecentCounterFree(RecentCounter* obj); // 释放统计器

MyStack*   MyStackCreate(void);                       // 创建栈
void       MyStackPush(MyStack* obj, int x);          // 入栈
int        MyStackPop(MyStack* obj);                  // 出栈
int        MyStackTop(MyStack* obj);                  // 获取栈顶元素
int        MyStackEmpty(MyStack* obj);                // 判断栈是否为空
void       MyStackFree(MyStack* obj);                 // 销毁栈

int main()
{
    /*
     * 此处代码由测试程序自动添加。
     * 你只需提交上述函数的实现。
     */
    return 0;
}

/******************** 学生提交的"缺失函数"会被拼接在此处 ********************/
/*
例如缺失 InitQueue 时，学生只提交：
LinkQueue* InitQueue(void) { ... }
*/

LinkQueue* InitQueue(void) {
    LinkQueue* Q = (LinkQueue*)malloc(sizeof(LinkQueue));
    if (Q == NULL) return NULL;
    Q->front = NULL;
    Q->rear = NULL;
    Q->size = 0;
    return Q;
}

int IsEmpty(const LinkQueue* Q) {
    if (Q == NULL) return 1;
    if (Q->front == NULL) return 1;
    return 0;
}

int GetSize(const LinkQueue* Q) {
    if (Q == NULL) return 0;
    return Q->size;
}

Status EnQueue(LinkQueue* Q, ElementType x) {
    if (Q == NULL) return ERROR;
    QNode* newNode = (QNode*)malloc(sizeof(QNode));
    if (newNode == NULL) return ERROR;
    newNode->data = x;
    newNode->next = NULL;
    if (IsEmpty(Q)) {
        Q->front = newNode;
        Q->rear = newNode;
    } else {
        Q->rear->next = newNode;
        Q->rear = newNode;
    }
    Q->size++;
    return OK;
}

Status DeQueue(LinkQueue* Q, ElementType* x) {
    if (Q == NULL || x == NULL || IsEmpty(Q)) return ERROR;
    *x = Q->front->data;
    QNode* temp = Q->front;
    Q->front = Q->front->next;
    free(temp);
    Q->size--;
    if (Q->front == NULL) Q->rear = NULL;
    return OK;
}

Status GetFront(const LinkQueue* Q, ElementType* x) {
    if (Q == NULL || x == NULL || IsEmpty(Q)) return ERROR;
    *x = Q->front->data;
    return OK;
}

void Clear(LinkQueue* Q) {
    if (Q == NULL) return;
    while (Q->front != NULL) {
        QNode* temp = Q->front;
        Q->front = Q->front->next;
        free(temp);
    }
    Q->rear = NULL;
    Q->size = 0;
}

void PrintQueue(const LinkQueue* Q) {
    if (Q == NULL || IsEmpty(Q)) {
        printf("NULL\n");
        return;
    }
    int first = 1;
    for (QNode* p = Q->front; p != NULL; p = p->next) {
        if (first) {
            printf("%d", p->data);
            first = 0;
        } else {
            printf(" %d", p->data);
        }
    }
    printf("\n");
}

void DestroyQueue(LinkQueue** pQ) {
    if (pQ == NULL) return;
    if (*pQ == NULL) return;
    Clear(*pQ);
    free(*pQ);
    *pQ = NULL;
}

Status ConcatQueue(LinkQueue* Q1, LinkQueue* Q2) {
    if (Q1 == NULL || Q2 == NULL || Q1 == Q2) return ERROR;
    if (!IsEmpty(Q2)) {
        if (IsEmpty(Q1)) {
            Q1->front = Q2->front;
            Q1->rear = Q2->rear;
            Q1->size = Q2->size;
        } else {
            Q1->rear->next = Q2->front;
            Q1->rear = Q2->rear;
            Q1->size += Q2->size;
        }
    }
    Q2->front = NULL;
    Q2->rear = NULL;
    Q2->size = 0;
    return OK;
}

Status SplitQueue(LinkQueue* Q, int k, LinkQueue* Q1, LinkQueue* Q2) {
    if (Q == NULL || Q1 == NULL || Q2 == NULL) return ERROR;
    if (k < 0 || k > Q->size) return ERROR;
    if (!IsEmpty(Q1) || !IsEmpty(Q2)) return ERROR;

    int n = Q->size;
    if (k == 0) {
        Q1->front = NULL;
        Q1->rear = NULL;
        Q1->size = 0;
        Q2->front = Q->front;
        Q2->rear = Q->rear;
        Q2->size = n;
    } else if (k == n) {
        Q1->front = Q->front;
        Q1->rear = Q->rear;
        Q1->size = n;
        Q2->front = NULL;
        Q2->rear = NULL;
        Q2->size = 0;
    } else {
        QNode* p = Q->front;
        QNode* pre = NULL;
        for (int i = 0; i < k; i++) {
            pre = p;
            p = p->next;
        }
        Q1->front = Q->front;
        Q1->rear = pre;
        Q1->size = k;
        pre->next = NULL;
        Q2->front = p;
        Q2->rear = Q->rear;
        Q2->size = n - k;
    }
    Q->front = NULL;
    Q->rear = NULL;
    Q->size = 0;
    return OK;
}

Status RemoveDuplicates(LinkQueue* Q) {
    if (Q == NULL) return ERROR;
    int dic[2005];
    for (int i = 0; i < 2005; i++) {
        dic[i] = 0;
    }
    QNode* curr = Q->front;
    QNode* prev = NULL;
    int count = 0;
    while (curr != NULL) {
        int idx = curr->data + 1000;
        if (dic[idx] == 0) {
            dic[idx] = 1;
            prev = curr;
            curr = curr->next;
        } else {
            QNode* temp = curr;
            if (prev == NULL) {
                Q->front = curr->next;
            } else {
                prev->next = curr->next;
            }
            if (curr == Q->rear) {
                Q->rear = prev;
            }
            curr = (prev == NULL) ? Q->front : prev->next;
            free(temp);
            count++;
        }
    }
    Q->size -= count;
    return OK;
}

Status SortQueue(LinkQueue* Q) {
    if (Q == NULL) return ERROR;
    int n = Q->size;
    if (n == 0) return OK;
    int* arr = (int*)malloc(sizeof(int) * (size_t)n);
    if (arr == NULL) return ERROR;
    for (int i = 0; i < n; i++) {
        DeQueue(Q, &arr[i]);
    }
    qsort(arr, (size_t)n, sizeof(int), [](const void* a, const void* b) -> int {
        int x = *(const int*)a;
        int y = *(const int*)b;
        return (x > y) - (x < y);
    });
    for (int i = 0; i < n; i++) {
        EnQueue(Q, arr[i]);
    }
    free(arr);
    return OK;
}

Status SplitByParity(LinkQueue* Q, LinkQueue* Qodd, LinkQueue* Qeven) {
    if (Q == NULL || Qodd == NULL || Qeven == NULL) return ERROR;
    if (!IsEmpty(Qodd) || !IsEmpty(Qeven)) return ERROR;
    while (!IsEmpty(Q)) {
        ElementType x;
        DeQueue(Q, &x);
        if (x % 2 == 0) {
            EnQueue(Qeven, x);
        } else {
            EnQueue(Qodd, x);
        }
    }
    return OK;
}

Status InterleaveQueue(LinkQueue* Q1, LinkQueue* Q2, LinkQueue* Q3) {
    if (Q1 == NULL || Q2 == NULL || Q3 == NULL) return ERROR;
    if (!IsEmpty(Q3)) return ERROR;
    while (!IsEmpty(Q1) && !IsEmpty(Q2)) {
        ElementType x;
        DeQueue(Q1, &x);
        EnQueue(Q3, x);
        DeQueue(Q2, &x);
        EnQueue(Q3, x);
    }
    while (!IsEmpty(Q1)) {
        ElementType x;
        DeQueue(Q1, &x);
        EnQueue(Q3, x);
    }
    while (!IsEmpty(Q2)) {
        ElementType x;
        DeQueue(Q2, &x);
        EnQueue(Q3, x);
    }
    return OK;
}

int HotPotato(LinkQueue* Q, int num) {
    if (Q == NULL || num < 1) return -1;
    if (IsEmpty(Q)) return -1;
    while (Q->size > 1) {
        for (int i = 0; i < num - 1; i++) {
            ElementType x;
            DeQueue(Q, &x);
            EnQueue(Q, x);
        }
        ElementType x;
        DeQueue(Q, &x);
    }
    ElementType x;
    if (GetFront(Q, &x) != OK) return -1;
    return x;
}

void PrintPascalTriangle(int n) {
    if (n <= 0) return;
    LinkQueue* Q = InitQueue();
    if (Q == NULL) return;
    EnQueue(Q, 1);
    for (int i = 0; i < n; i++) {
        PrintQueue(Q);
        if (i == n - 1) break;
        EnQueue(Q, 0);
        LinkQueue* Qnext = InitQueue();
        if (Qnext == NULL) {
            DestroyQueue(&Q);
            return;
        }
        ElementType prev = 0;
        while (!IsEmpty(Q)) {
            ElementType x;
            DeQueue(Q, &x);
            EnQueue(Qnext, prev + x);
            prev = x;
        }
        DestroyQueue(&Q);
        Q = Qnext;
    }
    DestroyQueue(&Q);
}

// RecentCounter* RecentCounterCreate(void) {
//     RecentCounter* obj = (RecentCounter*)malloc(sizeof(RecentCounter));
//     if (obj == NULL) return NULL;
//     obj->queue = InitQueue();
//     if (obj->queue == NULL) {
//         free(obj);
//         return NULL;
//     }
//     return obj;
// }

// int RecentCounterPing(RecentCounter* obj, int t) {
//     if (obj == NULL) return -1;
//     EnQueue(obj->queue, t);
//     while (obj->queue->front->data < t - 3000) {
//         ElementType x;
//         DeQueue(obj->queue, &x);
//     }
//     return obj->queue->size;
// }

// void RecentCounterFree(RecentCounter* obj) {
//     if (obj == NULL) return;
//     DestroyQueue(&obj->queue);
//     free(obj);
// }

MyStack* MyStackCreate(void) {
    MyStack* obj = (MyStack*)malloc(sizeof(MyStack));
    if (obj == NULL) return NULL;
    obj->q1 = InitQueue();
    if (obj->q1 == NULL) {
        free(obj);
        return NULL;
    }
    obj->q2 = InitQueue();
    if (obj->q2 == NULL) {
        DestroyQueue(&obj->q1);
        free(obj);
        return NULL;
    }
    return obj;
}

int MyStackEmpty(MyStack* obj) {
    if (obj == NULL) return 1;
    return IsEmpty(obj->q1);
}

void MyStackPush(MyStack* obj, int x) {
    if (obj == NULL) return;
    EnQueue(obj->q1, x);
}

int MyStackPop(MyStack* obj) {
    if (obj == NULL) return -1;
    while (obj->q1->size > 1) {
        ElementType x;
        DeQueue(obj->q1, &x);
        EnQueue(obj->q2, x);
    }
    ElementType x;
    DeQueue(obj->q1, &x);
    LinkQueue* t = obj->q1;
    obj->q1 = obj->q2;
    obj->q2 = t;
    return x;
}

int MyStackTop(MyStack* obj) {
    if (obj == NULL) return -1;
    if (IsEmpty(obj->q1)) return -1;
    return obj->q1->rear->data;
}

void MyStackFree(MyStack* obj) {
    if (obj == NULL) return;
    DestroyQueue(&obj->q1);
    DestroyQueue(&obj->q2);
    free(obj);
}
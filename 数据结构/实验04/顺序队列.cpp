#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXSIZE 1000

typedef int ElementType;

typedef struct {
    ElementType data[MAXSIZE];
    int front;  // 队头指针(指向队头元素)
    int rear;   // 队尾指针(指向队尾元素的下一位置)
} SqQueue;

typedef enum { OK = 1, ERROR = 0 } Status;

/* 需要你实现的函数 */
SqQueue* InitQueue(void);

/* 其他操作函数声明（本题不需要实现） */
int IsEmpty(const SqQueue* Q);
int IsFull(const SqQueue* Q);
int GetSize(const SqQueue* Q);
Status EnQueue(SqQueue* Q, ElementType x);
Status DeQueue(SqQueue* Q, ElementType* x);
Status GetFront(const SqQueue* Q, ElementType* x);
void Clear(SqQueue* Q);
void DestroyQueue(SqQueue** pQ);
void PrintQueue(const SqQueue* Q);
Status CopyQueue(const SqQueue* Q, SqQueue* T);
Status MergeQueue(SqQueue* Q1, SqQueue* Q2, SqQueue* Q3);
int LocateInQueue(const SqQueue* Q, ElementType x);
Status GetMaxInQueue(const SqQueue* Q, ElementType* maxVal);
int CountInQueue(const SqQueue* Q, ElementType x);
Status RemoveAllX(SqQueue* Q, ElementType x);
Status ReverseQueue(SqQueue* Q);
void Josephus(int n, int m, int result[]);
int IsPalindrome(const char* str);
Status SumQueue(const SqQueue* Q, long long* sum);

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
SqQueue* InitQueue(void) { ... }
*/

SqQueue* InitQueue(void) {
    SqQueue* Q = (SqQueue*)malloc(sizeof(SqQueue));
    if (Q == NULL) return NULL;
    Q->front = 0;
    Q->rear = 0;
    return Q;
}

static int IsEmpty(const SqQueue* Q) {
    if (Q == NULL) return 1;
    if (Q->front == Q->rear) return 1;
    return 0;
}

static int IsFull(const SqQueue* Q) {
    if (Q == NULL) return 0;
    if ((Q->rear + 1) % MAXSIZE == Q->front) return 1;
    return 0;
}

int GetSize(const SqQueue* Q) {
    if (Q == NULL) return 0;
    return (Q->rear - Q->front + MAXSIZE) % MAXSIZE;
}

Status EnQueue(SqQueue* Q, ElementType x) {
    if (Q == NULL) return ERROR;
    if (IsFull(Q)) return ERROR;
    Q->data[Q->rear] = x;
    Q->rear = (Q->rear + 1) % MAXSIZE;
    return OK;
}

Status DeQueue(SqQueue* Q, ElementType* x) {
    if (Q == NULL || x == NULL) return ERROR;
    if (IsEmpty(Q)) return ERROR;
    *x = Q->data[Q->front];
    Q->front = (Q->front + 1) % MAXSIZE;
    return OK;
}

Status GetFront(const SqQueue* Q, ElementType* x) {
    if (Q == NULL || x == NULL) return ERROR;
    if (IsEmpty(Q)) return ERROR;
    *x = Q->data[Q->front];
    return OK;
}

void Clear(SqQueue* Q) {
    if (Q == NULL) return;
    Q->front = 0;
    Q->rear = 0;
}

void DestroyQueue(SqQueue** pQ) {
    if (pQ == NULL) return;
    if (*pQ == NULL) return;
    free(*pQ);
    *pQ = NULL;
}

void PrintQueue(const SqQueue* Q) {
    if (Q == NULL || IsEmpty(Q)) {
        printf("NULL\n");
        return;
    }
    int idx = Q->front;
    int first = 1;
    while (idx != Q->rear) {
        if (first) {
            printf("%d", Q->data[idx]);
            first = 0;
        } else {
            printf(" %d", Q->data[idx]);
        }
        idx = (idx + 1) % MAXSIZE;
    }
    printf("\n");
}

Status CopyQueue(const SqQueue* Q, SqQueue* T) {
    if (Q == NULL || T == NULL) return ERROR;
    int i;
    for (i = 0; i < MAXSIZE; i++) {
        T->data[i] = Q->data[i];
    }
    T->front = Q->front;
    T->rear = Q->rear;
    return OK;
}

Status MergeQueue(SqQueue* Q1, SqQueue* Q2, SqQueue* Q3) {
    ElementType x;
    if (Q1 == NULL || Q2 == NULL || Q3 == NULL) return ERROR;
    if (GetSize(Q1) + GetSize(Q2) > MAXSIZE - 1) return ERROR;
    Clear(Q3);
    while (!IsEmpty(Q1)) {
        DeQueue(Q1, &x);
        EnQueue(Q3, x);
    }
    while (!IsEmpty(Q2)) {
        DeQueue(Q2, &x);
        EnQueue(Q3, x);
    }
    return OK;
}

int LocateInQueue(const SqQueue* Q, ElementType x) {
    int idx, pos;
    if (Q == NULL || IsEmpty(Q)) return 0;
    idx = Q->front;
    pos = 1;
    while (idx != Q->rear) {
        if (Q->data[idx] == x) return pos;
        idx = (idx + 1) % MAXSIZE;
        pos++;
    }
    return 0;
}

Status GetMaxInQueue(const SqQueue* Q, ElementType* maxVal) {
    int idx;
    if (Q == NULL || maxVal == NULL) return ERROR;
    if (IsEmpty(Q)) return ERROR;
    idx = Q->front;
    *maxVal = Q->data[idx];
    idx = (idx + 1) % MAXSIZE;
    while (idx != Q->rear) {
        if (Q->data[idx] > *maxVal) *maxVal = Q->data[idx];
        idx = (idx + 1) % MAXSIZE;
    }
    return OK;
}

int CountInQueue(const SqQueue* Q, ElementType x) {
    int idx, count;
    if (Q == NULL || IsEmpty(Q)) return 0;
    idx = Q->front;
    count = 0;
    while (idx != Q->rear) {
        if (Q->data[idx] == x) count++;
        idx = (idx + 1) % MAXSIZE;
    }
    return count;
}

Status RemoveAllX(SqQueue* Q, ElementType x) {
    ElementType val;
    int i, n;
    if (Q == NULL) return ERROR;
    n = GetSize(Q);
    for (i = 0; i < n; i++) {
        DeQueue(Q, &val);
        if (val != x) EnQueue(Q, val);
    }
    return OK;
}

Status ReverseQueue(SqQueue* Q) {
    ElementType stack[MAXSIZE];
    ElementType val;
    int top, i;
    if (Q == NULL) return ERROR;
    top = -1;
    while (!IsEmpty(Q)) {
        DeQueue(Q, &val);
        stack[++top] = val;
    }
    for (i = top; i >= 0; i--) {
        EnQueue(Q, stack[i]);
    }
    return OK;
}

void Josephus(int n, int m, int result[]) {
    SqQueue* Q;
    ElementType x;
    int i, idx;
    if (n <= 0 || m <= 0) return;
    Q = InitQueue();
    if (Q == NULL) return;
    for (i = 1; i <= n; i++) {
        EnQueue(Q, i);
    }
    idx = 0;
    while (!IsEmpty(Q)) {
        for (i = 1; i < m; i++) {
            DeQueue(Q, &x);
            EnQueue(Q, x);
        }
        DeQueue(Q, &x);
        result[idx++] = x;
    }
    DestroyQueue(&Q);
}

int IsPalindrome(const char* str) {
    SqQueue* Q;
    char stack[MAXSIZE];
    int top, i;
    char c;
    ElementType qc_elem;
    if (str == NULL || str[0] == '\0') return 1;
    Q = InitQueue();
    if (Q == NULL) return 0;
    top = -1;
    for (i = 0; str[i] != '\0'; i++) {
        if (!isalnum((unsigned char)str[i])) continue;
        c = (char)tolower((unsigned char)str[i]);
        EnQueue(Q, (ElementType)c);
        stack[++top] = c;
    }
    if (IsEmpty(Q)) {
        DestroyQueue(&Q);
        return 1;
    }
    while (!IsEmpty(Q)) {
        DeQueue(Q, &qc_elem);
        if ((char)qc_elem != stack[top--]) {
            DestroyQueue(&Q);
            return 0;
        }
    }
    DestroyQueue(&Q);
    return 1;
}

Status SumQueue(const SqQueue* Q, long long* sum) {
    int idx;
    if (Q == NULL || sum == NULL) return ERROR;
    if (IsEmpty(Q)) {
        *sum = 0;
        return OK;
    }
    *sum = 0;
    idx = Q->front;
    while (idx != Q->rear) {
        *sum += Q->data[idx];
        idx = (idx + 1) % MAXSIZE;
    }
    return OK;
}
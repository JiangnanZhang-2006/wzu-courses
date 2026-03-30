#include <stdio.h>
#include <stdlib.h>

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
    SqQueue *Q = (SqQueue*)malloc(sizeof(SqQueue));
    if (Q == NULL) return NULL;
    Q->front = 0;
    Q->rear = 0;
    return Q;
}

int IsEmpty(const SqQueue* Q) {
    if (Q == NULL) return 1;
    if (Q->front == Q->rear) return 1;
    return 0;
}

int IsFull(const SqQueue* Q) {
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
    if (Q == NULL || x == NULL || IsEmpty(Q)) return ERROR;
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
    for (int i = Q->front; i != Q->rear; i = (i + 1) % MAXSIZE) {
        if (i != Q->front) printf(" ");
        printf("%d", Q->data[i]);
    }
    printf("\n");
}

Status CopyQueue(const SqQueue* Q, SqQueue* T) {
    if (Q == NULL || T == NULL) return ERROR;
    *T = *Q;
    return OK;
}

Status MergeQueue(SqQueue* Q1, SqQueue* Q2, SqQueue* Q3) {
    if (Q1 == NULL || Q2 == NULL || Q3 == NULL) return ERROR;
    if (GetSize(Q1) + GetSize(Q2) > MAXSIZE - 1) return ERROR;
    Clear(Q3);
    ElementType x;
    while (!IsEmpty(Q1)) {
        if (DeQueue(Q1, &x) == ERROR) return ERROR;
        if (EnQueue(Q3, x) == ERROR) return ERROR;
    }
    while (!IsEmpty(Q2)) {
        if (DeQueue(Q2, &x) == ERROR) return ERROR;
        if (EnQueue(Q3, x) == ERROR) return ERROR;
    }
    return OK;
}

int LocateInQueue(const SqQueue* Q, ElementType x) {
    if (Q == NULL) return 0;
    int pos = 1;
    for (int i = Q->front; i != Q->rear; i = (i + 1) % MAXSIZE) {
        if (Q->data[i] == x) return pos;
        pos++;
    }
    return 0;
}

Status GetMaxInQueue(const SqQueue* Q, ElementType* maxVal) {
    if (Q == NULL || maxVal == NULL || IsEmpty(Q)) return ERROR;
    *maxVal = Q->data[Q->front];
    for (int i = Q->front + 1; i != Q->rear; i = (i + 1) % MAXSIZE) {
        if (Q->data[i] > *maxVal) *maxVal = Q->data[i];
    }
    return OK;
}

int CountInQueue(const SqQueue* Q, ElementType x) {
    if (Q == NULL) return 0;
    int count = 0;
    for (int i = Q->front; i != Q->rear; i = (i + 1) % MAXSIZE) {
        if (Q->data[i] == x) count++;
    }
    return count;
}

Status RemoveAllX(SqQueue* Q, ElementType x) {
    if (Q == NULL) return ERROR;
    int count = 0;
    for (int i = Q->front; i != Q->rear; i = (i + 1) % MAXSIZE) {
        if (Q->data[i] == x) count++;
        else Q->data[(i - count) % MAXSIZE] = Q->data[i];
    }
    Q->rear = (Q->rear - count) % MAXSIZE;
    return OK;
}

Status ReverseQueue(SqQueue* Q) {
    if (Q == NULL) return ERROR;
    int left = Q->front, right = Q->rear - 1;
    while (left != right && left != right + 1) {
        ElementType temp = Q->data[left];
        Q->data[left] = Q->data[right];
        Q->data[right] = temp;
        left = (left + 1) % MAXSIZE;
        right = (right - 1 + MAXSIZE) % MAXSIZE;
    }
    return OK;
}

void Josephus(int n, int m, int result[]) {
    if (n == 0 || m == 0) return;
    SqQueue* Q = InitQueue();
    if (Q == NULL) return;
    for (int i = 1; i <= n; i++) {
        if (EnQueue(Q, i) == ERROR) {
            DestroyQueue(&Q);
            return;
        }
    }
    int count = 0;
    while (!IsEmpty(Q)) {
        for (int i = 1; i < m; i++) {
            if (DeQueue(Q, &result[count]) == ERROR) {
                DestroyQueue(&Q);
                return;
            }
            if (EnQueue(Q, result[count]) == ERROR) {
                DestroyQueue(&Q);
                return;
            }
        }
        if (DeQueue(Q, &result[count]) == ERROR) {
            DestroyQueue(&Q);
            return;
        }
        count++;
    }
    DestroyQueue(&Q);
}

int IsPalindrome(const char* str)
{
    if (str == NULL) return 1;

    SqQueue* Q = InitQueue();
    if (Q == NULL) return 0;

    char stack[MAXSIZE];
    int top = -1;

    for (const char* p = str; *p != '\0'; p++) {
        unsigned char uch = (unsigned char)*p;
        char c;
        if (uch >= '0' && uch <= '9') {
            c = (char)uch;
        } else if (uch >= 'a' && uch <= 'z') {
            c = (char)uch;
        } else if (uch >= 'A' && uch <= 'Z') {
            c = (char)(uch - 'A' + 'a');
        } else {
            continue;
        }
        if (IsFull(Q) || top >= MAXSIZE - 1) {
            DestroyQueue(&Q);
            return 0;
        }
        if (EnQueue(Q, (ElementType)(unsigned char)c) == ERROR) {
            DestroyQueue(&Q);
            return 0;
        }
        stack[++top] = c;
    }

    if (IsEmpty(Q)) {
        DestroyQueue(&Q);
        return 1;
    }

    ElementType x;
    while (!IsEmpty(Q)) {
        if (DeQueue(Q, &x) == ERROR) {
            DestroyQueue(&Q);
            return 0;
        }
        if ((char)(unsigned char)x != stack[top--]) {
            DestroyQueue(&Q);
            return 0;
        }
    }
    DestroyQueue(&Q);
    return 1;
}

Status SumQueue(const SqQueue* Q, long long* sum) {
    if (Q == NULL || sum == NULL) return ERROR;
    *sum = 0;
    if (IsEmpty(Q)) return OK;
    for (int i = Q->front; i != Q->rear; i = (i + 1) % MAXSIZE) {
        *sum += (long long)Q->data[i];
    }
    return OK;
}
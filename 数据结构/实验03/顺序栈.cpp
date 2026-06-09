#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 1000

typedef int ElementType;

typedef struct {
    ElementType data[MAXSIZE];
    int top;
} SeqStack;

typedef enum { OK = 1, ERROR = 0 } Status;

/* 需要你实现的函数 */
SeqStack* InitStack(void);

/* 其他操作函数声明（本题不需要实现） */
int IsEmpty(const SeqStack* S);
int IsFull(const SeqStack* S);
int GetSize(const SeqStack* S);
Status Push(SeqStack* S, ElementType x);
Status Pop(SeqStack* S, ElementType* x);
Status GetTop(const SeqStack* S, ElementType* x);
void Clear(SeqStack* S);
void DestroyStack(SeqStack** pS);
Status CopyStack(const SeqStack* S, SeqStack* T);
void PrintStack(const SeqStack* S);
Status ReverseStack(SeqStack* S);
Status GetMin(const SeqStack* S, ElementType* min);
Status IsSymmetric(const SeqStack* S);
Status DeleteElem(SeqStack* S, ElementType e);
Status RemoveDuplicate(SeqStack* S);
Status ReverseTop(SeqStack* S, int k);
Status IsValidPopSeq(const int* push, const int* pop, int n);

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
例如缺失 InitStack 时，学生只提交：
SeqStack* InitStack(void) { ... }
*/

SeqStack* InitStack(void) {
    SeqStack* S = (SeqStack*)malloc(sizeof(SeqStack));
    if (S == NULL) return NULL;
    S->top = -1;
    return S;
}

int IsEmpty(const SeqStack* S) {
    if (S == NULL) return 1;
    if (S->top == -1) return 1;
    return 0;
}

int IsFull(const SeqStack* S) {
    if (S == NULL) return 0;
    if (S->top >= MAXSIZE - 1) return 1;
    return 0;
}

int GetSize(const SeqStack* S) {
    if (S == NULL) return 0;
    return S->top + 1;
}

Status Push(SeqStack* S, ElementType x) {
    if (S == NULL) return ERROR;
    if (IsFull(S)) return ERROR;
    S->data[++S->top] = x;
    return OK;
}

Status Pop(SeqStack* S, ElementType* x) {
    if (S == NULL || x == NULL) return ERROR;
    if (IsEmpty(S)) return ERROR;
    *x = S->data[S->top--];
    return OK;
}

Status GetTop(const SeqStack* S, ElementType* x) {
    if (S == NULL || x == NULL) return ERROR;
    if (IsEmpty(S)) return ERROR;
    *x = S->data[S->top];
    return OK;
}

void Clear(SeqStack* S) {
    if (S == NULL) return;
    S->top = -1;
}

void DestroyStack(SeqStack** pS) {
    if (pS == NULL) return;
    if (*pS == NULL) return;
    free(*pS);
    *pS = NULL;
}

Status CopyStack(const SeqStack* S, SeqStack* T) {
    if (S == NULL || T == NULL) return ERROR;
    if (IsEmpty(S)) return OK;
    for (int i = 0; i <= S->top; i++) {
        T->data[i] = S->data[i];
    }
    T->top = S->top;
    return OK;
}

void PrintStack(const SeqStack* S) {
    if (S == NULL || IsEmpty(S)) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; i <= S->top; i++) {
        printf(i == 0 ? "%d" : " %d", S->data[i]);
    }
    printf("\n");
}

Status ReverseStack(SeqStack* S) {
    if (S == NULL) return ERROR;
    if (IsEmpty(S)) return OK;
    for (int i = 0; i < (S->top + 1) / 2; i++) {
        ElementType temp = S->data[i];
        S->data[i] = S->data[S->top - i];
        S->data[S->top - i] = temp;
    }
    return OK;
}

Status GetMin(const SeqStack* S, ElementType* min) {
    if (S == NULL || min == NULL) return ERROR;
    if (IsEmpty(S)) return ERROR;
    *min = S->data[0];
    for (int i = 1; i <= S->top; i++) {
        if (S->data[i] < *min) {
            *min = S->data[i];
        }
    }
    return OK;
}

Status IsSymmetric(const SeqStack* S) {
    if (S == NULL) return ERROR;
    if (IsEmpty(S)) return OK;
    for (int i = 0; i < (S->top + 1) / 2; i++) {
        if (S->data[i] != S->data[S->top - i]) {
            return ERROR;
        }
    }
    return OK;
}

Status DeleteElem(SeqStack* S, ElementType e) {
    if (S == NULL) return ERROR;
    int count = 0;
    for (int i = 0; i <= S->top; i++) {
        if (S->data[i] == e) {
            count++;
            continue;
        }
        S->data[i - count] = S->data[i];
    }
    S->top -= count;
    return OK;
}

Status MergeStack(const SeqStack* S1, const SeqStack* S2, SeqStack* S3) {
    if (S1 == NULL || S2 == NULL || S3 == NULL) return ERROR;
    if (S1->top + S2->top + 2 > MAXSIZE) return ERROR;
    Clear(S3);
    CopyStack(S1, S3);
    for (int i = 0; i <= S2->top; i++) {
        Push(S3, S2->data[i]);
    }
    return OK;
}

Status RemoveDuplicate(SeqStack* S) {
    if (S == NULL) return ERROR;
    int count = 0;
    int dic[2005];
    for (int i = 0; i < 2005; i++) {
        dic[i] = 0;
    }
    for (int i = 0; i <= S->top; i++) {
        if (dic[S->data[i] + 1000] == 0) {
            dic[S->data[i] + 1000] = 1;
        } else {
            count++;
            continue;
        }
        S->data[i - count] = S->data[i];
    }
    S->top -= count;
    return OK;
}

Status ReverseTop(SeqStack* S, int k) {
    if (S == NULL) return ERROR;
    if (k < 0 || k > S->top + 1) return ERROR;
    if (IsEmpty(S) || k <= 1) return OK;
    int left = S->top - k + 1, right = S->top;
    while (left < right) {
        ElementType temp = S->data[left];
        S->data[left] = S->data[right];
        S->data[right] = temp;
        left++;
        right--;
    }
    return OK;
}

Status IsValidPopSeq(const int* push, const int* pop, int n) {
    if (push == NULL || pop == NULL || n <= 0) return ERROR;
    SeqStack* S = InitStack();
    if (S == NULL) return ERROR;
    int pushIdx = 0, popIdx = 0;
    ElementType temp;
    while (popIdx < n) {
        if (pushIdx < n && push[pushIdx] == pop[popIdx]) {
            pushIdx++;
            popIdx++;
        } else if (!IsEmpty(S)) {
            GetTop(S, &temp);
            if (temp == pop[popIdx]) {
                Pop(S, &temp);
                popIdx++;
            } else if (pushIdx < n) {
                Push(S, push[pushIdx++]);
            } else {
                DestroyStack(&S);
                return ERROR;
            }
        } else if (pushIdx < n) {
            Push(S, push[pushIdx++]);
        } else {
            DestroyStack(&S);
            return ERROR;
        }
    }
    DestroyStack(&S);
    return OK;
}
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct StackNode {
    ElementType data;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    int size;
} LinkStack;

typedef enum { OK = 1, ERROR = 0 } Status;

/* 需要你实现的函数 */
LinkStack* InitStack(void);

/* 其他操作函数声明（本题不需要实现） */
int IsEmpty(const LinkStack* S);
int GetSize(const LinkStack* S);
Status Push(LinkStack* S, ElementType x);
Status Pop(LinkStack* S, ElementType* x);
Status GetTop(const LinkStack* S, ElementType* x);
void Clear(LinkStack* S);
void DestroyStack(LinkStack** pS);
void PrintStack(const LinkStack* S);
Status ReverseStack(LinkStack* S);
Status GetMin(const LinkStack* S, ElementType* min);
Status IsSymmetric(const LinkStack* S);
Status DeleteElem(LinkStack* S, ElementType e);
Status MergeStack(const LinkStack* S1, const LinkStack* S2, LinkStack* S3);
Status RemoveDuplicate(LinkStack* S);
Status ReverseTop(LinkStack* S, int k);
Status GetRangeSum(const LinkStack* S, int low, int high, int* sum);
Status InterleaveStack(const LinkStack* S1, const LinkStack* S2, LinkStack* S3);

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
LinkStack* InitStack(void) { ... }
*/

LinkStack* InitStack(void) {
    LinkStack* S = (LinkStack*)malloc(sizeof(LinkStack));
    if (S == NULL) return NULL;
    S->top = NULL;
    S->size = 0;
    return S;
}

int IsEmpty(const LinkStack* S) {
    if (S == NULL) return 1;
    if (S->top == NULL) return 1;
    return 0;
}

int GetSize(const LinkStack* S) {
    if (S == NULL) return 0;
    return S->size;
}

Status Push(LinkStack* S, ElementType x) {
    if (S == NULL) return ERROR;
    StackNode* new_node = (StackNode*)malloc(sizeof(StackNode));
    if (new_node == NULL) return ERROR;
    new_node->data = x;
    new_node->next = S->top;
    S->top = new_node;
    S->size++;
    return OK;
}

Status Pop(LinkStack* S, ElementType* x) {
    if (S == NULL || x == NULL || IsEmpty(S)) return ERROR;
    *x = S->top->data;
    StackNode* temp = S->top;
    S->top = S->top->next;
    free(temp);
    S->size--;
    return OK;
}

Status GetTop(const LinkStack* S, ElementType* x) {
    if (S == NULL || x == NULL || IsEmpty(S)) return ERROR;
    *x = S->top->data;
    return OK;
}

void Clear(LinkStack* S) {
    if (S == NULL) return;
    while (S->top != NULL) {
        StackNode* temp = S->top;
        S->top = S->top->next;
        free(temp);
    }
    S->size = 0;
}

void DestroyStack(LinkStack** pS) {
    if (pS == NULL) return;
    if (*pS == NULL) return;
    Clear(*pS);
    free(*pS);
    *pS = NULL;
}

Status CopyStack(const LinkStack* S, LinkStack* T) {
    if (S == NULL || T == NULL) return ERROR;
    if (IsEmpty(S)) {
        Clear(T);
        return OK;
    }
    LinkStack* new_stack = InitStack();
    if (new_stack == NULL) return ERROR;
    new_stack->size = S->size;
    StackNode* curr = S->top;
    StackNode* new_curr = NULL;
    LinkStack* temp_T = T;
    while (curr != NULL) {
        if (new_curr == NULL) {
            new_curr = (StackNode*)malloc(sizeof(StackNode));
            if (new_curr == NULL) {
                DestroyStack(&new_stack);
                return ERROR;
            }
            new_curr->data = curr->data;
            new_curr->next = NULL;
            new_stack->top = new_curr;
        } else {
            new_curr->next = (StackNode*)malloc(sizeof(StackNode));
            if (new_curr->next == NULL) {
                DestroyStack(&new_stack);
                return ERROR;
            }
            new_curr->next->data = curr->data;
            new_curr->next->next = NULL;
            new_curr = new_curr->next;  
        }
        curr = curr->next;
    }
    Clear(temp_T);
    T->top = new_stack->top;
    T->size = new_stack->size;
    free(new_stack);
    return OK;
}

void PrintStack(const LinkStack* S) {
    if (S == NULL || S->top == NULL) {
        printf("NULL\n");
        return;
    }
    int n = 0;
    for (StackNode* p = S->top; p != NULL; p = p->next) n++;
    ElementType* buf = (ElementType*)malloc(sizeof(ElementType) * (size_t)n);
    if (buf != NULL) {
        StackNode* p = S->top;
        for (int i = n - 1; i >= 0; i--) {
            buf[i] = p->data;
            p = p->next;
        }
        for (int i = 0; i < n - 1; i++) printf("%d ", buf[i]);
        printf("%d\n", buf[n - 1]);
        free(buf);
        return;
    }
    /* malloc 失败时避免崩溃：O(n^2) 按栈底到栈顶输出 */
    for (int i = 0; i < n; i++) {
        StackNode* p = S->top;
        for (int j = 0; j < n - 1 - i; j++) p = p->next;
        if (i > 0) printf(" ");
        printf("%d", p->data);
    }
    printf("\n");
}

Status ReverseStack(LinkStack* S) {
    if (S == NULL) return ERROR;
    if (IsEmpty(S) || S->size == 1) return OK;
    StackNode *next, *curr = S->top, *prev = NULL;
    while (curr != NULL) {
         next = curr->next;
         curr->next = prev;
         prev = curr;
         curr = next;
    }
    S->top = prev;
    return OK;
}

Status GetMin(const LinkStack* S, ElementType* min) {
    if (S == NULL || min == NULL || IsEmpty(S)) return ERROR;
    *min = S->top->data;
    StackNode* curr = S->top->next;
    while (curr != NULL) {
        if (curr->data < *min) *min = curr->data;
        curr = curr->next;
    }
    return OK;
}

Status IsSymmetric(const LinkStack* S) {
    if (S == NULL) return ERROR;
    if (IsEmpty(S)) return OK;
    int *arr = (int *)malloc(sizeof(int) * (int)S->size);
    if (arr == NULL) return ERROR;
    StackNode* curr = S->top;
    for (int i = 0; i < S->size; i++) {
        arr[i] = curr->data;
        curr = curr->next;
    }
    for (int i = 0; i < S->size / 2; i++) {
        if (arr[i] != arr[S->size - i - 1]) {
            free(arr);
            return ERROR;
        }
    }
    free(arr);
    return OK;
}

Status DeleteElem(LinkStack* S, ElementType e) {
    if (S == NULL) return ERROR;
    if (IsEmpty(S)) return OK;
    while (S->top != NULL && S->top->data == e) {
        StackNode* temp = S->top;
        S->top = S->top->next;
        free(temp);
        S->size--;
    }
    if (S->top == NULL) return OK;
    StackNode* curr = S->top;
    while (curr->next != NULL) {
        if (curr->next->data == e) {
            StackNode* temp = curr->next;
            curr->next = curr->next->next;
            free(temp);
            S->size--;
        } else {
            curr = curr->next;
        }
    }
    return OK;
}

static Status AppendStackTo(const LinkStack* S, LinkStack* dest, LinkStack* temp) {
    StackNode* curr = S->top;
    while (curr != NULL) {
        if (Push(temp, curr->data) == ERROR) return ERROR;
        curr = curr->next;
    }
    ElementType x;
    while (!IsEmpty(temp)) {
        Pop(temp, &x);
        if (Push(dest, x) == ERROR) return ERROR;
    }
    return OK;
}

Status MergeStack(const LinkStack* S1, const LinkStack* S2, LinkStack* S3) {
    if (S1 == NULL || S2 == NULL || S3 == NULL) return ERROR;
    LinkStack* new_stack = InitStack();
    if (new_stack == NULL) return ERROR;
    LinkStack* temp = InitStack();
    if (temp == NULL) {
        DestroyStack(&new_stack);
        return ERROR;
    }
    if (AppendStackTo(S1, new_stack, temp) == ERROR) {
        DestroyStack(&new_stack);
        DestroyStack(&temp);
        return ERROR;
    }
    if (AppendStackTo(S2, new_stack, temp) == ERROR) {
        DestroyStack(&new_stack);
        DestroyStack(&temp);
        return ERROR;
    }
    Clear(S3);
    S3->top = new_stack->top;
    S3->size = new_stack->size;
    free(new_stack);
    DestroyStack(&temp);
    return OK;
}

Status RemoveDuplicate(LinkStack* S) {
    if (S == NULL) return ERROR;
    if (IsEmpty(S)) return OK;
    LinkStack* temp = InitStack();
    if (temp == NULL) return ERROR;
    int arr[2005];
    for (int i = 0; i < 2005; i++) {
        arr[i] = 0;
    }
    while (!IsEmpty(S)) {
        ElementType x;
        Pop(S, &x);
        if (Push(temp, x) == ERROR) {
            DestroyStack(&temp);
            return ERROR;
        }
    }
    while (!IsEmpty(temp)) {
        ElementType x;
        Pop(temp, &x);
        if (arr[x + 1000] == 0) {
            arr[x + 1000] = 1;
            if (Push(S, x) == ERROR) {
                DestroyStack(&temp);
                return ERROR;
            }
        }
    }
    DestroyStack(&temp);
    return OK;
}

Status ReverseTop(LinkStack* S, int k) {
    if (S == NULL) return ERROR;
    if (k < 0 || k > S->size) return ERROR;
    LinkStack* temp = InitStack();
    if (temp == NULL) return ERROR;
    for (int i = 0; i < k; i++) {
        ElementType x;
        Pop(S, &x);
        if (Push(temp, x) == ERROR) {
            DestroyStack(&temp);
            return ERROR;
        }
    }
    ReverseStack(temp);
    for (int i = 0; i < k; i++) {
        ElementType x;
        Pop(temp, &x);
        if (Push(S, x) == ERROR) {
            DestroyStack(&temp);
            return ERROR;
        }
    }
    DestroyStack(&temp);
    return OK;
}

Status GetRangeSum(const LinkStack* S, int low, int high, int* sum) {
    if (S == NULL || sum == NULL) return ERROR;
    if (low < 1 || high < low || high > S->size) return ERROR;
    int n = S->size;
    int* arr = (int*)malloc(sizeof(int) * n);
    if (arr == NULL) return ERROR;
    StackNode* curr = S->top;
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = curr->data;
        curr = curr->next;
    }
    int s = 0;
    for (int i = low - 1; i < high; i++)
        s += arr[i];
    free(arr);
    *sum = s;
    return OK;
}

Status InterleaveStack(const LinkStack* S1, const LinkStack* S2, LinkStack* S3) {
    if (S1 == NULL || S2 == NULL || S3 == NULL) return ERROR;

    /* 按链表结点计数（与 InterleaveStack.cpp 中 GetSize 一致，且不依赖可能不同步的 size 域） */
    int n1 = 0;
    for (StackNode* p = S1->top; p != NULL; p = p->next) n1++;
    int n2 = 0;
    for (StackNode* p = S2->top; p != NULL; p = p->next) n2++;
    int n = n1 + n2;

    if (n == 0) {
        Clear(S3);
        return OK;
    }

    ElementType* buf = (ElementType*)malloc(sizeof(ElementType) * (size_t)n);
    if (buf == NULL) return ERROR;

    int i = 0, k = 0;
    StackNode* p1 = S1->top;
    StackNode* p2 = S2->top;

    if (n2 > n1) {
        for (int j = 0; j < n2 - n1; j++) {
            buf[k++] = p2->data;
            p2 = p2->next;
        }
    }
    if (n1 > n2) {
        for (int j = 0; j < n1 - n2; j++) {
            buf[k++] = p1->data;
            p1 = p1->next;
        }
    }
    for (; p1 != NULL || p2 != NULL;) {
        if (i & 1) {
            buf[k++] = p1->data;
            p1 = p1->next;
        } else {
            buf[k++] = p2->data;
            p2 = p2->next;
        }
        i++;
    }

    Clear(S3);
    for (i = 0; i < n; i++) {
        if (Push(S3, buf[i]) == ERROR) {
            free(buf);
            return ERROR;
        }
    }
    free(buf);
    return OK;
}
/*
 * 作业3-B10：仅含题面 7 个函数（与 3784.cpp 中实现一致）
 * 若评测系统已预置类型与 #include，按平台说明只粘贴下方函数体即可。
 */
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

/******************** 7 个函数 ********************/

LinkStack* InitStack(void) {
    LinkStack* S = (LinkStack*)malloc(sizeof(LinkStack));
    if (S == NULL) return NULL;
    S->top = NULL;
    S->size = 0;
    return S;
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

void Clear(LinkStack* S) {
    if (S == NULL) return;
    while (S->top != NULL) {
        StackNode* temp = S->top;
        S->top = S->top->next;
        free(temp);
    }
    S->size = 0;
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
    for (int i = 0; i < n; i++) {
        StackNode* p = S->top;
        for (int j = 0; j < n - 1 - i; j++) p = p->next;
        if (i > 0) printf(" ");
        printf("%d", p->data);
    }
    printf("\n");
}

int GetSize(const LinkStack* S) {
    if (S == NULL) return 0;
    return S->size;
}

void DestroyStack(LinkStack** pS) {
    if (pS == NULL) return;
    if (*pS == NULL) return;
    Clear(*pS);
    free(*pS);
    *pS = NULL;
}

Status InterleaveStack(const LinkStack* S1, const LinkStack* S2, LinkStack* S3) {
    if (S1 == NULL || S2 == NULL || S3 == NULL) return ERROR;

    int n1 = 0;
    for (StackNode* p = S1->top; p != NULL; p = p->next) n1++;
    int n2 = 0;
    for (StackNode* p = S2->top; p != NULL; p = p->next) n2++;
    int total = n1 + n2;

    if (total == 0) {
        Clear(S3);
        return OK;
    }

    ElementType* arr1 = NULL;
    ElementType* arr2 = NULL;
    ElementType* merged = NULL;

    if (n1 > 0) {
        arr1 = (ElementType*)malloc(sizeof(ElementType) * (size_t)n1);
        if (arr1 == NULL) return ERROR;
        StackNode* c = S1->top;
        for (int i = n1 - 1; i >= 0; i--) {
            arr1[i] = c->data;
            c = c->next;
        }
    }
    if (n2 > 0) {
        arr2 = (ElementType*)malloc(sizeof(ElementType) * (size_t)n2);
        if (arr2 == NULL) {
            free(arr1);
            return ERROR;
        }
        StackNode* c = S2->top;
        for (int i = n2 - 1; i >= 0; i--) {
            arr2[i] = c->data;
            c = c->next;
        }
    }
    merged = (ElementType*)malloc(sizeof(ElementType) * (size_t)total);
    if (merged == NULL) {
        free(arr1);
        free(arr2);
        return ERROR;
    }
    {
        int i = 0, j = 0, k = 0;
        while (i < n1 && j < n2) {
            merged[k++] = arr1[i++];
            merged[k++] = arr2[j++];
        }
        while (i < n1) merged[k++] = arr1[i++];
        while (j < n2) merged[k++] = arr2[j++];
    }

    LinkStack* new_stack = InitStack();
    if (new_stack == NULL) {
        free(arr1);
        free(arr2);
        free(merged);
        return ERROR;
    }
    for (int t = 0; t < total; t++) {
        if (Push(new_stack, merged[t]) == ERROR) {
            DestroyStack(&new_stack);
            free(arr1);
            free(arr2);
            free(merged);
            return ERROR;
        }
    }

    Clear(S3);
    S3->top = new_stack->top;
    S3->size = new_stack->size;
    free(new_stack);
    free(arr1);
    free(arr2);
    free(merged);
    return OK;
}

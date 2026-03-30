/*
 * 本地自测 3801：对照题面示例 1～6，不提交评测机。
 * 编译运行：gcc -std=c11 -Wall -Wextra -o /tmp/3801test 3801_local_test.c && /tmp/3801test
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

/* 与 3784.cpp 中 7 个函数保持一致（提交时只交这 7 段） */
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

    int n1 = GetSize(S1);
    int n2 = GetSize(S2);
    int total = n1 + n2;

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
    if (total > 0) {
        merged = (ElementType*)malloc(sizeof(ElementType) * (size_t)total);
        if (merged == NULL) {
            free(arr1);
            free(arr2);
            return ERROR;
        }
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

/* 按「栈底→栈顶」顺序 a[0]..a[n-1]，依次 Push，得到正确链栈 */
static void build_bottom_to_top(LinkStack* S, const int* a, int n) {
    for (int i = 0; i < n; i++) Push(S, a[i]);
}

static int run_one(const char* name, const int* s1, int n1, const int* s2, int n2,
                   const char* expect_line) {
    LinkStack* S1 = InitStack();
    LinkStack* S2 = InitStack();
    LinkStack* S3 = InitStack();
    build_bottom_to_top(S1, s1, n1);
    build_bottom_to_top(S2, s2, n2);

    Status st = InterleaveStack(S1, S2, S3);
    char* buf = NULL;
    size_t len = 0;
    FILE* mem = open_memstream(&buf, &len);
    if (mem == NULL) {
        fprintf(stderr, "open_memstream failed\n");
        DestroyStack(&S1);
        DestroyStack(&S2);
        DestroyStack(&S3);
        return 0;
    }
    /* 复刻 PrintStack 格式，写入内存便于 strcmp */
    if (S3 == NULL || S3->top == NULL) {
        fprintf(mem, "NULL\n");
    } else {
        int n = 0;
        for (StackNode* p = S3->top; p != NULL; p = p->next) n++;
        int* b = (int*)malloc(sizeof(int) * (size_t)n);
        StackNode* p = S3->top;
        for (int i = n - 1; i >= 0; i--) {
            b[i] = p->data;
            p = p->next;
        }
        for (int i = 0; i < n - 1; i++) fprintf(mem, "%d ", b[i]);
        fprintf(mem, "%d\n", b[n - 1]);
        free(b);
    }
    fclose(mem);

    int ok = (st == OK) && buf && (strcmp(buf, expect_line) == 0);
    printf("[%s] %s\n", ok ? "OK" : "FAIL", name);
    if (!ok) {
        printf("  expect (with \\n): %s", expect_line);
        printf("  got   : %s", buf ? buf : "(null)");
        printf("  status: %d\n", (int)st);
    }
    free(buf);

    DestroyStack(&S1);
    DestroyStack(&S2);
    DestroyStack(&S3);
    return ok;
}

int main(void) {
    int fail = 0;

    int e1a[] = {1, 2, 3};
    int e1b[] = {4, 5, 6};
    if (!run_one("例1 等长", e1a, 3, e1b, 3, "1 4 2 5 3 6\n")) fail++;

    int e2a[] = {1, 2, 3, 4, 5};
    int e2b[] = {6, 7};
    if (!run_one("例2 S1较长", e2a, 5, e2b, 2, "1 6 2 7 3 4 5\n")) fail++;

    int e3a[] = {1, 2};
    int e3b[] = {3, 4, 5, 6, 7};
    if (!run_one("例3 S2较长", e3a, 2, e3b, 5, "1 3 2 4 5 6 7\n")) fail++;

    int e4b[] = {1, 2, 3};
    if (!run_one("例4 S1空", NULL, 0, e4b, 3, "1 2 3\n")) fail++;

    int e5a[] = {1, 2, 3};
    if (!run_one("例5 S2空", e5a, 3, NULL, 0, "1 2 3\n")) fail++;

    if (!run_one("例6 都空", NULL, 0, NULL, 0, "NULL\n")) fail++;

    printf("\n总计: %s\n", fail ? "存在失败" : "6/6 与题面一致");
    return fail ? 1 : 0;
}

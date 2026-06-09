#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
#define MAXSIZE 1000

typedef struct {
    ElementType data[MAXSIZE];
    int length;
    int capacity;
} SeqList;

typedef enum { OK = 1, ERROR = 0 } Status;

SeqList* InitList         (void);
Status   PushBack         (SeqList* L,       ElementType x);
void     PrintList        (const SeqList* L);
int      IsEmpty          (const SeqList* L);
int      IsFull           (const SeqList* L);
int      GetLength        (const SeqList* L);
Status   GetElem          (const SeqList* L, int pos,         ElementType* out);
int      LocateElem       (const SeqList* L, ElementType x);
Status   InsertAt         (SeqList* L,       int pos,         ElementType x);
Status   DeleteAt         (SeqList* L,       int pos,         ElementType* deleted);
int      RemoveAll        (SeqList* L,       ElementType x);
int      RemoveRange      (SeqList* L,       ElementType low, ElementType high);
void     Reverse          (SeqList* L);
void     Clear            (SeqList* L);
void     DestroyList      (SeqList** pL);
Status   MergeSortedList  (const SeqList* A, const SeqList* B, SeqList* C);
int      UniqueKeepFirst  (SeqList* L);
void     RotateRight      (SeqList* L, int k);
Status   UnionSortedUnique(const SeqList* A, const SeqList* B, SeqList* C);

/*
cmd 定义（整数，避免字符串解析）：
1 x 0    : push x
2 pos x  : insert pos x
3 pos 0  : delete pos          -> 若成功输出被删元素，否则输出 FAIL_ELEM
4 x 0    : find x              -> 输出位置或 -1
5 pos 0  : get pos             -> 若成功输出元素，否则输出 FAIL_ELEM
6 0 0    : print               -> 输出当前表（空表输出空行）

ExecuteCommand：

- 成功返回 OK，失败返回 ERROR
- find 的结果写到 out_int（失败也可写 -1）
- delete/get 的结果写到 out_elem（失败写 FAIL_ELEM）
*/

Status ExecuteCommand(SeqList* L, int cmd, int a, int b, int* out_int, ElementType* out_elem);

int main()
{
    /*
     * 此处代码由测试程序自动添加，主要用于：
     * 1. 创建和初始化数据结构
     * 2. 调用你实现的函数（可能多次）
     * 3. 输出测试结果
     * 4. 清理资源
     */
    return 0;
}

SeqList* InitList(void) {
    SeqList* L;
    try {
        L = new SeqList;
        // memset(L->data, 0, MAXSIZE);
    } catch (...) {
        return NULL;
    };
    L->length = 0;
    L->capacity = MAXSIZE;
    return L;
}

Status PushBack(SeqList* L, ElementType e) {
    if (L == NULL || L->length >= L->capacity) {
        return ERROR;
    }
    L->data[L->length++] = e;
    return OK;
}

void PrintList(const SeqList* L) {
    if (L == NULL) {
        printf("\n");
    } else {
        for (int i = 0; i < L->length; ++i) {
            printf(i == 0 ? "" : " ");
            printf("%d", L->data[i]);
        }
        printf("\n");
    }
}

int IsEmpty(const SeqList* L) {
    if (L == NULL) return 1;
    if (L->length == 0) return 1;
    return 0;
}

int IsFull(const SeqList* L) {
    if (L == NULL) return 0;
    if (L->length == L->capacity) return 1;
    return 0;
}

int GetLength(const SeqList* L) {
    if (L == NULL) return 0;
    return L->length;
}

Status GetElem(const SeqList* L, int pos, ElementType* out) {
    int FAIL_ELEM = -2147483648;
    *out = FAIL_ELEM;
    if (L == NULL) return ERROR;
    if (out == NULL) return ERROR;
    if (pos < 1 || pos > L->length) return ERROR;
    *out = L->data[pos - 1];
    return OK;
}

int LocateElem(const SeqList* L, ElementType x) {
    if (L == NULL) return -1;
    for (int i = 0; i < L->length; ++i)
        if (L->data[i] == x) return i + 1;
    return -1;
}

Status InsertAt(SeqList* L, int pos, ElementType x) {
    if (L == NULL) return ERROR;
    if (L->length >= L->capacity) return ERROR;
    if (pos < 1 || pos > L->length + 1) return ERROR;
    --pos;
    for (int i = L->length; i > pos; --i)
        L->data[i] = L->data[i - 1];
    L->data[pos] = x;
    ++L->length;
    return OK;
}

Status DeleteAt(SeqList* L, int pos, ElementType* deleted) {
    int FAIL_ELEM = -2147483648;
    *deleted = FAIL_ELEM;
    if (L == NULL) return ERROR;
    if (deleted == NULL) return ERROR;
    if (pos < 1 || pos > L->length) return ERROR;
    *deleted = L->data[pos - 1];
    for (int i = pos - 1; i < L->length - 1; ++i)
        L->data[i] = L->data[i + 1];
    --L->length;
    return OK;
}

int RemoveAll(SeqList* L, ElementType x) {
    if (L == NULL) return 0;
    int new_length = 0;
    for (int i = 0; i < L->length; ++i)
        if (L->data[i] != x)
            L->data[new_length++] = L->data[i];
    int count = L->length - new_length;
    L->length = new_length;
    return count;
}

int RemoveRange(SeqList* L, ElementType low, ElementType high) {
    if (L == NULL) return 0;
    if (low > high) return 0;
    int new_length = 0;
    for (int i = 0; i < L->length; ++i)
        if (L->data[i] < low || L->data[i] > high)
            L->data[new_length++] = L->data[i];
    int count = L->length - new_length;
    L->length = new_length;
    return count;
}

void Reverse(SeqList* L) {
    if (L == NULL) return;
    for (int i = 0; i < L->length / 2; i++){
        ElementType temp = L->data[i];
        L->data[i] = L->data[L->length - 1 - i];
        L->data[L->length - 1 - i] = temp;
    }
}

void Clear(SeqList* L) {
    if (L == NULL) return;
    L->length = 0;
}

void DestroyList(SeqList** pL) {
    if (pL == NULL) return;
    if (*pL == NULL) return;
    free(*pL);
    *pL = NULL;
}

Status MergeSortedList(const SeqList* A, const SeqList* B, SeqList* C) {
    if (A == NULL || B == NULL || C == NULL) return ERROR;
    if (A->length + B->length > C->capacity) return ERROR;
    int i = 0, j = 0, k = 0;
    while (i < A->length && j < B->length) {
        if (A->data[i] < B->data[j]) {
            C->data[k++] = A->data[i++];
        } else {
            C->data[k++] = B->data[j++];
        }
    }
    while (i < A->length) {
        C->data[k++] = A->data[i++];
    }
    while (j < B->length) {
        C->data[k++] = B->data[j++];
    }
    C->length = k;
    return OK;
}

int UniqueKeepFirst(SeqList* L) {
    if (L == NULL) return 0;
    if (L->length == 0) return 0;
    int new_length = 1;
    for (int i = 1; i < L->length; ++i) {
        int is_duplicate = 0;
        for (int j = 0; j < new_length; ++j) {
            if (L->data[i] == L->data[j]) {
                is_duplicate = 1;
                break;
            }
        }
        if (!is_duplicate) {
            L->data[new_length++] = L->data[i];
        }
    }
    int count = L->length - new_length;
    L->length = new_length;
    return count;
}

void RotateRight(SeqList* L, int k) {
    if (L == NULL) return;
    if (k < 0) return;
    if (L->length <= 1) return;
    k = k % L->length;
    for (int i = 0; i < k; ++i) {
        ElementType temp = L->data[L->length - 1];
        for (int j = L->length - 1; j > 0; --j)
            L->data[j] = L->data[j - 1];
        L->data[0] = temp;
    }
}

Status UnionSortedUnique(const SeqList* A, const SeqList* B, SeqList* C) {
    if (A == NULL || B == NULL || C == NULL) return ERROR;
    int total = A->length + B->length;
    if (total == 0) {
        C->length = 0;
        return OK;
    }
    ElementType* tmp = (ElementType*)malloc((size_t)total * sizeof(ElementType));
    if (tmp == NULL) return ERROR;
    int i = 0, j = 0, k = 0;
    while (i < A->length && j < B->length) {
        ElementType cand = A->data[i] < B->data[j] ? A->data[i++] : B->data[j++];
        if (k == 0 || cand != tmp[k - 1])
            tmp[k++] = cand;
    }
    while (i < A->length) {
        ElementType cand = A->data[i++];
        if (k == 0 || cand != tmp[k - 1])
            tmp[k++] = cand;
    }
    while (j < B->length) {
        ElementType cand = B->data[j++];
        if (k == 0 || cand != tmp[k - 1])
            tmp[k++] = cand;
    }
    if (k > C->capacity) {
        free(tmp);
        return ERROR;
    }
    for (int t = 0; t < k; ++t)
        C->data[t] = tmp[t];
    C->length = k;
    free(tmp);
    return OK;
}


Status ExecuteCommand(SeqList* L, int cmd, int a, int b, int* out_int, ElementType* out_elem) {
    if (L == NULL) return ERROR;
    if (out_int == NULL) return ERROR;
    if (out_elem == NULL) return ERROR;
    if (cmd == 1) return PushBack(L, a);
    else if (cmd == 2) return InsertAt(L, a, b);
    else if (cmd == 3) return DeleteAt(L, a, out_elem);
    else if (cmd == 4) *out_int = LocateElem(L, a);
    else if (cmd == 5) return GetElem(L, a, out_elem);
    else if (cmd == 6) PrintList(L);
    else return ERROR;
    return OK;
}

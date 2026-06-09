#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/******************** 数据结构定义（与题面完全一致） ********************/
typedef int ElementType;

typedef struct {
    ElementType* data;
    int length;
    int capacity;
} SeqList;

typedef enum { OK = 1, ERROR = 0 } Status;

/******************** 函数声明（本题要求实现） ********************/
SeqList* InitList(void);
Status   PushBack(SeqList* L, ElementType x);
Status   ExpandCapacity(SeqList* L, int newCapacity);
void     PrintList(const SeqList* L);
int      IsEmpty(const SeqList* L);
int      IsFull(const SeqList* L);
int      GetLength(const SeqList* L);
Status   GetElem(const SeqList* L, int pos, ElementType* out);
int      LocateElem(const SeqList* L, ElementType x);
Status   InsertAt(SeqList* L, int pos, ElementType x);
Status   DeleteAt(SeqList* L, int pos, ElementType* deleted);
int      RemoveAll(SeqList* L, ElementType x);
void     Reverse(SeqList* L);
void     Clear(SeqList* L);
void     DestroyList(SeqList** pL);
Status   InsertRange(SeqList* L, int pos, const ElementType* arr, int count);
Status   MergeLists(SeqList* dest, SeqList** sources, int count);
Status   DeleteRange(SeqList* L, int start, int end, int shrink);
Status   UniqueAndCompress(SeqList* L);
int      CountAndUpdate(SeqList* L, int start, int end, ElementType threshold, ElementType newValue);
Status   RotateLeft(SeqList* L, int k);

/******************** 主函数 ********************/
int main()
{
    /*
     * 此处代码由测试程序自动添加，主要用于：
     * 1. 创建和初始化数据结构
     * 2. 插入测试数据
     * 3. 调用你实现的函数
     * 4. 输出测试结果
     * 5. 清理资源（销毁数据结构）
     *
     * 你无需关心此处代码的具体实现细节。
     */
    return 0;
}

/******************** 函数实现 ********************/
/*
 * 请在下方实现题目要求的函数
 * 你的代码将被添加在此处
 */

SeqList* InitList(void) {
    SeqList* L = (SeqList*)malloc(sizeof(SeqList));
    if (L == NULL) return NULL;
    L->data = (ElementType*)malloc(10 * sizeof(ElementType));
    if (L->data == NULL) {
        free(L);
        return NULL;
    }
    L->length = 0;
    L->capacity = 10;
    return L;
}

Status ExpandCapacity(SeqList* L, int newCapacity) {
    if (L == NULL || L->data == NULL || newCapacity < 0) return ERROR;
    if (newCapacity <= L->capacity) return OK;
    ElementType* new_data = (ElementType*)realloc(L->data, newCapacity * sizeof(ElementType));
    if (new_data == NULL) return ERROR;
    L->capacity = newCapacity;
    L->data = new_data;
    return OK;
}

Status PushBack(SeqList* L, ElementType x) {
    if (L == NULL) return ERROR;
    if (L->length >= L->capacity && ExpandCapacity(L, L->capacity * 2) == ERROR) return ERROR;
    L->data[L->length++] = x;
    return OK;
}

void PrintList(const SeqList* L) {
    if (L == NULL || L->data == NULL) {
        printf("-1\n");
        return;
    }
    for (int i = 0; i < L->length; i++) printf(i == 0 ? "%d" : " %d", L->data[i]);
    printf("\n");
}

int IsEmpty(const SeqList* L) {
    if (L == NULL) return 1;
    return L->length == 0;
}

int IsFull(const SeqList* L) {
    return 0;
}

int GetLength(const SeqList* L) {
    if (L == NULL) return 0;
    return L->length;
}

Status GetElem(const SeqList* L, int pos, ElementType* out) {
    int FAIL_ELEM = -2147483648;
    *out = FAIL_ELEM;
    if (L == NULL || out == NULL || pos < 1 || pos > L->length) return ERROR;
    *out = L->data[pos - 1];
    return OK;
}

int LocateElem(const SeqList* L, ElementType x) {
    if (L == NULL) return -1;
    for (int i = 0; i < L->length; i++) if (L->data[i] == x) return i + 1;
    return -1;
}

Status InsertAt(SeqList* L, int pos, ElementType x) {
    if (L == NULL || pos < 1 || pos > L->length + 1) return ERROR;
    if (L->length >= L->capacity && ExpandCapacity(L, L->capacity * 2) == ERROR) return ERROR;
    for (int i = L->length; i > pos - 1; i--) L->data[i] = L->data[i - 1];
    L->data[pos - 1] = x;
    L->length++;
    return OK;
}

Status DeleteAt(SeqList* L, int pos, ElementType* deleted) {
    int FAIL_ELEM = -2147483648;
    *deleted = FAIL_ELEM;
    if (L == NULL || deleted == NULL || pos < 1 || pos > L->length) return ERROR;
    *deleted = L->data[pos - 1];
    for (int i = pos - 1; i < L->length - 1; i++) L->data[i] = L->data[i + 1];
    L->length--;
    return OK;
}

int RemoveAll(SeqList* L, ElementType x) {
    if (L == NULL) return 0;
    int cnt = 0;
    for (int i = 0; i < L->length; ++i)
        if (L->data[i] == x)
            cnt++;
        else 
            L->data[i - cnt] = L->data[i];
    L->length -= cnt;
    return cnt;
}

void Reverse(SeqList* L) {
    if (L == NULL) return;
    for (int i = 0; i < L->length / 2; ++i) {
        ElementType temp = L->data[i];
        L->data[i] = L->data[L->length - i - 1];
        L->data[L->length - i - 1] = temp;
    }
}

void Clear(SeqList* L) {
    if (L == NULL) return;
    L->length = 0;
}

void DestroyList(SeqList** pL) {
    if (pL == NULL) return;
    if (*pL == NULL) return;
    if ((*pL)->data != NULL) free((*pL)->data);
    free(*pL);
    *pL = NULL;
}

Status InsertRange(SeqList* L, int pos, const ElementType* arr, int count) {
    if (L == NULL || L->data == NULL) return ERROR;
    if (count > 0 && arr == NULL) return ERROR;
    if (pos < 0 || pos > L->length) return ERROR;
    if (count < 0) return ERROR;
    int need = L->capacity * 2;
    if (count > L->capacity)
        need = count + L->capacity;
    if (count + L->length > L->capacity && ExpandCapacity(L, need) == ERROR) return ERROR;
    for (int i = L->length - 1; i >= pos; --i)
        L->data[i + count] = L->data[i];
    for (int i = pos; i < pos + count; i++)
        L->data[i] = arr[i - pos];
    L->length += count;
    return OK;
}

Status MergeLists(SeqList* dest, SeqList** sources, int count) {
    if (dest == NULL || dest->data == NULL) return ERROR;
    if (count > 0 && sources == NULL) return ERROR;
    if (count < 0) return ERROR;

    if (count == 0) {
        dest->length = 0;
        return OK;
    }

    int need = 0;
    for (int i = 0; i < count; ++i) {
        if (sources[i] == NULL || sources[i]->data == NULL)
            return ERROR;
        need += sources[i]->length;
    }

    if (dest->capacity < need) {
        int newCap = dest->capacity;
        while (newCap < need) newCap *= 2;
        if (ExpandCapacity(dest, newCap) == ERROR) return ERROR;
    }

    dest->length = 0;
    for (int i = 0; i < count; ++i)
        for (int j = 0; j < sources[i]->length; ++j)
            dest->data[dest->length++] = sources[i]->data[j];
    return OK;
}

Status DeleteRange(SeqList* L, int start, int end, int shrink) {
    if (L == NULL || L->data == NULL) return ERROR;
    if (start < 0 || end >= L->length || start > end) return ERROR;

    int del_count = end - start + 1;
    int new_length = L->length - del_count;

    int new_cap = L->capacity;
    if (shrink != 0 && new_length <= L->capacity / 4) {
        new_cap = L->capacity / 2;
        if (new_cap < 10) new_cap = 10;
        if (new_cap < L->capacity) {
            ElementType* new_data = (ElementType*)malloc((size_t)new_cap * sizeof(ElementType));
            if (new_data == NULL) return ERROR;
            memmove(L->data + start, L->data + end + 1, (size_t)(L->length - end - 1) * sizeof(ElementType));
            L->length = new_length;
            memcpy(new_data, L->data, (size_t)new_length * sizeof(ElementType));
            free(L->data);
            L->data = new_data;
            L->capacity = new_cap;
            return OK;
        }
    }

    memmove(L->data + start, L->data + end + 1, (size_t)(L->length - end - 1) * sizeof(ElementType));
    L->length = new_length;
    return OK;
}

Status UniqueAndCompress(SeqList* L) {
    if (L == NULL || L->data == NULL) return ERROR;
    ElementType* new_data = (ElementType*)malloc(L->length * sizeof(ElementType));
    if (new_data == NULL) return ERROR;
    int idx = 0;
    for (int i = 0; i < L->length; ++i) {
        if (i == 0 || L->data[i] != L->data[i - 1]) {
            new_data[idx++] = L->data[i];
        }
    }
    int new_cap = idx >= 10 ? idx : 10;
    ElementType* tmp = (ElementType*)realloc(new_data, new_cap * sizeof(ElementType));
    if (tmp == NULL) {
        free(new_data);
        return ERROR;
    }
    new_data = tmp;
    free(L->data);
    L->data = new_data;
    L->length = idx;
    L->capacity = new_cap;
    return OK;
}

int CountAndUpdate(SeqList* L, int start, int end, ElementType threshold, ElementType newValue) {
    if (L == NULL || L->data == NULL) return -1;
    if (start < 0 || end >= L->length || start > end) return -1;
    int count = 0;
    for (int i = start; i <= end; ++i) {
        if (L->data[i] >= threshold) {
            count++;
            L->data[i] = newValue;
        }
    }
    return count;
}

Status RotateLeft(SeqList* L, int k) {
    if (L == NULL || L->data == NULL) return ERROR;
    if (k < 0) return ERROR;
    if (k == 0 || L->length <= 1) return OK;
    k = k % L->length;
    if (k == 0) return OK;
    int low, high, len;
    low = 0; high = k - 1; len = high - low + 1;
    for (int i = 0; i < len / 2; ++i) {
        ElementType temp = L->data[low + i]; L->data[low + i] = L->data[high - i]; L->data[high - i] = temp;
    }
    low = k; high = L->length - 1; len = high - low + 1;
    for (int i = 0; i < len / 2; ++i) {
        ElementType temp = L->data[low + i]; L->data[low + i] = L->data[high - i]; L->data[high - i] = temp;
    }
    low = 0; high = L->length - 1; len = high - low + 1;
    for (int i = 0; i < len / 2; ++i) {
        ElementType temp = L->data[low + i]; L->data[low + i] = L->data[high - i]; L->data[high - i] = temp;
    }
    return OK;
}
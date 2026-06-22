#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int  size;
    int  capacity;
} MinHeap;

typedef struct {
    int min_val;   /* 堆中最小元素值 */
    int max_val;   /* 堆中最大元素值 */
    int sum;       /* 堆中所有元素之和 */
    int count;     /* 堆中元素个数 */
} HeapStatResult;

MinHeap* CreateMinHeap(int capacity);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

MinHeap* CreateMinHeap(int capacity) {
    if (capacity <= 0) return NULL;
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    if (heap == NULL) return NULL;
    /* 1-based：data[0] 不用，有效下标 1..capacity */
    heap->data = (int*)malloc(sizeof(int) * (capacity + 1));
    if (heap->data == NULL) {
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

int IsEmpty(MinHeap* h) {
    if (h == NULL || h->size == 0) return 1;
    return 0;
}

int IsFull(MinHeap* h) {
    if (h->size == h->capacity) return 1;
    return 0;
}

void SiftUp(MinHeap* h, int i) {
    if (h == NULL || h->data == NULL || i <= 1) return;
    int parent = i / 2;
    if (h->data[i] >= h->data[parent]) return;
    int temp = h->data[parent];
    h->data[parent] = h->data[i];
    h->data[i] = temp;
    SiftUp(h, parent);
}

void SiftDown(MinHeap* h, int i) {
    if (h == NULL || h->data == NULL || h->size == 0 || i < 1 || i > h->size) return;
    int left = 2 * i;
    int right = 2 * i + 1;
    int smallest = i;
    if (left <= h->size && h->data[left] < h->data[smallest]) smallest = left;
    if (right <= h->size && h->data[right] < h->data[smallest]) smallest = right;
    if (smallest != i) {
        int temp = h->data[i];
        h->data[i] = h->data[smallest];
        h->data[smallest] = temp;
        SiftDown(h, smallest);
    }
}

int Insert(MinHeap* h, int val) {
    if (h == NULL || IsFull(h)) return 0;
    h->size++;
    h->data[h->size] = val;
    SiftUp(h, h->size);
    return 1;
}

void PrintHeap(MinHeap* h) {
    if (h == NULL || IsEmpty(h)) return;
    for (int i = 1; i <= h->size; i++) {
        if (i > 1) printf(" ");
        printf("%d", h->data[i]);
    }
    printf("\n");
}

int GetMin(MinHeap* h) {
    if (h == NULL || IsEmpty(h)) return -1;
    return h->data[1];
}

int GetSize(MinHeap* h) {
    if (h == NULL || h->data == NULL) return 0;
    return h->size;
}

int DeleteMin(MinHeap* h) {
    if (h == NULL || IsEmpty(h)) return -1;
    int min = h->data[1];
    h->data[1] = h->data[h->size];
    h->size--;
    SiftDown(h, 1);
    return min;
}

MinHeap* BuildHeap(int arr[], int n, int capacity) {
    if (arr == NULL || n <= 0 || capacity < n) return NULL;
    MinHeap* heap = CreateMinHeap(capacity);
    if (heap == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        heap->data[i + 1] = arr[i];
    }
    heap->size = n;
    for (int i = n / 2; i >= 1; i--) {
        SiftDown(heap, i);
    }
    return heap;
}

void HeapSort(MinHeap* h, int* result) {
    if (h == NULL || result == NULL) return;
    int n = h->size;
    for (int i = 0; i < n; i++) {
        result[i] = DeleteMin(h);
    }
}

int Contains(MinHeap* h, int val) {
    if (h == NULL || IsEmpty(h)) return 0;
    for (int i = 1; i <= h->size; i++) {
        if (h->data[i] == val) return 1;
    }
    return 0;
}

void DestroyMinHeap(MinHeap** ph) {
    if (ph == NULL || *ph == NULL) return;
    free((*ph)->data);
    free(*ph);
    *ph = NULL;
}

int ReplaceMin(MinHeap* h, int val) {
    if (h == NULL || IsEmpty(h) || Contains(h, val)) return 0;
    h->data[1] = val;
    SiftDown(h, 1);
    return 1;
}

int GetKMin(MinHeap* h, int k, int* result) {
    if (h == NULL || result == NULL || IsEmpty(h)) return 0;
    if (k <= 0) return 0;
    int count = k;
    if (count > h->size) count = h->size;
    for (int i = 0; i < count; i++) {
        result[i] = DeleteMin(h);
    }
    return count;
}

MinHeap* BuildHeapUnique(int arr[], int n) {
    if (arr == NULL || n <= 0) return NULL;
    int seen[256] = {0};
    int vals[200];
    int m = 0;
    for (int i = 0; i < n; i++) {
        int v = arr[i];
        if (v < 0 || v >= 256) continue;
        if (!seen[v]) {
            seen[v] = 1;
            vals[m++] = v;
        }
    }
    if (m == 0) return NULL;
    return BuildHeap(vals, m, m);
}

MinHeap* MergeHeap(MinHeap* h1, MinHeap* h2) {
    int empty1 = (h1 == NULL || h1->size == 0);
    int empty2 = (h2 == NULL || h2->size == 0);
    if (empty1 && empty2) return NULL;

    int s1 = empty1 ? 0 : h1->size;
    int s2 = empty2 ? 0 : h2->size;
    int total = s1 + s2;

    int* vals = (int*)malloc(sizeof(int) * total);
    if (vals == NULL) return NULL;

    int k = 0;
    if (!empty1) {
        for (int i = 1; i <= h1->size; i++) {
            vals[k++] = h1->data[i];
        }
    }
    if (!empty2) {
        for (int i = 1; i <= h2->size; i++) {
            vals[k++] = h2->data[i];
        }
    }

    MinHeap* heap = BuildHeap(vals, total, total);
    free(vals);
    return heap;
}

int FindKth(MinHeap* h, int k) {
    if (h == NULL || h->size == 0 || k <= 0 || k > h->size) return -1;

    int n = h->size;
    int* data = (int*)malloc(sizeof(int) * (n + 1));
    if (data == NULL) return -1;

    for (int i = 1; i <= n; i++) {
        data[i] = h->data[i];
    }

    MinHeap temp;
    temp.data = data;
    temp.size = n;
    temp.capacity = n;

    int result = -1;
    for (int i = 0; i < k; i++) {
        result = DeleteMin(&temp);
    }

    free(data);
    return result;
}

void HeapStats(MinHeap* h, HeapStatResult* result) {
    if (result == NULL) return;
    if (h == NULL || h->size == 0) {
        result->min_val = -1;
        result->max_val = -1;
        result->sum = 0;
        result->count = 0;
        return;
    }
    int min_val = h->data[1];
    int max_val = h->data[1];
    int sum = 0;
    for (int i = 1; i <= h->size; i++) {
        int v = h->data[i];
        if (v < min_val) min_val = v;
        if (v > max_val) max_val = v;
        sum += v;
    }
    result->min_val = min_val;
    result->max_val = max_val;
    result->sum = sum;
    result->count = h->size;
}

int DeleteIf(MinHeap* h, int threshold) {
    if (h == NULL || h->size == 0) return 0;

    int deleted = 0;
    int write = 1;
    for (int i = 1; i <= h->size; i++) {
        if (h->data[i] > threshold) {
            deleted++;
        } else {
            h->data[write++] = h->data[i];
        }
    }
    if (deleted == 0) return 0;

    h->size = write - 1;
    if (h->size > 0) {
        for (int i = h->size / 2; i >= 1; i--) {
            SiftDown(h, i);
        }
    }
    return deleted;
}

int IsMinHeap(int arr[], int n) {
    if (arr == NULL || n <= 0) return 1;
    for (int i = 1; i <= n / 2; i++) {
        int left = 2 * i;
        int right = 2 * i + 1;
        if (left <= n && arr[i] > arr[left]) return 0;
        if (right <= n && arr[i] > arr[right]) return 0;
    }
    return 1;
}

MinHeap* FromSortedArray(int arr[], int n) {
    if (arr == NULL || n <= 0) return NULL;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] >= arr[i + 1]) return NULL;
    }
    return BuildHeap(arr, n, n);
}
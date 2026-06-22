#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* data;
    int  size;
    int  capacity;
} MaxHeap;

MaxHeap* CreateMaxHeap(int capacity);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

MaxHeap* CreateMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->data = (int*)malloc(sizeof(int) * (capacity + 1));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

int IsEmpty(MaxHeap* h) {
    if (h == NULL || h->size == 0) return 1;
    return 0;
}

int IsFull(MaxHeap* h) {
    if (h == NULL) return 0;
    if (h->size >= h->capacity) return 1;
    return 0;
}

void SiftUp(MaxHeap* h, int i) {
    if (h == NULL || h->data == NULL || i <= 1) return;
    int parent = i / 2;
    if (h->data[i] <= h->data[parent]) return;
    int temp = h->data[parent];
    h->data[parent] = h->data[i];
    h->data[i] = temp;
    SiftUp(h, parent);
}

int Insert(MaxHeap* h, int val) {
    if (h == NULL || IsFull(h)) return 0;
    h->size++;
    h->data[h->size] = val;
    SiftUp(h, h->size);
    return 1;
}

int GetMax(MaxHeap* h) {
    if (h == NULL || IsEmpty(h)) return -1;
    return h->data[1];
}

int GetSize(MaxHeap* h) {
    if (h == NULL) return 0;
    return h->size;
}

void SiftDown(MaxHeap* h, int i) {
    if (h == NULL || h->data == NULL || h->size == 0 || i < 1 || i > h->size) return;
    int left = 2 * i;
    int right = 2 * i + 1;
    int largest = i;
    if (left <= h->size && h->data[left] > h->data[largest]) largest = left;
    if (right <= h->size && h->data[right] > h->data[largest]) largest = right;
    if (largest != i) {
        int temp = h->data[i];
        h->data[i] = h->data[largest];
        h->data[largest] = temp;
        SiftDown(h, largest);
    }
}

int DeleteMax(MaxHeap* h) {
    if (h == NULL || IsEmpty(h)) return -1;
    int max = h->data[1];
    h->data[1] = h->data[h->size];
    h->size--;
    SiftDown(h, 1);
    return max;
}

MaxHeap* BuildHeap(int arr[], int n, int capacity) {
    if (arr == NULL || n <= 0 || capacity < n) return NULL;
    MaxHeap* heap = CreateMaxHeap(capacity);
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

void HeapSort(MaxHeap* h, int* result) {
    if (h == NULL || result == NULL) return;
    int n = h->size;
    for (int i = 0; i < n; i++) {
        result[i] = DeleteMax(h);
    }
}

int Contains(MaxHeap* h, int val) {
    if (h == NULL || IsEmpty(h)) return 0;
    for (int i = 1; i <= h->size; i++) {
        if (h->data[i] == val) return 1;
    }
    return 0;
}

void DestroyMaxHeap(MaxHeap** ph) {
    if (ph == NULL || *ph == NULL) return;
    free((*ph)->data);
    free(*ph);
    *ph = NULL;
}
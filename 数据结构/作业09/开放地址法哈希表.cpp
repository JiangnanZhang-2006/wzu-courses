#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 1, ERROR = 0 } Status;
typedef enum { EMPTY = 0, OCCUPIED = 1, DELETED = 2 } SlotState;

typedef struct {
    int       key;
    int       value;
    SlotState state;
} Slot;

typedef struct {
    Slot* slots;
    int   size;
    int   count;
    int   deleted;
} OAHashTable;

OAHashTable* CreateTable(int size);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

OAHashTable* CreateTable(int size) {
    if (size <= 0) return NULL;
    OAHashTable* ht = (OAHashTable*)malloc(sizeof(OAHashTable));
    if (ht == NULL) return NULL;
    ht->slots = (Slot*)malloc(sizeof(Slot) * size);
    if (ht->slots == NULL) {
        free(ht);
        return NULL;
    }
    ht->size = size;
    ht->count = 0;
    ht->deleted = 0;
    for (int i = 0; i < size; i++) {
        ht->slots[i].state = EMPTY;
    }
    return ht;
}

int HashFunc(OAHashTable* ht, int key) {
    if (ht == NULL) return -1;
    return abs(key) % ht->size;
}

int Probe(OAHashTable* ht, int key, int i) {
    if (ht == NULL || i < 0) return -1;
    return (HashFunc(ht, key) + i * i) % ht->size;
}

Status Insert(OAHashTable* ht, int key, int value) {
    if (ht == NULL) return ERROR;

    int firstDeleted = -1;
    for (int i = 0; i < ht->size; i++) {
        int index = Probe(ht, key, i);
        if (index == -1) return ERROR;

        if (ht->slots[index].state == OCCUPIED) {
            if (ht->slots[index].key == key) {
                ht->slots[index].value = value;
                return ERROR;
            }
            continue;
        }

        if (ht->slots[index].state == DELETED) {
            if (firstDeleted == -1) firstDeleted = index;
            continue;
        }

        ht->slots[index].key = key;
        ht->slots[index].value = value;
        ht->slots[index].state = OCCUPIED;
        ht->count++;
        return OK;
    }

    if (firstDeleted != -1) {
        ht->slots[firstDeleted].key = key;
        ht->slots[firstDeleted].value = value;
        ht->slots[firstDeleted].state = OCCUPIED;
        ht->deleted--;
        ht->count++;
        return OK;
    }

    return ERROR;
}

int Search(OAHashTable* ht, int key) {
    if (ht == NULL) return -1;
    for (int i = 0; i < ht->size; i++) {
        int index = Probe(ht, key, i);
        if (index == -1) return -1;

        if (ht->slots[index].state == EMPTY) return -1;

        if (ht->slots[index].state == OCCUPIED && ht->slots[index].key == key)
            return index;
    }
    return -1;
}

int GetValue(OAHashTable* ht, int key) {
    if (ht == NULL) return -1;
    int index = Search(ht, key);
    if (index == -1) return -1;
    return ht->slots[index].value;
}

Status Delete(OAHashTable* ht, int key) {
    if (ht == NULL) return ERROR;
    int index = Search(ht, key);
    if (index == -1) return ERROR;
    ht->slots[index].state = DELETED;
    ht->count--;
    ht->deleted++;
    return OK;
}

int Contains(OAHashTable* ht, int key) {
    if (ht == NULL) return 0;
    return Search(ht, key) != -1 ? 1 : 0;
}

int GetCount(OAHashTable* ht) {
    if (ht == NULL) return 0;
    return ht->count;
}

int GetDeletedCount(OAHashTable* ht) {
    if (ht == NULL) return 0;
    return ht->deleted;
}

int GetSlotState(OAHashTable* ht, int index) {
    if (ht == NULL || index < 0 || index >= ht->size) return -1;
    return (int)ht->slots[index].state;
}

float GetLoadFactor(OAHashTable* ht) {
    if (ht == NULL || ht->size == 0) return 0.0f;
    return (float)ht->count / (float)ht->size;
}

Status Resize(OAHashTable* ht, int newSize) {
    if (ht == NULL || newSize <= 0) return ERROR;

    int n = ht->count;
    int* keys = (int*)malloc(sizeof(int) * n);
    int* values = (int*)malloc(sizeof(int) * n);
    if (keys == NULL || values == NULL) {
        free(keys);
        free(values);
        return ERROR;
    }

    int idx = 0;
    for (int i = 0; i < ht->size; i++) {
        if (ht->slots[i].state == OCCUPIED) {
            keys[idx] = ht->slots[i].key;
            values[idx] = ht->slots[i].value;
            idx++;
        }
    }

    free(ht->slots);
    ht->slots = (Slot*)malloc(sizeof(Slot) * newSize);
    if (ht->slots == NULL) {
        free(keys);
        free(values);
        return ERROR;
    }

    ht->size = newSize;
    ht->deleted = 0;
    ht->count = 0;
    for (int i = 0; i < newSize; i++) {
        ht->slots[i].state = EMPTY;
    }

    for (int i = 0; i < n; i++) {
        Insert(ht, keys[i], values[i]);
    }

    free(keys);
    free(values);
    return OK;
}

void GetAllKeys(OAHashTable* ht, int* keys, int* cnt) {
    if (ht == NULL) {
        *cnt = 0;
        return;
    }
    if (keys == NULL || cnt == NULL) return;

    *cnt = 0;
    for (int i = 0; i < ht->size; i++) {
        if (ht->slots[i].state == OCCUPIED) {
            keys[*cnt] = ht->slots[i].key;
            (*cnt)++;
        }
    }
    for (int i = 0; i < *cnt - 1; i++) {
        for (int j = i + 1; j < *cnt; j++) {
            if (keys[i] > keys[j]) {
                int tmp = keys[i];
                keys[i] = keys[j];
                keys[j] = tmp;
            }
        }
    }
}

void DestroyTable(OAHashTable** pht) {
    if (pht == NULL || *pht == NULL) return;
    OAHashTable* ht = *pht;
    free(ht->slots);
    free(ht);
    *pht = NULL;
}
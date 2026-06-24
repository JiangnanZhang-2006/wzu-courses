#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct HashNode {
    int key;
    int value;
    struct HashNode* next;
} HashNode;

typedef struct {
    HashNode** buckets;
    int size;
    int count;
} HashTable;

HashNode* CreateNode(int key, int value);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

static HashNode* htCreateNode(int key, int value) {
    HashNode* node = (HashNode*)malloc(sizeof(HashNode));
    if (node == NULL) return NULL;
    node->key = key;
    node->value = value;
    node->next = NULL;
    return node;
}

HashNode* CreateNode(int key, int value) {
    return htCreateNode(key, value);
}

HashTable* CreateTable(int size) {
    if (size <= 0) return NULL;
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) return NULL;
    table->buckets = (HashNode**)malloc(sizeof(HashNode*) * size);
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    table->size = size;
    table->count = 0;
    return table;
}

static int htHashFunc(HashTable* ht, int key) {
    if (ht == NULL) return -1;
    return abs(key) % ht->size;
}

int HashFunc(HashTable* ht, int key) {
    return htHashFunc(ht, key);
}

Status Insert(HashTable* ht, int key, int value) {
    if (ht == NULL) return ERROR;
    int index = htHashFunc(ht, key);
    if (index == -1) return ERROR;
    HashNode* node = htCreateNode(key, value);
    if (node == NULL) return ERROR;
    HashNode* cur = ht->buckets[index];
    while (cur != NULL) {
        if (cur->key == key) {
            cur->value = value;
            return ERROR;
        }
        cur = cur->next;
    }

    node->next = ht->buckets[index];
    ht->buckets[index] = node;
    ht->count++;
    return OK;
}

static HashNode* htSearch(HashTable* ht, int key) {
    if (ht == NULL) return NULL;
    int index = htHashFunc(ht, key);
    if (index == -1) return NULL;
    HashNode* cur = ht->buckets[index];
    while (cur != NULL) {
        if (cur->key == key) return cur;
        cur = cur->next;
    }
    return NULL;
}

HashNode* Search(HashTable* ht, int key) {
    return htSearch(ht, key);
}

int GetValue(HashTable* ht, int key) {
    if (ht == NULL) return -1;
    HashNode* node = htSearch(ht, key);
    if (node == NULL) return -1;
    return node->value;
}

Status Delete(HashTable* ht, int key) {
    if (ht == NULL) return ERROR;
    int index = htHashFunc(ht, key);
    if (index == -1) return ERROR;
    HashNode* cur = ht->buckets[index];
    HashNode* prev = NULL;
    while (cur != NULL) {
        if (cur->key == key) {
            if (prev == NULL) {
                ht->buckets[index] = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            ht->count--;
            return OK;
        }
        prev = cur;
        cur = cur->next;
    }
    return ERROR;
}

int Contains(HashTable* ht, int key) {
    if (ht == NULL) return 0;
    HashNode* node = htSearch(ht, key);
    if (node == NULL) return 0;
    return 1;
}

int GetCount(HashTable* ht) {
    if (ht == NULL) return 0;
    return ht->count;
}

int GetBucketSize(HashTable* ht) {
    if (ht == NULL) return 0;
    return ht->size;
}

float GetLoadFactor(HashTable* ht) {
    if (ht == NULL || ht->size == 0) return 0.0f;
    return (float)ht->count / ht->size;
}

static int htGetChainLength(HashTable* ht, int index) {
    if (ht == NULL || index < 0 || index >= ht->size) return -1;
    int length = 0;
    HashNode* cur = ht->buckets[index];
    while (cur != NULL) {
        length++;
        cur = cur->next;
    }
    return length;
}

int GetChainLength(HashTable* ht, int index) {
    return htGetChainLength(ht, index);
}

int GetMaxChainLength(HashTable* ht) {
    if (ht == NULL) return 0;
    int maxLength = 0;
    for (int i = 0; i < ht->size; i++) {
        int length = htGetChainLength(ht, i);
        if (length > maxLength) maxLength = length;
    }
    return maxLength;
}

static HashTable* htCreateTable(int size) {
    if (size <= 0) return NULL;
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) return NULL;
    table->buckets = (HashNode**)malloc(sizeof(HashNode*) * size);
    if (table->buckets == NULL) {
        free(table);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        table->buckets[i] = NULL;
    }
    table->size = size;
    table->count = 0;
    return table;
}

Status Resize(HashTable* ht, int newSize) {
    if (ht == NULL || newSize <= 0) return ERROR;
    if (newSize == ht->size) return OK;
    HashTable* newTable = htCreateTable(newSize);
    if (newTable == NULL) return ERROR;
    for (int i = 0; i < ht->size; i++) {
        HashNode* cur = ht->buckets[i];
        while (cur != NULL) {
            HashNode* next = cur->next;
            int index = HashFunc(newTable, cur->key);
            cur->next = newTable->buckets[index];
            newTable->buckets[index] = cur;
            cur = next;
        }
    }
    free(ht->buckets);
    ht->buckets = newTable->buckets;
    ht->size = newSize;
    free(newTable);
    return OK;
}

void GetAllKeys(HashTable* ht, int* keys, int* cnt) {
    if (ht == NULL) {
        *cnt = 0;
        return;
    }
    if (keys == NULL || cnt == NULL) return;

    *cnt = 0;
    for (int i = 0; i < ht->size; i++) {
        HashNode* cur = ht->buckets[i];
        while (cur != NULL) {
            keys[*cnt] = cur->key;
            (*cnt)++;
            cur = cur->next;
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

void DestroyTable(HashTable** pht) {
    if (pht == NULL || *pht == NULL) return;
    HashTable* ht = *pht;
    for (int i = 0; i < ht->size; i++) {
        HashNode* cur = ht->buckets[i];
        while (cur != NULL) {
            HashNode* next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(ht->buckets);
    free(ht);
    *pht = NULL;
}

int DeleteIf(HashTable* ht, int threshold) {
    if (ht == NULL) return -1;
    int deletedCount = 0;
    for (int i = 0; i < ht->size; i++) {
        HashNode* cur = ht->buckets[i];
        HashNode* prev = NULL;
        while (cur != NULL) {
            if (cur->value < threshold) {
                HashNode* toDelete = cur;
                cur = cur->next;
                if (prev == NULL) {
                    ht->buckets[i] = cur;
                } else {
                    prev->next = cur;
                }
                free(toDelete);
                ht->count--;
                deletedCount++;
            } else {
                prev = cur;
                cur = cur->next;
            }
        }
    }
    return deletedCount;
}

int CountEmptyBuckets(HashTable* ht) {
    if (ht == NULL) return -1;
    int empty = 0;
    for (int i = 0; i < ht->size; i++) {
        if (ht->buckets[i] == NULL) empty++;
    }
    return empty;
}

Status ReverseBucket(HashTable* ht, int index) {
    if (ht == NULL || index < 0 || index >= ht->size) return ERROR;

    HashNode* cur = ht->buckets[index];
    if (cur == NULL || cur->next == NULL) return OK;

    HashNode* prev = NULL;
    while (cur != NULL) {
        HashNode* next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }
    ht->buckets[index] = prev;
    return OK;
}

Status Rehash(HashTable* ht, int newSize) {
    if (ht == NULL || newSize <= 0) return ERROR;

    HashNode** newBuckets = (HashNode**)malloc(sizeof(HashNode*) * newSize);
    if (newBuckets == NULL) return ERROR;

    for (int i = 0; i < newSize; i++) {
        newBuckets[i] = NULL;
    }

    int count = 0;
    for (int i = 0; i < ht->size; i++) {
        HashNode* cur = ht->buckets[i];
        while (cur != NULL) {
            HashNode* next = cur->next;
            if (cur->value > 0) {
                int index = abs(cur->key) % newSize;
                cur->next = newBuckets[index];
                newBuckets[index] = cur;
                count++;
            } else {
                free(cur);
            }
            cur = next;
        }
    }

    free(ht->buckets);
    ht->buckets = newBuckets;
    ht->size = newSize;
    ht->count = count;
    return OK;
}

int FindMaxValue(HashTable* ht) {
    if (ht == NULL || ht->count == 0) return -1;

    int maxVal = 0;
    int maxKey = -1;
    for (int i = 0; i < ht->size; i++) {
        HashNode* cur = ht->buckets[i];
        while (cur != NULL) {
            if (maxKey == -1 || cur->value > maxVal) {
                maxVal = cur->value;
                maxKey = cur->key;
            }
            cur = cur->next;
        }
    }
    return maxKey;
}

HashTable* MergeTable(HashTable* a, HashTable* b, int newSize) {
    if (a == NULL || b == NULL || newSize <= 0) return NULL;

    HashTable* ht = CreateTable(newSize);
    if (ht == NULL) return NULL;

    HashTable* sources[2] = {a, b};
    for (int s = 0; s < 2; s++) {
        HashTable* src = sources[s];
        for (int i = 0; i < src->size; i++) {
            HashNode* cur = src->buckets[i];
            while (cur != NULL) {
                int index = abs(cur->key) % newSize;
                HashNode* exist = ht->buckets[index];
                while (exist != NULL && exist->key != cur->key) {
                    exist = exist->next;
                }
                if (exist != NULL) {
                    exist->value = cur->value;
                } else {
                    HashNode* node = CreateNode(cur->key, cur->value);
                    if (node == NULL) {
                        HashTable* tmp = ht;
                        DestroyTable(&tmp);
                        return NULL;
                    }
                    node->next = ht->buckets[index];
                    ht->buckets[index] = node;
                    ht->count++;
                }
                cur = cur->next;
            }
        }
    }
    return ht;
}
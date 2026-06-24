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

HashNode* CreateNode(int key, int value){
	HashNode* node = (HashNode*)malloc(sizeof(HashNode));
	if(node == NULL)
	return NULL;
	node->key = key; 
	node->value = value;
	node->next = NULL;
	return node;
}

HashTable* CreateTable(int size){
	if(size <= 0)
	return NULL;
	HashTable* table = (HashTable*)malloc(sizeof(HashTable)); 
	if(table == NULL)
	return NULL;
	HashNode** b = (HashNode**)malloc(sizeof(HashNode*)*size);
	if(b == NULL){
		free(table);
		return NULL;
	}
	table->buckets = b;
	for(int i = 0;i < size;i++){
		table->buckets[i] = NULL;
	}
	table->size = size; 
	table->count = 0;
	return table;
}

int HashFunc(HashTable* ht, int key) {
    if (ht == NULL) {
        return -1;
    }
    int index = key % ht->size;
    if (index < 0) {
        index += ht->size;
    }
    return index;
}

Status Insert(HashTable* ht, int key, int value) {
    if (ht == NULL || ht->buckets == NULL) {
        return ERROR;
    }
    
    int index = HashFunc(ht, key);
    if (index == -1) {
        return ERROR;
    }
    
    HashNode* current = ht->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return ERROR;
        }
        current = current->next;
    }
    
    HashNode* newNode = CreateNode(key, value);
    if (newNode == NULL) {
        return ERROR;
    }
    newNode->next = ht->buckets[index];
    ht->buckets[index] = newNode;
    ht->count++;
    return OK;
}


HashNode* Search(HashTable* ht, int key) {
    if (ht == NULL || ht->buckets == NULL) {
        return NULL;
    }
    
    int index = HashFunc(ht, key);
    if (index == -1 || index >= ht->size) {
        return NULL;
    }
    HashNode* current = ht->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return current;  
        }
        current = current->next;
    }
    return NULL; 
}

int GetValue(HashTable* ht, int key){
	if(ht == NULL)
	return -1;
	HashNode* node = Search(ht,key);
	if(node == NULL)
	return -1;
	return node->value;
}


Status Delete(HashTable* ht, int key){
	if(ht == NULL)
	return ERROR;
	int index = HashFunc(ht,key);
	HashNode* del = ht->buckets[index];
	HashNode* pre = NULL;
	while(del != NULL){
		if(del->key == key){
			if(pre == NULL){
				ht->buckets[index] = del->next;
			}else{
				pre->next = del->next;
			}
				free(del);
				ht->count--;
				del = NULL;
		return OK;	
		}
		pre = del;
		del = pre->next;
	}
	
	return ERROR;
}

int Contains(HashTable* ht, int key) {
    if (ht == NULL) {
        return 0;
    }
    
    int index = HashFunc(ht, key);
    if (index == -1) {
        return 0;
    }
    HashNode* current = ht->buckets[index];
    while (current != NULL) {
        if (current->key == key) {
            return 1; 
        }
        current = current->next;
    }
    return 0;  
}

int GetCount(HashTable* ht){
	if(ht == NULL)
	return 0;
	return ht->count;
}

int GetBucketSize(HashTable* ht){
	if(ht == NULL)
	return 0;
	return ht->size;
	
}
float GetLoadFactor(HashTable* ht){
	if(ht == NULL)
	return 0.0f;
	if(ht->size == 0)
	return 0.0f;
	return (float)ht->count / (float)ht->size;
	
}
 
int GetChainLength(HashTable* ht, int index){
	if(ht == NULL||index<0||index >= ht->size)
	return -1;
	int len = 0;
	HashNode* cur = ht->buckets[index];
	while(cur){
		cur = cur->next;
		len++;
	} 
	return len;
}

int GetMaxChainLength(HashTable* ht){
	if(ht == NULL)
	return 0;
	int Max_Len = 0;
	for(int i = 0;i < ht->size;i++){
		int len =  GetChainLength(ht,i);
		if(len > Max_Len)
		Max_Len = len;
	} 
	return Max_Len;
}

Status Resize(HashTable* ht, int newSize) {
    if (ht == NULL || newSize <= 0) {
        return ERROR;
    }
    
    HashNode** oldBuckets = ht->buckets;
    int oldSize = ht->size;
    HashNode** newBuckets = (HashNode**)calloc(newSize, sizeof(HashNode*));
    if (newBuckets == NULL) {
        return ERROR;
    }
    
    ht->buckets = newBuckets;
    ht->size = newSize;
    ht->count = 0;  
    for (int i = 0; i < oldSize; i++) {
        HashNode* current = oldBuckets[i];
        while (current != NULL) {
            HashNode* next = current->next;
            int newIndex = HashFunc(ht, current->key);
            current->next = ht->buckets[newIndex];
            ht->buckets[newIndex] = current;
            ht->count++;
            current = next;
        }
    }
    free(oldBuckets);
    return OK;
}

void GetAllKeys(HashTable* ht, int* keys, int* cnt) {
    if (ht == NULL) {
        *cnt = 0;
        return;
    }
    
    *cnt = 0;
    for (int i = 0; i < ht->size; i++) {
        HashNode* current = ht->buckets[i];
        while (current != NULL) {
            keys[*cnt] = current->key;
            (*cnt)++;
            current = current->next;
        }
    }
    for (int i = 0; i < *cnt - 1; i++) {
        for (int j = 0; j < *cnt - i - 1; j++) {
            if (keys[j] > keys[j + 1]) {
                int tep = keys[j];
                keys[j] = keys[j + 1];
                keys[j + 1] = tep;
            }
        }
    }
    
}


void DestroyTable(HashTable** pht){
	if(pht == NULL)
	return;
	if((*pht) == NULL)
	return; 
for(int i = 0;i < (*pht)->size; i++){
	HashNode* cur = (*pht)->buckets[i];
	while(cur != NULL){
		HashNode* next = cur->next;
		free(cur);
		cur = next;
		}
	}
	free((*pht)->buckets);
	free(*pht);
	*pht = NULL;
	return ;	
}
int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

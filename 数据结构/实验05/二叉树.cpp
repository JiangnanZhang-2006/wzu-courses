#include <cstddef>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char ElementType;

typedef struct BiTNode {
    ElementType data;
    struct BiTNode* lchild;
    struct BiTNode* rchild;
} BiTNode, *BiTree;

/* 需要你实现的函数 */
BiTree CreateTree(const char* str);
BiTree CreateTreeByPreorder(const char* str);
int IsEmpty(BiTree T);
void PreOrder(BiTree T);
void InOrder(BiTree T);
void PostOrder(BiTree T);
int GetHeight(BiTree T);
int GetNodeCount(BiTree T);
int GetLeafCount(BiTree T);
BiTree FindNode(BiTree T, ElementType x);
int GetLevelNodeCount(BiTree T, int k);
void CountDegree(BiTree T, int* d0, int* d1, int* d2);
void SwapChildren(BiTree T);
void DestroyTree(BiTree* pT);
void PrintLeaves(BiTree T);
int GetWidth(BiTree T);
int GetSingleChildCount(BiTree T);
int IsEqual(BiTree T1, BiTree T2);
int FindPath(BiTree T, ElementType x, ElementType path[], int* pathLen);
ElementType GetMax(BiTree T);
ElementType GetMin(BiTree T);

int main()
{
    /*
     * 本地测试入口。
     * OJ 评测时将使用独立测试程序。
     */
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/
/*
例如：
BiTree CreateTree(const char* str) {
    ...
}
*/
BiTree CreateTree(const char* str) {
    if (str == NULL) return NULL;
    if (str[0] == '\0') return NULL;
    BiTree node = (BiTree)malloc(sizeof(BiTNode));
    if (node == NULL) return NULL;
    node->data = str[0];
    node->lchild = NULL;
    node->rchild = NULL;
    char substring[105];
    if (str[1] == '(') {
        int start = 2;
        int left_paren = 1, right_paren = 0;
        int n = strlen(str);
        int has_left = 0;
        for (int i = start; i < n; i++) {
            if (str[i] == '(') left_paren++;
            if (str[i] == ')') right_paren++;
            if (left_paren == right_paren + 1 && str[i] == ',') {
                strncpy(substring, str + start, i - start);
                substring[i - start] = '\0';
                node->lchild = CreateTree(substring);
                has_left = 1;
                start = i + 1;
            }
            if (left_paren == right_paren) {
                strncpy(substring, str + start, i - start);
                substring[i - start] = '\0';
                if (has_left) {
                    node->rchild = CreateTree(substring);
                } else {
                    node->lchild = CreateTree(substring);
                }
                break;
            }
        }
        return node;
    }
    return node;
}
static BiTree BuildTreeByPreorder(const char* str, size_t* pos) {
    if (str[*pos] == '\0')
        return NULL;
    char c = str[*pos];
    (*pos)++;
    if (c == '#')
        return NULL;
    BiTree node = (BiTree)malloc(sizeof(BiTNode));
    if (node == NULL)
        return NULL;
    node->data = c;
    node->lchild = BuildTreeByPreorder(str, pos);
    node->rchild = BuildTreeByPreorder(str, pos);
    return node;
}

BiTree CreateTreeByPreorder(const char* str) {
    if (str == NULL)
        return NULL;
    if (str[0] == '\0')
        return NULL;
    size_t pos = 0;
    return BuildTreeByPreorder(str, &pos);
}

int IsEmpty(BiTree T) {
    if (T == NULL) return 1;
    return 0;
}

void PreOrder(BiTree T) {
    if (!IsEmpty(T)) {
        printf("%c", T->data);
        PreOrder(T->lchild);
        PreOrder(T->rchild);
    }
}

void InOrder(BiTree T) {
    if (!IsEmpty(T)) {
        InOrder(T->lchild);
        printf("%c", T->data);
        InOrder(T->rchild);
    }
}

void PostOrder(BiTree T) {
    if (!IsEmpty(T)) {
        PostOrder(T->lchild);
        PostOrder(T->rchild);
        printf("%c", T->data);
    }
}

void LevelOrder(BiTree T) {
    if (IsEmpty(T)) return;
    class QueueClass{
        private:
            BiTNode *data[105];
            int front;
            int rear;
        public:
            QueueClass() {
                front = 0;
                rear = 0;
            }
            void enqueue(BiTNode *x) {
                data[rear++] = x;
            }
            BiTNode *dequeue() {
                return data[front++];
            }
            int isEmpty() {
                return front == rear;
            }
    };
    QueueClass queue;
    queue.enqueue(T);
    while (!queue.isEmpty()) {
        BiTNode *cur = queue.dequeue();
        printf("%c", cur->data);
        if (!IsEmpty(cur->lchild)) queue.enqueue(cur->lchild);
        if (!IsEmpty(cur->rchild)) queue.enqueue(cur->rchild);
    }
}

int GetHeight(BiTree T) {
    if (IsEmpty(T)) return 0;
    class QueueClass{
        private:
            BiTNode *data[105];
            int front;
            int rear;
        public:
            QueueClass() {
                front = 0;
                rear = 0;
            }
            void enqueue(BiTNode *x) {
                data[rear++] = x;
            }
            BiTNode *dequeue() {
                return data[front++];
            }
            int isEmpty() {
                return front == rear;
            }
            int getSize() {
                return rear - front;
            }
    };
    QueueClass queue;
    queue.enqueue(T);
    int depth = 0;
    while (!queue.isEmpty()) {
        int size = queue.getSize();
        depth++;
        for (int i = 0; i < size; i++) {
            BiTNode *cur = queue.dequeue();
            if (!IsEmpty(cur->lchild)) queue.enqueue(cur->lchild);
            if (!IsEmpty(cur->rchild)) queue.enqueue(cur->rchild);
        }
    }
    return depth;
}

int GetNodeCount(BiTree T) {
    if (IsEmpty(T))
        return 0;
    return 1 + GetNodeCount(T->lchild) + GetNodeCount(T->rchild);
}

int GetLeafCount(BiTree T) {
    if (IsEmpty(T)) return 0;
    class QueueClass{
        private:
            BiTNode *data[105];
            int front;
            int rear;
        public:
            QueueClass() {
                front = 0;
                rear = 0;
            }
            void enqueue(BiTNode *x) {
                data[rear++] = x;
            }
            BiTNode *dequeue() {
                return data[front++];
            }
            int isEmpty() {
                return front == rear;
            }
            int getSize() {
                return rear - front;
            }
    };
    QueueClass queue;
    queue.enqueue(T);
    int leafCount = 0;
    while (!queue.isEmpty()) {
        BiTNode *cur = queue.dequeue();
        if (IsEmpty(cur->lchild) && IsEmpty(cur->rchild)) leafCount++;
        if (!IsEmpty(cur->lchild)) queue.enqueue(cur->lchild);
        if (!IsEmpty(cur->rchild)) queue.enqueue(cur->rchild);
    }
    return leafCount;
}

BiTree FindNode(BiTree T, ElementType x)
{
    if (IsEmpty(T))
        return NULL;
    if (T->data == x)
        return T;
    BiTree p = FindNode(T->lchild, x);
    if (p != NULL)
        return p;
    return FindNode(T->rchild, x);
}

int GetLevelNodeCount(BiTree T, int k) {
    if (IsEmpty(T)) return 0;
    class QueueClass{
        private:
            BiTNode *data[105];
            int front;
            int rear;
        public:
            QueueClass() {
                front = 0;
                rear = 0;
            }
            void enqueue(BiTNode *x) {
                data[rear++] = x;
            }
            BiTNode *dequeue() {
                return data[front++];
            }
            int isEmpty() {
                return front == rear;
            }
            int getSize() {
                return rear - front;
            }
    };
    QueueClass queue;
    queue.enqueue(T);
    int depth = 0;
    while (!queue.isEmpty()) {
        int size = queue.getSize();
        depth++;
        if (depth == k) 
            return size;
        for (int i = 0; i < size; i++) {
            BiTNode *cur = queue.dequeue();
            if (!IsEmpty(cur->lchild)) queue.enqueue(cur->lchild);
            if (!IsEmpty(cur->rchild)) queue.enqueue(cur->rchild);
        }
    }
    return 0;
}

void CountDegree(BiTree T, int* d0, int* d1, int* d2) {
    if (d0 == NULL || d1 == NULL || d2 == NULL)
        return;
    if (IsEmpty(T))
        return;
    class QueueClass{
        private:
            BiTNode *data[105];
            int front;
            int rear;
        public:
            QueueClass() {
                front = 0;
                rear = 0;
            }
            void enqueue(BiTNode *x) {
                data[rear++] = x;
            }
            BiTNode *dequeue() {
                return data[front++];
            }
            int isEmpty() {
                return front == rear;
            }
    };
    QueueClass queue;
    queue.enqueue(T);
    while (!queue.isEmpty()) {
        int count = 0;
        BiTNode *cur = queue.dequeue();
        if (!IsEmpty(cur->lchild)) {
            queue.enqueue(cur->lchild);
            count++;
        }
        if (!IsEmpty(cur->rchild)) {
            queue.enqueue(cur->rchild);
            count++;
        }
        switch(count) {
            case 0:
                (*d0)++;
                break;
            case 1:
                (*d1)++;
                break;
            case 2:
                (*d2)++;
                break;
        }
    }
    return;
}

void SwapChildren(BiTree T) {
    if (T == NULL) return;
    BiTNode *temp = T->lchild;
    T->lchild = T->rchild;
    T->rchild = temp;
    SwapChildren(T->lchild);
    return SwapChildren(T->rchild);
}

void DestroyTree(BiTree* pT)
{
    if (pT == NULL || *pT == NULL)
        return;
    DestroyTree(&(*pT)->lchild);
    DestroyTree(&(*pT)->rchild);
    free(*pT);
    *pT = NULL;
}

void SubPrintLeave(BiTree T, int &first) {
    if (T->lchild == NULL && T->rchild == NULL) {
        if (first) {
            first = 0;
            printf("%c", T->data);
        } else {
            printf(" %c", T->data);
        }
        return;
    }
    if (T->lchild != NULL)
        SubPrintLeave(T->lchild, first);
    if (T->rchild != NULL)
        SubPrintLeave(T->rchild, first);
}

void PrintLeaves(BiTree T) {
    int first = 1;
    if (T == NULL) {
        printf("NULL\n");
        return;
    }
    SubPrintLeave(T, first);
    printf("\n");
}

int GetWidth(BiTree T) {
    if (IsEmpty(T)) return 0;
    class QueueClass{
        private:
            BiTNode *data[105];
            int front;
            int rear;
        public:
            QueueClass() {
                front = 0;
                rear = 0;
            }
            void enqueue(BiTNode *x) {
                data[rear++] = x;
            }
            BiTNode *dequeue() {
                return data[front++];
            }
            int isEmpty() {
                return front == rear;
            }
            int getSize() {
                return rear - front;
            }
    };
    QueueClass queue;
    queue.enqueue(T);
    int max = 0;

    while (!queue.isEmpty()) {
        int size = queue.getSize();
        max = size > max ? size : max;
        for (int i = 0; i < size; i++) {
            BiTNode *cur = queue.dequeue();
            if (!IsEmpty(cur->lchild)) queue.enqueue(cur->lchild);
            if (!IsEmpty(cur->rchild)) queue.enqueue(cur->rchild);
        }
    }

    return max;
}

int GetSingleChildCount(BiTree T) {
    int a = 0, b = 0, c = 0;
    CountDegree(T, &a, &b, &c);
    return b;
}

int IsEqual(BiTree T1, BiTree T2) {
    if (T1 == NULL && T2 == NULL) 
        return 1;
    if (T1 == NULL || T2 == NULL) 
        return 0;
    if (T1->data == T2->data && IsEqual(T1->lchild, T2->lchild) && IsEqual(T1->rchild, T2->rchild)) {
        return 1;
    }
    return 0;
}



static int SubFindPath(BiTree T, ElementType x, ElementType path[], int depth) {
    if (T == NULL)
        return 0;
    path[depth] = T->data;
    if (T->data == x)
        return depth + 1;
    int len = SubFindPath(T->lchild, x, path, depth + 1);
    if (len != 0)
        return len;
    return SubFindPath(T->rchild, x, path, depth + 1);
}

int FindPath(BiTree T, ElementType x, ElementType path[], int* pathLen) {
    if (pathLen == NULL)
        return 0;
    if (path == NULL) {
        *pathLen = 0;
        return 0;
    }
    if (IsEmpty(T)) {
        *pathLen = 0;
        return 0;
    }
    int len = SubFindPath(T, x, path, 0);
    *pathLen = len;
    return len != 0 ? 1 : 0;
}

ElementType GetMax(BiTree T) {
    if (IsEmpty(T))
        return '#';
    ElementType m = T->data;
    if (T->lchild != NULL) {
        ElementType lm = GetMax(T->lchild);
        if (lm > m)
            m = lm;
    }
    if (T->rchild != NULL) {
        ElementType rm = GetMax(T->rchild);
        if (rm > m)
            m = rm;
    }
    return m;
}

ElementType GetMin(BiTree T) {
    if (IsEmpty(T))
        return '#';
    ElementType m = T->data;
    if (T->lchild != NULL) {
        ElementType lm = GetMin(T->lchild);
        if (lm < m)
            m = lm;
    }
    if (T->rchild != NULL) {
        ElementType rm = GetMin(T->rchild);
        if (rm < m)
            m = rm;
    }
    return m;
}
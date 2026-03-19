#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode {
    ElementType data;
    struct LNode* next;
} LNode, *LinkList;

typedef enum { OK = 1, ERROR = 0 } Status;

/* 需要你实现的函数（无头节点：L 直接指向首元，空表 L==NULL） */
Status InitList(LinkList* pL);
Status IsEmpty(const LinkList L);
void PrintList(const LinkList L);
int GetLength(const LinkList L);
Status PushBack(LinkList* pL, ElementType x);
Status PushFront(LinkList* pL, ElementType x);
Status GetElem(const LinkList L, int pos1, ElementType* out);
int LocateElem(const LinkList L, ElementType x);
Status InsertAt(LinkList* pL, int pos1, ElementType x);
Status DeleteAt(LinkList* pL, int pos1, ElementType* deleted);
int RemoveAll(LinkList* pL, ElementType x);
void Reverse(LinkList* pL);
void Clear(LinkList* pL);
void DestroyList(LinkList* pL);
Status InsertSorted(LinkList* pL, ElementType x);
Status RemoveRange(LinkList* pL, ElementType low, ElementType high);
Status RemoveDuplicates(LinkList* pL);
Status FindMiddle(const LinkList L, ElementType* out);
Status SplitByPosition(LinkList* pL, LinkList* pLodd, LinkList* pLeven);
Status MergeSorted(const LinkList La, const LinkList Lb, LinkList* pLc);
Status Intersection(LinkList* pLa, LinkList* pLb, LinkList* pLc);
Status ReverseSegment(LinkList* pL, int start, int end);
Status RemoveMin(LinkList* pL, ElementType* minVal);
Status SplitByValue(LinkList* pL, ElementType x, LinkList* pLess, LinkList* pGreaterEqual);
Status Unique(LinkList* pL);

int main()
{
    /*
     * 此处代码由测试程序自动添加。
     * 你只需提交上述函数的实现。
     */
    return 0;
}

/******************** 学生提交的"缺失函数"会被拼接在此处 ********************/
/*
例如缺失 InitList 时，学生只提交：
void InitList(LinkList* pL) { ... }
*/

/* 无头节点：L 直接指向首元节点，空表时 L == NULL */
Status InitList(LinkList* pL) {
    if (pL == NULL) return ERROR;
    *pL = NULL;
    return OK;
}

Status IsEmpty(const LinkList L) {
    if (L == NULL) return OK;
    return ERROR;
}

void PrintList(const LinkList L) {
    if (L == NULL) {
        printf("NULL\n");
        return;
    }
    LinkList p = L;
    int first = 1;
    while (p != NULL) {
        if (first) { printf("%d", p->data); first = 0; }
        else printf(" %d", p->data);
        p = p->next;
    }
    printf("\n");
}

int GetLength(const LinkList L) {
    if (L == NULL) return 0;
    int n = 0;
    for (LinkList p = L; p != NULL; p = p->next) n++;
    return n;
}

Status PushBack(LinkList* pL, ElementType x) {
    if (pL == NULL) return ERROR;
    LinkList new_node = (LinkList)malloc(sizeof(LNode));
    if (new_node == NULL) return ERROR;
    new_node->data = x;
    new_node->next = NULL;
    if (*pL == NULL) {
        *pL = new_node;
        return OK;
    }
    LinkList p = *pL;
    while (p->next != NULL) p = p->next;
    p->next = new_node;
    return OK;
}

Status PushFront(LinkList* pL, ElementType x) {
    if (pL == NULL) return ERROR;
    LinkList new_node = (LinkList)malloc(sizeof(LNode));
    if (new_node == NULL) return ERROR;
    new_node->data = x;
    new_node->next = *pL;
    *pL = new_node;
    return OK;
}

Status GetElem(const LinkList L, int pos1, ElementType* out) {
    if (L == NULL || out == NULL || pos1 < 1) return ERROR;
    int i = 0;
    LinkList p = L;
    while (p != NULL) {
        i++;
        if (i == pos1) { *out = p->data; return OK; }
        p = p->next;
    }
    return ERROR;
}

int LocateElem(const LinkList L, ElementType x) {
    if (L == NULL) return -1;
    int i = 0;
    LinkList p = L;
    while (p != NULL) {
        i++;
        if (p->data == x) return i;
        p = p->next;
    }
    return -1;
}

Status InsertAt(LinkList* pL, int pos1, ElementType x) {
    if (pL == NULL || pos1 < 1) return ERROR;
    if (pos1 == 1) {
        LinkList new_node = (LinkList)malloc(sizeof(LNode));
        if (new_node == NULL) return ERROR;
        new_node->data = x;
        new_node->next = *pL;
        *pL = new_node;
        return OK;
    }
    int i = 1;
    LinkList p = *pL;
    while (p != NULL && i < pos1 - 1) { p = p->next; i++; }
    if (p == NULL) return ERROR;
    LinkList new_node = (LinkList)malloc(sizeof(LNode));
    if (new_node == NULL) return ERROR;
    new_node->data = x;
    new_node->next = p->next;
    p->next = new_node;
    return OK;
}

Status DeleteAt(LinkList* pL, int pos1, ElementType* deleted) {
    if (pL == NULL || deleted == NULL || pos1 < 1) return ERROR;
    if (*pL == NULL) return ERROR;
    if (pos1 == 1) {
        LinkList t = *pL;
        *deleted = t->data;
        *pL = t->next;
        free(t);
        return OK;
    }
    int i = 1;
    LinkList p = *pL;
    while (p->next != NULL && i < pos1 - 1) { p = p->next; i++; }
    if (p->next == NULL) return ERROR;
    LinkList t = p->next;
    *deleted = t->data;
    p->next = t->next;
    free(t);
    return OK;
}

int RemoveAll(LinkList* pL, ElementType x) {
    if (pL == NULL) return 0;
    int count = 0;
    while (*pL != NULL && (*pL)->data == x) {
        LinkList t = *pL;
        *pL = t->next;
        free(t);
        count++;
    }
    if (*pL == NULL) return count;
    LinkList p = *pL;
    while (p->next != NULL) {
        if (p->next->data == x) {
            count++;
            LinkList t = p->next;
            p->next = t->next;
            free(t);
        } else {
            p = p->next;
        }
    }
    return count;
}

void Reverse(LinkList* pL) {
    if (pL == NULL || *pL == NULL) return;
    LinkList prev = NULL, curr = *pL, next;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *pL = prev;
}

Status ReverseSegment(LinkList* pL, int start, int end) {
    if (pL == NULL || start < 1 || end < start) return ERROR;
    int length = GetLength(*pL);
    if (start > length || end > length) return ERROR;
    LinkList prev_seg = NULL, curr = *pL;
    for (int i = 1; i < start; i++) {
        prev_seg = curr;
        curr = curr->next;
    }
    LinkList start_node = curr;
    for (int i = start; i < end; i++) curr = curr->next;
    LinkList end_node = curr;
    LinkList next_node = end_node->next;
    end_node->next = NULL;
    LinkList prev = NULL;
    curr = start_node;
    while (curr != NULL) {
        LinkList next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    if (prev_seg != NULL)
        prev_seg->next = prev;
    else
        *pL = prev;
    start_node->next = next_node;
    return OK;
}

void Clear(LinkList* pL) {
    if (pL == NULL) return;
    while (*pL != NULL) {
        LinkList t = *pL;
        *pL = t->next;
        free(t);
    }
}

void DestroyList(LinkList* pL) {
    if (pL == NULL) return;
    while (*pL != NULL) {
        LinkList t = *pL;
        *pL = t->next;
        free(t);
    }
    *pL = NULL;
}

Status RemoveMin(LinkList* pL, ElementType* minVal) {
    if (pL == NULL || minVal == NULL || *pL == NULL) return ERROR;
    LinkList prev = NULL, min_prev = NULL, curr = *pL, min_node = NULL;
    while (curr != NULL) {
        if (min_node == NULL || curr->data < min_node->data) {
            min_prev = prev;
            min_node = curr;
        }
        prev = curr;
        curr = curr->next;
    }
    *minVal = min_node->data;
    if (min_prev == NULL) {
        *pL = min_node->next;
    } else {
        min_prev->next = min_node->next;
    }
    free(min_node);
    return OK;
}

Status SplitByValue(LinkList* pL, ElementType x, LinkList* pLess, LinkList* pGreaterEqual) {
    if (pL == NULL || pLess == NULL || pGreaterEqual == NULL) return ERROR;
    while (*pLess != NULL) {
        LinkList t = *pLess;
        *pLess = t->next;
        free(t);
    }
    while (*pGreaterEqual != NULL) {
        LinkList t = *pGreaterEqual;
        *pGreaterEqual = t->next;
        free(t);
    }
    LinkList Less_tail = NULL, GreaterEqual_tail = NULL;
    while (*pL != NULL) {
        if ((*pL)->data < x) {
            LinkList t = *pL;
            *pL = t->next;
            t->next = NULL;
            if (Less_tail == NULL){
                *pLess = t;
                Less_tail = t;
            } else {
                Less_tail->next = t;
                Less_tail = t;
            }
        } else {
            LinkList t = *pL;
            *pL = t->next;
            t->next = NULL;
            if (GreaterEqual_tail == NULL){
                *pGreaterEqual = t;
                GreaterEqual_tail = t;
            }else {
                GreaterEqual_tail->next = t;
                GreaterEqual_tail = t;
            }
        }
    }
    return OK;
}

Status InsertSorted(LinkList* pL, ElementType x) {
    if (pL == NULL) return ERROR;
    LinkList new_node = (LinkList)malloc(sizeof(LNode));
    if (new_node == NULL) return ERROR;
    new_node->data = x;
    new_node->next = NULL;
    if (*pL == NULL || (*pL)->data >= x) {
        new_node->next = *pL;
        *pL = new_node;
        return OK;
    }
    LinkList p = *pL;
    while (p->next != NULL && p->next->data < x) p = p->next;
    new_node->next = p->next;
    p->next = new_node;
    return OK;
}

Status RemoveRange(LinkList* pL, ElementType low, ElementType high) {
    if (pL == NULL) return ERROR;
    if (low > high) return OK;
    while (*pL != NULL && (*pL)->data >= low && (*pL)->data <= high) {
        LinkList t = *pL;
        *pL = t->next;
        free(t);
    }
    if (*pL == NULL) return OK;
    LinkList p = *pL;
    while (p->next != NULL) {
        if (p->next->data >= low && p->next->data <= high) {
            LinkList t = p->next;
            p->next = t->next;
            free(t);
        } else {
            p = p->next;
        }
    }
    return OK;
}

Status RemoveDuplicates(LinkList* pL) {
    if (pL == NULL) return ERROR;
    if (*pL == NULL) return OK;
    LinkList p = *pL;
    while (p != NULL) {
        LinkList q = p;
        while (q->next != NULL) {
            if (q->next->data == p->data) {
                LinkList t = q->next;
                q->next = t->next;
                free(t);
            } else {
                q = q->next;
            }
        }
        p = p->next;
    }
    return OK;
}

Status FindMiddle(const LinkList L, ElementType* out) {
    if (L == NULL || out == NULL) return ERROR;
    LinkList slow = L, fast = L;
    while (fast != NULL && fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *out = slow->data;
    return OK;
}

Status SplitByPosition(LinkList* pL, LinkList* pLodd, LinkList* pLeven) {
    if (pL == NULL || pLodd == NULL || pLeven == NULL) return ERROR;
    if (*pLodd != NULL || *pLeven != NULL) return ERROR; /* 要求调用前已置空 */
    LinkList p = *pL;
    *pL = NULL;
    LinkList odd_tail = NULL, even_tail = NULL;
    int pos = 1;
    while (p != NULL) {
        LinkList next = p->next;
        p->next = NULL;
        if (pos % 2 == 1) {
            if (odd_tail == NULL) *pLodd = p; else odd_tail->next = p;
            odd_tail = p;
        } else {
            if (even_tail == NULL) *pLeven = p; else even_tail->next = p;
            even_tail = p;
        }
        p = next;
        pos++;
    }
    return OK;
}

Status MergeSorted(LinkList* pLa, LinkList* pLb, LinkList* pLc) {
    if (pLa == NULL || pLb == NULL || pLc == NULL) return ERROR;
    while (*pLc != NULL) {
        LinkList t = *pLc;
        *pLc = t->next;
        free(t);
    }
    LinkList pa = *pLa, pb = *pLb;
    if (pa == NULL) {
        *pLc = pb;
        *pLa = NULL;
        *pLb = NULL;
        return OK;
    }
    if (pb == NULL) {
        *pLc = pa;
        *pLa = NULL;
        *pLb = NULL;
        return OK;
    }
    LinkList head = NULL, tail = NULL;
    while (pa != NULL && pb != NULL) {
        LinkList pick;
        if (pa->data <= pb->data) {
            pick = pa;
            pa = pa->next;
        } else {
            pick = pb;
            pb = pb->next;
        }
        pick->next = NULL;
        if (tail == NULL) head = tail = pick;
        else { tail->next = pick; tail = pick; }
    }
    if (pa != NULL) {
        if (tail == NULL) head = pa;
        else tail->next = pa;
    }
    if (pb != NULL) {
        if (tail == NULL) head = pb;
        else tail->next = pb;
    }
    *pLc = head;
    *pLa = NULL;
    *pLb = NULL;
    return OK;
}

Status Intersection(LinkList* pLa, LinkList* pLb, LinkList* pLc) {
    if (pLa == NULL || pLb == NULL || pLc == NULL) return ERROR;
    while (*pLc != NULL) {
        LinkList t = *pLc;
        *pLc = t->next;
        free(t);
    }
    if (*pLa == NULL || *pLb == NULL) {
        while (*pLa != NULL) { LinkList t = *pLa; *pLa = t->next; free(t); }
        while (*pLb != NULL) { LinkList t = *pLb; *pLb = t->next; free(t); }
        *pLa = NULL;
        *pLb = NULL;
        *pLc = NULL;
        return OK;
    }
    LinkList head = NULL, tail = NULL;
    LinkList pa = *pLa, pb = *pLb;
    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data) {
            LinkList t = pa;
            pa = pa->next;
            free(t);
        } else if (pa->data > pb->data) {
            LinkList t = pb;
            pb = pb->next;
            free(t);
        } else {
            LinkList pick = pa;
            pa = pa->next;
            pick->next = NULL;
            if (tail == NULL) head = tail = pick;
            else { tail->next = pick; tail = pick; }
            while (pa != NULL && pa->data == tail->data) {
                LinkList t = pa;
                pa = pa->next;
                free(t);
            }
            while (pb != NULL && pb->data == tail->data) {
                LinkList t = pb;
                pb = pb->next;
                free(t);
            }
        }
    }
    while (pa != NULL) { LinkList t = pa; pa = pa->next; free(t); }
    while (pb != NULL) { LinkList t = pb; pb = pb->next; free(t); }
    *pLc = head;
    *pLa = NULL;
    *pLb = NULL;
    return OK;
}

Status Unique(LinkList* pL) {
    if (pL == NULL) return ERROR;
    if (*pL == NULL) return OK;
    LinkList p = *pL;
    while (p != NULL) {
        if (p->next != NULL && p->next->data == p->data) {
            LinkList t = p->next;
            p->next = t->next;
            free(t);
        } else p = p->next;
    }
    return OK;
}
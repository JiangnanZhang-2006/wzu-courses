#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;

typedef struct LNode {
    ElementType data;
    struct LNode* next;
} LNode, *LinkList;

typedef enum { OK = 1, ERROR = 0 } Status;

/* 需要你实现的函数 */
LinkList InitList(void);
Status IsEmpty(const LinkList L);
void PrintList(const LinkList L);
int GetLength(const LinkList L);
Status PushBack(LinkList L, ElementType x);
Status PushFront(LinkList L, ElementType x);
Status GetElem(const LinkList L, int pos1, ElementType* out);
int LocateElem(const LinkList L, ElementType x);
Status InsertAt(LinkList L, int pos1, ElementType x);
Status DeleteAt(LinkList L, int pos1, ElementType* deleted);
int RemoveAll(LinkList L, ElementType x);
void Reverse(LinkList L);
void Clear(LinkList L);
void DestroyList(LinkList* pL);
Status InsertSorted(LinkList L, ElementType x);
Status RemoveRange(LinkList L, ElementType low, ElementType high);
Status RemoveDuplicates(LinkList L);
Status FindMiddle(const LinkList L, ElementType* out);
Status SplitByPosition(LinkList L, LinkList* pLodd, LinkList* pLeven);
Status MergeSorted(const LinkList La, const LinkList Lb, LinkList Lc);
Status Intersection(const LinkList La, const LinkList Lb, LinkList Lc);

int main()
{
    /*
     * 此处代码由测试程序自动添加。
     * 你只需提交上述函数的实现。
     */
    return 0;
}
/******************** 学生提交的“缺失函数”会被拼接在此处 ********************/
/*
例如缺失 InitList 时，学生只提交：
LinkList InitList(void) { ... }
*/

LinkList InitList(void) {
    LinkList L = (LinkList)malloc(sizeof(LNode));
    if (L == NULL) return NULL;
    L->next = NULL;
    return L;
}

Status IsEmpty(const LinkList L) {
    if (L == NULL) return OK;
    if (L->next == NULL) return OK;
    return ERROR;
}

void PrintList(const LinkList L) {
    if (L == NULL || L->next == NULL) {
        printf("NULL\n");
        return;
    }
    LinkList p = L->next;
    bool first = true;
    while (p != NULL) {
        if (first) {
            printf("%d", p->data);
            first = false;
        } else {
            printf(" %d", p->data);
        }
        p = p->next;
    }
    printf("\n");
}

int GetLength(const LinkList L) {
    if (L == NULL) return 0;
    int length = 0;
    LinkList p = L->next;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    return length;
}

Status PushBack(LinkList L, ElementType x) {
    if (L == NULL) return ERROR;
    LinkList new_node = (LinkList)malloc(sizeof(LNode));
    if (new_node == NULL) return ERROR;
    new_node->data = x;
    new_node->next = NULL;
    LinkList p = L;
    while (p->next != NULL) p = p->next;
    p->next = new_node;
    return OK;
}

Status PushFront(LinkList L, ElementType x) {
    if (L == NULL) return ERROR;
    LinkList new_node = (LinkList)malloc(sizeof(LNode));
    if (new_node == NULL) return ERROR;
    new_node->data = x;
    new_node->next = L->next;
    L->next = new_node;
    return OK;
}

Status GetElem(const LinkList L, int pos1, ElementType* out) {
    if (L == NULL || out == NULL || pos1 < 1) return ERROR;
    int count = 0;
    LinkList p = L->next;
    while (p != NULL) {
        count++;
        if (count == pos1) {
            *out = p->data;
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

int LocateElem(const LinkList L, ElementType x) {
    if (L == NULL) return -1;
    int count = 0;
    LinkList p = L->next;
    while (p != NULL) {
        count++;
        if (p->data == x) return count;
        p = p->next;
    }
    return -1;
}

Status InsertAt(LinkList L, int pos1, ElementType x) {
    if (L == NULL || pos1 < 1) return ERROR;
    int count = 0;
    LinkList p = L;
    while (p != NULL) {
        count++;
        if (count == pos1) break;
        p = p->next;
    }
    if (p == NULL) return ERROR;
    LinkList new_node = (LinkList)malloc(sizeof(LNode));
    if (new_node == NULL) return ERROR;
    new_node->data = x;
    new_node->next = p->next;
    p->next = new_node;
    return OK;
}

Status DeleteAt(LinkList L, int pos1, ElementType* deleted) {
    if (L == NULL || deleted == NULL || pos1 < 1) return ERROR;
    int count = 0;
    LinkList p = L;
    while (p->next != NULL) {
        count++;
        if (count == pos1) {
            *deleted = p->next->data;
            LinkList temp = p->next;
            p->next = p->next->next;
            free(temp);
            return OK;
        }
        p = p->next;
    }
    return ERROR;
}

int RemoveAll(LinkList L, ElementType x) {
    if (L == NULL) return 0;
    int count = 0;
    LinkList p = L;
    while (p->next != NULL) {
        if (p->next->data == x) {
            count++;
            LinkList temp = p->next;
            p->next = p->next->next;
            free(temp);
        } else {
            p = p->next;
        }
    }
    return count;
}

void Reverse(LinkList L) {
    LinkList prev, curr, next;
    prev = NULL;
    curr = L->next;
    while (curr != NULL) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    L->next = prev;
}

void Clear(LinkList L) {
    if (L == NULL) return;
    LinkList p = L->next;
    while (p != NULL) {
        LinkList temp = p;
        p = p->next;
        free(temp);
    }
    L->next = NULL;
}

void DestroyList(LinkList* pL) {
    if (pL == NULL) return;
    if (*pL == NULL) return;
    LinkList p = (*pL)->next;
    while (p != NULL) {
        LinkList temp = p;
        p = p->next;
        free(temp);
    }
    free(*pL);
    *pL = NULL;
}

Status InsertSorted(LinkList L, ElementType x) {
    if (L == NULL) return ERROR;
    LinkList new_node = (LinkList)malloc(sizeof(LNode));
    if (new_node == NULL) return ERROR;
    new_node->data = x;
    new_node->next = NULL;
    LinkList p = L;
    while (p->next != NULL) {
        if (p->next->data >= x) break;
        p = p->next;
    }
    new_node->next = p->next;
    p->next = new_node;
    return OK;
}

Status RemoveRange(LinkList L, ElementType low, ElementType high) {
    if (L == NULL) return ERROR;
    if (low > high) return OK;
    LinkList p = L;
    while (p->next != NULL && p->next->data < low) p = p->next;
    while (p->next != NULL) {
        if (p->next->data >= low && p->next->data <= high) {
            LinkList temp = p->next;
            p->next = p->next->next;
            free(temp);
        } else {
            p = p->next;
        }
    }
    return OK;
}

Status RemoveDuplicates(LinkList L) {
    if (L == NULL) return ERROR;
    if (L->next == NULL) return OK;
    LinkList p = L->next;
    while (p != NULL) {
        LinkList q = p;
        while (q->next != NULL) {
            if (q->next->data == p->data) {
                LinkList temp = q->next;
                q->next = q->next->next;
                free(temp);
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
    LinkList slow = L->next;
    LinkList fast = L->next;
    while (fast != NULL && fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *out = slow->data;
    return OK;
}

Status SplitByPosition(LinkList L, LinkList* pLodd, LinkList* pLeven) {
    if (L == NULL || pLodd == NULL || pLeven == NULL) return ERROR;
    if (*pLodd == NULL || *pLeven == NULL) return ERROR;
    LinkList odd_tail = *pLodd;
    LinkList even_tail = *pLeven;
    LinkList p = L->next;
    int count = 1;
    while (p != NULL) {
        if (count % 2 != 0) {
            odd_tail->next = p;
            odd_tail = odd_tail->next;
        } else {
            even_tail->next = p;
            even_tail = even_tail->next;
        }
        p = p->next;
        count++;
    }
    odd_tail->next = NULL;
    even_tail->next = NULL;
    L->next = NULL;
    return OK;
}

Status MergeSorted(const LinkList La, const LinkList Lb, LinkList Lc) {
    //none decreasing order
    if (La == NULL || Lb == NULL || Lc == NULL) return ERROR;
    if (!IsEmpty(Lc)) return ERROR;
    if (IsEmpty(La) && IsEmpty(Lb)) return OK;
    LinkList pa = La->next;
    LinkList pb = Lb->next;
    LinkList temp = InitList();
    if (temp == NULL) return ERROR;
    while (pa != NULL && pb != NULL) {
        if (pa->data < pb->data) {
            if (PushBack(temp, pa->data) == ERROR) {
                DestroyList(&temp);
                return ERROR;
            }
            pa = pa->next;
        } else {
            if (PushBack(temp, pb->data) == ERROR) {
                DestroyList(&temp);
                return ERROR;
            }
            pb = pb->next;
        }
    }
    while (pa != NULL) {
        if (PushBack(temp, pa->data) == ERROR) {
            DestroyList(&temp);
            return ERROR;
        }
        pa = pa->next;
    }
    while (pb != NULL) {
        if (PushBack(temp, pb->data) == ERROR) {
            DestroyList(&temp);
            return ERROR;
        }
        pb = pb->next;
    }
    Lc->next = temp->next;
    free(temp);
    return OK;
}

Status Intersection(const LinkList La, const LinkList Lb, LinkList Lc) {
    if (La == NULL || Lb == NULL || Lc == NULL) return ERROR;
    if (!IsEmpty(Lc)) return ERROR;
    LinkList temp = InitList();
    if (temp == NULL) return ERROR;
    LinkList pa = La->next;
    while (pa != NULL) {
        if (LocateElem(Lb, pa->data) != -1) {
            if (PushBack(temp, pa->data) == ERROR) {
                DestroyList(&temp);
                return ERROR;
            }
        }
        pa = pa->next;
    }
    //remove duplicates
    LinkList p = temp->next;
    while (p != NULL) {
        LinkList q = p;
        while (q->next != NULL) {
            if (q->next->data == p->data) {
                LinkList _temp = q->next;
                q->next = q->next->next;
                free(_temp);
            } else {
                q = q->next;
            }
        }
        p = p->next;
    }
    Lc->next = temp->next;
    free(temp);

    return OK;
}
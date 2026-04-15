/******************** 3856 统计单分支节点 — 仅提交以下函数实现（可整体粘贴） ********************/

#include <stddef.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct BiTNode {
    ElementType data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

/* 先序+# 建子树：内部用 */
static BiTree BuildPreorder(const char *str, size_t *pos)
{
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
    node->lchild = BuildPreorder(str, pos);
    node->rchild = BuildPreorder(str, pos);
    return node;
}

BiTree CreateTreeByPreorder(const char *str)
{
    if (str == NULL)
        return NULL;
    if (str[0] == '\0')
        return NULL;
    size_t pos = 0;
    return BuildPreorder(str, &pos);
}

int IsEmpty(BiTree T)
{
    return T == NULL ? 1 : 0;
}

void CountDegree(BiTree T, int *d0, int *d1, int *d2)
{
    if (d0 == NULL || d1 == NULL || d2 == NULL)
        return;
    if (T == NULL)
        return;

    CountDegree(T->lchild, d0, d1, d2);
    CountDegree(T->rchild, d0, d1, d2);

    /* 后序位置统计当前结点度数（或改为先序/中序，只要每个结点访问一次即可） */
    int left = (T->lchild != NULL);
    int right = (T->rchild != NULL);
    int deg = left + right;
    if (deg == 0)
        (*d0)++;
    else if (deg == 1)
        (*d1)++;
    else
        (*d2)++;
}

void DestroyTree(BiTree *pT)
{
    if (pT == NULL || *pT == NULL)
        return;
    DestroyTree(&(*pT)->lchild);
    DestroyTree(&(*pT)->rchild);
    free(*pT);
    *pT = NULL;
}

int GetSingleChildCount(BiTree T)
{
    int d0 = 0, d1 = 0, d2 = 0;
    CountDegree(T, &d0, &d1, &d2);
    return d1;
}

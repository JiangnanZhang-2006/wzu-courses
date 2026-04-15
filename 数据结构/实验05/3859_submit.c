/************************************************************
 * 3859 - 最大最小值（OJ 提交用：不依赖 string.h/strlen，适配仅含 cstdio、cstdlib 的 Main.cc）
 ************************************************************/

#include <stddef.h>
#include <stdlib.h>

typedef char ElementType;

typedef struct BiTNode {
    ElementType data;
    struct BiTNode *lchild;
    struct BiTNode *rchild;
} BiTNode, *BiTree;

/* 先序+# 建树 */
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

int GetNodeCount(BiTree T)
{
    if (T == NULL)
        return 0;
    return 1 + GetNodeCount(T->lchild) + GetNodeCount(T->rchild);
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

ElementType GetMax(BiTree T)
{
    if (T == NULL)
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

ElementType GetMin(BiTree T)
{
    if (T == NULL)
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

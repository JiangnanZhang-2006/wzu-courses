#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct HuffmanNode {
    char data;
    int  weight;
    struct HuffmanNode* lchild;
    struct HuffmanNode* rchild;
} HuffmanNode, *HuffmanTree;

typedef struct CodeNode {
    char ch;
    char code[256];
    struct CodeNode* next;
} CodeNode;

typedef struct {
    CodeNode* head;    /* 链表头指针 */
    int n;             /* 编码节点数量 */
} CodeTable;


/* 需要你实现的函数 */
HuffmanNode* FindMinAndRemove(HuffmanNode** nodes, int* size);
HuffmanTree CreateHuffmanTree(char chars[], int weights[], int n);
CodeTable* CreateCodeTable(HuffmanTree root);

int main()
{
    /*
     * 本地测试入口。
     * OJ 评测时将使用独立测试程序。
     */
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

void HuffmanFreeSubtree(HuffmanNode* p) {
    if (p == NULL) return;
    HuffmanFreeSubtree(p->lchild);
    HuffmanFreeSubtree(p->rchild);
    free(p);
}

HuffmanNode* FindMinAndRemove(HuffmanNode** nodes, int* size) {
    if (nodes == NULL || size == NULL || *size <= 0) return NULL;
    int pmin = 0;
    int wmin = nodes[0]->weight;
    for (int i = 1; i < *size; i++) {
        if (nodes[i]->weight < wmin) {
            wmin = nodes[i]->weight;
            pmin = i;
        }
    }
    HuffmanNode* res = nodes[pmin];
    for (int i = pmin; i < *size - 1; i++) {
        nodes[i] = nodes[i + 1];
    }
    (*size)--;
    return res;
}

HuffmanTree CreateHuffmanTree(char chars[], int weights[], int n) {
    if (chars == NULL || weights == NULL || n <= 0) return NULL;
    HuffmanNode** forest = (HuffmanNode**)malloc(sizeof(HuffmanNode*) * n);
    if (forest == NULL) return NULL;
    for (int i = 0; i < n; i++) {
        HuffmanNode* leaf = (HuffmanNode*)malloc(sizeof(HuffmanNode));
        if (leaf == NULL) {
            for (int j = 0; j < i; j++) {
                free(forest[j]);
            }
            free(forest);
            return NULL;
        }
        leaf->data = chars[i];
        leaf->weight = weights[i];
        leaf->lchild = NULL;
        leaf->rchild = NULL;
        forest[i] = leaf;
    }
    int size = n;
    while (size > 1) {
        HuffmanNode* min1 = FindMinAndRemove(forest, &size);
        HuffmanNode* min2 = FindMinAndRemove(forest, &size);
        HuffmanNode* parent = (HuffmanNode*)malloc(sizeof(HuffmanNode));
        // if (parent == NULL) {
        //     for (int j = 0; j < size; j++) {
        //         HuffmanFreeSubtree(forest[j]);
        //     }
        //     HuffmanFreeSubtree(min1);
        //     HuffmanFreeSubtree(min2);
        //     free(forest);
        //     return NULL;
        // }
        parent->data = '\0';
        parent->weight = min1->weight + min2->weight;
        parent->lchild = min1;
        parent->rchild = min2;
        forest[size] = parent;
        size++;
    }
    HuffmanTree root = forest[0];
    free(forest);
    return root;
}

void SubCreateCodeTable(HuffmanTree root, char* code, int depth) {
    if (root == NULL) return;
    
}

CodeTable* CreateCodeTable(HuffmanTree root) {
    if (root == NULL) return NULL;
    CodeTable* pct = (CodeTable*)malloc(sizeof(CodeTable));
    if (pct == NULL) return NULL;
    pct->head = NULL;
    pct->n = 0;
    SubCreateCodeTable(root, "", 0);
    return pct;
}
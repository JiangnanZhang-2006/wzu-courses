#include <cstddef>
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
int GetWPL(HuffmanTree root);
int IsEmpty(HuffmanTree root);
int GetHeight(HuffmanTree root);
int GetLeafCount(HuffmanTree root);
int GetWPLHelper(HuffmanTree node, int depth);


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

static CodeTable* s_code_table_build = NULL;

void SubCreateCodeTable(HuffmanTree root, char* code, int depth) {
    if (root == NULL || s_code_table_build == NULL) return;
    if (root->lchild == NULL && root->rchild == NULL) {
        CodeNode* node = (CodeNode*)malloc(sizeof(CodeNode));
        if (node == NULL) return;
        node->ch = root->data;
        if (depth == 0) {
            node->code[0] = '0';
            node->code[1] = '\0';
        } else {
            code[depth] = '\0';
            strncpy(node->code, code, sizeof(node->code) - 1);
            node->code[sizeof(node->code) - 1] = '\0';
        }
        node->next = s_code_table_build->head;
        s_code_table_build->head = node;
        s_code_table_build->n++;
        return;
    }
    code[depth] = '0';
    SubCreateCodeTable(root->lchild, code, depth + 1);
    code[depth] = '1';
    SubCreateCodeTable(root->rchild, code, depth + 1);
}

CodeTable* CreateCodeTable(HuffmanTree root) {
    if (root == NULL) return NULL;
    CodeTable* pct = (CodeTable*)malloc(sizeof(CodeTable));
    if (pct == NULL) return NULL;
    pct->head = NULL;
    pct->n = 0;
    s_code_table_build = pct;
    char buf[256];
    buf[0] = '\0';
    SubCreateCodeTable(root, buf, 0);
    s_code_table_build = NULL;
    return pct;
}

int IsEmpty(HuffmanTree root) {
    if (root == NULL) return 1;
    return 0;
}

int GetHeight(HuffmanTree root) {
    if (IsEmpty(root)) return 0;
    int rheight = GetHeight(root->rchild), lheight = GetHeight(root->lchild);
    if (rheight > lheight) return rheight + 1;
    return lheight + 1;
}

int GetLeafCount(HuffmanTree root) {
    if (IsEmpty(root)) return 0;
    if (IsEmpty(root->lchild) && IsEmpty(root->rchild)) return 1;
    return GetLeafCount(root->lchild) + GetLeafCount(root->rchild);
}

int GetWPLHelper(HuffmanTree node, int depth) {
    if (node == NULL) return 0;
    if (node->lchild == NULL && node->rchild == NULL) return depth * node->weight;
    return GetWPLHelper(node->lchild, depth + 1) + GetWPLHelper(node->rchild, depth + 1);
}

int GetWPL(HuffmanTree root) {
    if (root == NULL) return 0;
    return GetWPLHelper(root, 0);
}

char* FindCodeByChar(CodeTable* ct, char ch) {
    if (ct == NULL || ct->head == NULL) return NULL;
    CodeNode* p = ct->head;
    while (p != NULL) {
        if (p->ch == ch) return p->code;
        p = p->next;
    }
    return NULL;
}

void FindMaxWeightCharHelper(HuffmanTree root, int* maxWeight, char* maxChar) {
    if (root == NULL) return;
    if (IsEmpty(root->lchild) && IsEmpty(root->rchild)) {
        if (*maxWeight < root->weight) {
            *maxWeight = root->weight;
            *maxChar = root->data;
        }
        return;
    }
    FindMaxWeightCharHelper(root->lchild, maxWeight, maxChar);
    FindMaxWeightCharHelper(root->rchild, maxWeight, maxChar);
}

char FindMaxWeightChar(HuffmanTree root) {
    if (root == NULL) return '\0';
    int maxWeight = 0;
    char maxChar = '\0';
    FindMaxWeightCharHelper(root, &maxWeight, &maxChar);
    return maxChar;
}

char* EncodeChar(CodeTable* ct, char ch) {
    if (ct == NULL || ch == '\0') return NULL;
    return FindCodeByChar(ct, ch);
}

char* EncodeString(CodeTable* ct, const char* str) {
    if (ct == NULL || str == NULL) return NULL;

    size_t total = 1;
    for (const char* p = str; *p; p++) {
        char* c = FindCodeByChar(ct, *p);
        if (c == NULL) return NULL;
        total += strlen(c);
    }

    char* result = (char*)malloc(total);
    if (result == NULL) return NULL;

    char* dest = result;
    for (const char* p = str; *p; p++) {
        char* c = FindCodeByChar(ct, *p);
        if (c == NULL) {
            free(result);
            return NULL;
        }
        size_t clen = strlen(c);
        memcpy(dest, c, clen);
        dest += clen;
    }
    *dest = '\0';
    return result;
}

char DecodeChar(HuffmanTree root, const char* code, int* pos) {
    if (root == NULL || code == NULL || pos == NULL) return '\0';
    if (*pos >= strlen(code)) return '\0';
    HuffmanTree node = root;
    while (node->lchild != NULL || node->rchild != NULL) {
        if (code[*pos] == '0') node = node->lchild;
        else node = node->rchild;
        (*pos)++;
    }
    return node->data;
}

char* DecodeString(HuffmanTree root, const char* code) {
    if (root == NULL || code == NULL) return NULL;
    size_t len = strlen(code);
    char* result = (char*)malloc(len + 1);
    if (result == NULL) return NULL;
    char* dest = result;
    int pos = 0;
    while (pos < len) {
        char ch = DecodeChar(root, code, &pos);
        if (ch == '\0') break;
        *dest++ = ch;
    }
    *dest = '\0';
    return result;
}

void DestroyHuffmanTree(HuffmanTree* pRoot) {
    if (pRoot == NULL || *pRoot == NULL) return;
    DestroyHuffmanTree(&(*pRoot)->lchild);
    DestroyHuffmanTree(&(*pRoot)->rchild);
    free(*pRoot);
    *pRoot = NULL;
}

void DestroyCodeTable(CodeTable** pCt) {
    if (pCt == NULL || *pCt == NULL) return;
    CodeNode* p = (*pCt)->head;
    while (p != NULL) {
        CodeNode* next = p->next;
        free(p);
        p = next;
    }
    free(*pCt);
    *pCt = NULL;
}

int GetFixedBits(int n) {
    if (n <= 1) return 1;
    int bits = 0;
    int cap = 1;
    while (cap < n) {
        cap <<= 1;
        bits++;
    }
    return bits;
}

double CalcCompressionRate(HuffmanTree root, int n) {
    if (root == NULL || n <= 0) return 0.0;
    int totalWeight = root->weight;
    int fixedBits = GetFixedBits(n);
    int fixedEncodingBits = totalWeight * fixedBits;
    if (fixedEncodingBits <= 0) return 0.0;
    int wpl = GetWPL(root);
    return (double)(fixedEncodingBits - wpl) / (double)fixedEncodingBits;
}
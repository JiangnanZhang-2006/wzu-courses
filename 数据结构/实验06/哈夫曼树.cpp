#include <cstddef>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

typedef struct {
    char data;        /* 字符数据 */
    int weight;       /* 权值 */
    int parent;       /* 父节点下标 */
    int lchild;       /* 左孩子下标 */
    int rchild;       /* 右孩子下标 */
} HTNode;

typedef struct {
    HTNode* nodes;    /* 节点数组 */
    int n;            /* 叶子节点数 */
    int size;         /* 总节点数(2n-1) */
} HuffmanTree;

typedef struct {
    char ch;          /* 字符 */
    char code[256];   /* 编码字符串 */
} CodeNode;

typedef struct {
    CodeNode* codes;  /* 编码数组 */
    int n;            /* 编码数量 */
} CodeTable;

typedef struct {
    char** encodedStrs;  /* 编码后的字符串数组 */
    int count;           /* 字符串数量 */
    int originalBits;    /* 原始总位数 */
    int encodedBits;     /* 编码后总位数 */
} BatchEncodeResult;

typedef struct {
    int height1;      /* 树1高度 */
    int height2;      /* 树2高度 */
    int wpl1;         /* 树1 WPL */
    int wpl2;         /* 树2 WPL */
    CodeTable* ct1;   /* 树1编码表 */
    CodeTable* ct2;   /* 树2编码表 */
} CompareResult;

typedef struct {
    int nodeCount;    /* 总节点数 */
    int leafCount;    /* 叶子节点数 */
    int height;       /* 树高度 */
    int wpl;          /* 带权路径长度 */
    CodeTable* ct;    /* 编码表 */
} TreeReport;

/* 辅助函数声明（已在测试代码中实现，你可以直接调用） */
void SelectMinTwo(HuffmanTree* ht, int end, int* s1, int* s2);

/* 需要你实现的函数 */
HuffmanTree* CreateHuffmanTree(char chars[], int weights[], int n);
CodeTable* CreateCodeTable(HuffmanTree* ht);
int IsEmpty(HuffmanTree* ht);
void PrintHuffmanTree(HuffmanTree* ht);
void PrintCodeTable(CodeTable* ct);
int GetHeight(HuffmanTree* ht);
int GetNodeCount(HuffmanTree* ht);
int GetWPL(HuffmanTree* ht);
char* FindCodeByChar(CodeTable* ct, char ch);
char FindCharByCode(CodeTable* ct, const char* code);
char* EncodeString(CodeTable* ct, const char* str);
char DecodeChar(HuffmanTree* ht, const char* code, int* pos);
void DestroyHuffmanTree(HuffmanTree** pHt);
void DestroyCodeTable(CodeTable** pCt);
double CalcCompressionRate(int originalBits, int encodedBits);
int VerifyEncodeDecode(char chars[], int weights[], int n, const char* testStr);
BatchEncodeResult* BatchEncode(char chars[], int weights[], int n, char* strs[], int m);
void DestroyBatchEncodeResult(BatchEncodeResult** pResult);
char* QueryCodeTable(CodeTable* ct, char queryType, const char* queryParam);
CompareResult* CompareHuffmanTrees(HuffmanTree* ht1, HuffmanTree* ht2);

int main()
{
    /*
     * 本地测试入口。
     * OJ 评测时将使用独立测试程序。
     */
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

void SelectMinTwo(HuffmanTree* ht, int end, int* s1, int* s2) {
    if (s1 == NULL || s2 == NULL || ht == NULL || ht->nodes == NULL) return;
    *s1 = *s2 = -1;
    if (end < 0) return;
    for (int j = 0; j <= end; j++) {
        if (ht->nodes[j].parent != -1) continue;
        if (*s1 < 0) {
            *s1 = j;
            continue;
        }
        int wj = ht->nodes[j].weight, w1 = ht->nodes[*s1].weight;
        if (wj < w1 || (wj == w1 && j < *s1))
            *s1 = j;
    }
    if (*s1 < 0) return;
    for (int j = 0; j <= end; j++) {
        if (ht->nodes[j].parent != -1 || j == *s1) continue;
        if (*s2 < 0) {
            *s2 = j;
            continue;
        }
        int wj = ht->nodes[j].weight, w2 = ht->nodes[*s2].weight;
        if (wj < w2 || (wj == w2 && j < *s2))
            *s2 = j;
    }
}

HuffmanTree* CreateHuffmanTree(char chars[], int weights[], int n) {
    if (chars == NULL || weights == NULL || n <= 0) return NULL;
    HuffmanTree* dht = (HuffmanTree*)malloc(sizeof(HuffmanTree));
    if (dht == NULL) return NULL;
    dht->n = n;
    dht->size = 2 * n - 1;
    dht->nodes = (HTNode*)malloc(sizeof(HTNode) * (n * 2 - 1));
    if (dht->nodes == NULL) {
        free(dht);
        return NULL;
    }
    for (int i = 0; i < n; i++) {
        dht->nodes[i].data = chars[i];
        dht->nodes[i].weight = weights[i];
        dht->nodes[i].lchild = -1;
        dht->nodes[i].rchild = -1;
        dht->nodes[i].parent = -1;
    }
    for (int i = n; i < 2 * n - 1; i++) {
        int s1, s2;
        SelectMinTwo(dht, i - 1, &s1, &s2);
        if (s1 < 0 || s2 < 0) {
            free(dht->nodes);
            free(dht);
            return NULL;
        }
        dht->nodes[i].lchild = s1;
        dht->nodes[i].rchild = s2;
        dht->nodes[s1].parent = i;
        dht->nodes[s2].parent = i;
        dht->nodes[i].data = '\0';
        dht->nodes[i].parent = -1;
        dht->nodes[i].weight = dht->nodes[s1].weight + dht->nodes[s2].weight;
    }
    return dht;
}

CodeTable* CreateCodeTable(HuffmanTree* ht) {
    if (ht == NULL || ht->nodes == NULL || ht->n <= 0) return NULL;
    int leafNum = ht->n;
    CodeTable* pct = (CodeTable*)malloc(sizeof(CodeTable));
    if (pct == NULL) return NULL;
    pct->n = leafNum;
    pct->codes = (CodeNode*)malloc((size_t)leafNum * sizeof(CodeNode));
    if (pct->codes == NULL) {
        free(pct);
        return NULL;
    }
    for (int i = 0; i < leafNum; i++) {
        pct->codes[i].ch = ht->nodes[i].data;
        char tmp[256];
        int len = 0;
        int c = i;
        while (ht->nodes[c].parent != -1) {
            int p = ht->nodes[c].parent;
            tmp[len++] =
                (ht->nodes[p].lchild == c) ? '0' : '1';
            c = p;
        }
        if (len == 0) {
            pct->codes[i].code[0] = '0';
            pct->codes[i].code[1] = '\0';
        } else {
            for (int j = 0; j < len; j++) {
                pct->codes[i].code[j] = tmp[len - 1 - j];
            }
            pct->codes[i].code[len] = '\0';
        }
    }
    return pct;
}

int IsEmpty(HuffmanTree* ht) {
    if (ht == NULL || ht->nodes == NULL || ht->n <= 0) return 1;
    return 0;
}

void PrintHuffmanTree(HuffmanTree* ht) {
    if (ht == NULL || ht->nodes == NULL || ht->n <= 0) return;
    for (int i = 0; i < ht->size; i++) {
        if (i < ht->n) printf("%d %c %d %d %d %d\n", i, ht->nodes[i].data, ht->nodes[i].weight, ht->nodes[i].parent, ht->nodes[i].lchild, ht->nodes[i].rchild);
        else printf("%d - %d %d %d %d\n", i, ht->nodes[i].weight, ht->nodes[i].parent, ht->nodes[i].lchild, ht->nodes[i].rchild);
    }
}

void PrintCodeTable(CodeTable* ct) {
    if (ct == NULL || ct->codes == NULL) return;
    for (int i = 0; i < ct->n; i++) {
        printf("%c:%s\n", ct->codes[i].ch, ct->codes[i].code);
    }
}

static int SubtreeHeight(HTNode* nodes, int i) {
    if (i < 0) return 0;
    if (nodes[i].lchild < 0 && nodes[i].rchild < 0)
        return 1;
    int hL = SubtreeHeight(nodes, nodes[i].lchild);
    int hR = SubtreeHeight(nodes, nodes[i].rchild);
    return 1 + (hL > hR ? hL : hR);
}

int GetHeight(HuffmanTree* ht) {
    if (ht == NULL || ht->nodes == NULL || ht->n <= 0) return 0;
    int root = -1;
    for (int k = 0; k < ht->size; k++) {
        if (ht->nodes[k].parent == -1) {
            root = k;
            break;
        }
    }
    if (root < 0) return 0;
    return SubtreeHeight(ht->nodes, root);
}

int GetNodeCount(HuffmanTree* ht) {
    if (ht == NULL || ht->nodes == NULL || ht->n <= 0) return 0;
    return ht->size;
}

int GetWPL(HuffmanTree* ht) {
    if (ht == NULL || ht->nodes == NULL || ht->n <= 0) return 0;
    int wpl = 0;
    for (int i = 0; i < ht->n; i++) {
        int edges = 0;
        for (int c = i; ht->nodes[c].parent != -1; c = ht->nodes[c].parent)
            edges++;
        wpl += edges * ht->nodes[i].weight;
    }
    return wpl;
}

char* FindCodeByChar(CodeTable* ct, char ch) {
    if (ct == NULL || ct->codes == NULL) return NULL;
    for (int i = 0; i < ct->n; i++)
        if (ct->codes[i].ch == ch) return ct->codes[i].code;
    return NULL;
}

char FindCharByCode(CodeTable* ct, const char* code) {
    if (ct == NULL || ct->codes == NULL || code == NULL) return '\0';
    for (int i = 0; i < ct->n; i++) {
        if (strcmp(code, ct->codes[i].code) == 0) return ct->codes[i].ch;
    }
    return '\0';
}

char* EncodeString(CodeTable* ct, const char* str) {
    if (ct == NULL || str == NULL) return NULL;
    int pos = 0;
    char* s = (char*)malloc(sizeof(char) * 10000);
    if (s == NULL) return NULL;
    for (int i = 0; str[i] != '\0'; i++) {
        for (int j = 0; j < ct->n; j++) {
            if (str[i] == ct->codes[j].ch) {
                for (int k = 0; ct->codes[j].code[k] != '\0'; k++) {
                    s[pos++] = ct->codes[j].code[k];
                }
                break;
            }
        }
    }
    s[pos++] = '\0';
    return s;
}

char DecodeChar(HuffmanTree* ht, const char* code, int* pos) {
    if (ht == NULL || ht->nodes == NULL || pos == NULL || code == NULL)
        return '\0';
    int root = -1;
    for (int i = 0; i < ht->size; i++) {
        if (ht->nodes[i].parent == -1) {
            root = i;
            break;
        }
    }
    if (root < 0) return '\0';
    int p = root;
    if (ht->nodes[p].lchild < 0 && ht->nodes[p].rchild < 0) {
        if (ht->n == 1 && code[*pos] == '0')
            (*pos)++;
        return ht->nodes[p].data;
    }
    while (ht->nodes[p].lchild >= 0 || ht->nodes[p].rchild >= 0) {
        char b = code[*pos];
        if (b == '\0') return '\0';
        int nxt = (b == '0')
                      ? ht->nodes[p].lchild
                      : (b == '1' ? ht->nodes[p].rchild : -1);
        if (nxt < 0) return '\0';
        p = nxt;
        (*pos)++;
    }
    return ht->nodes[p].data;
}

char* DecodeString(HuffmanTree* ht, const char* code) {
    if (ht == NULL || ht->nodes == NULL || ht->n <= 0 || code == NULL) return NULL;
    char *s = (char*)malloc(sizeof(char) * 1000);
    if (s == NULL) return NULL;
    int codePos = 0;
    int sPos = 0;
    char ch;
    while ((ch = DecodeChar(ht, code, &codePos)) != '\0')
        s[sPos++] = ch;
    s[sPos] = '\0';
    return s;
}

void DestroyHuffmanTree(HuffmanTree** pHt) {
    if (pHt == NULL || *pHt == NULL) return;
    free((*pHt)->nodes);
    (*pHt)->nodes = NULL;
    free(*pHt);
    (*pHt) = NULL;
    return;
}

void DestroyCodeTable(CodeTable** pCt) {
    if (pCt == NULL || *pCt == NULL) return;
    free((*pCt)->codes);
    (*pCt)->codes = NULL;
    free(*pCt);
    *pCt = NULL;
    return;
}

double CalcCompressionRate(int originalBits, int encodedBits) {
    return originalBits <= 0 ? -1.0 : (double)encodedBits / (double)originalBits;
}

int VerifyEncodeDecode(char chars[], int weights[], int n, const char* testStr) {
    int status = 1, valid = 1;
    HuffmanTree* pht = CreateHuffmanTree(chars, weights, n);
    if (pht == NULL) valid = 0;
    CodeTable* pct = CreateCodeTable(pht);
    if (pct == NULL) valid = 0;
    char* pcBefore = EncodeString(pct, testStr);
    if (pcBefore == NULL) valid = 0;
    char* pcAfter = DecodeString(pht, pcBefore);
    if (pcAfter == NULL) valid = 0;
    status = !(strcmp(pcAfter, testStr) == -1);
    DestroyCodeTable(&pct);
    DestroyHuffmanTree(&pht);
    if (valid) {
        if (status) return 1;
        else return 0;
    } else return -1;
}

void DestroyBatchEncodeResult(BatchEncodeResult** pResult) {
    if (pResult == NULL || *pResult == NULL) return;
    if ((*pResult)->encodedStrs != NULL) {
        for (int i = 0; i < (*pResult)->count; i++) {
            free((*pResult)->encodedStrs[i]);
            (*pResult)->encodedStrs[i] = NULL;
        }
        free((*pResult)->encodedStrs);
        (*pResult)->encodedStrs = NULL;
    }
    free(*pResult);
    *pResult = NULL;
    return;
}

BatchEncodeResult* BatchEncode(char chars[], int weights[], int n, char* strs[], int m) {
    if (chars == NULL || weights == NULL || strs == NULL || n <= 0 || m <= 0)
        return NULL;
    BatchEncodeResult* pber = (BatchEncodeResult*)malloc(sizeof(BatchEncodeResult));
    if (pber == NULL) return NULL;
    pber->encodedStrs = (char**)calloc((size_t)m, sizeof(char*));
    if (pber->encodedStrs == NULL) {
        free(pber);
        return NULL;
    }
    pber->encodedBits = 0;
    pber->originalBits = 0;
    pber->count = m;
    HuffmanTree* pht = CreateHuffmanTree(chars, weights, n);
    if (pht == NULL) {
        DestroyBatchEncodeResult(&pber);
        return NULL;
    }
    CodeTable* pct = CreateCodeTable(pht);
    if (pct == NULL) {
        DestroyHuffmanTree(&pht);
        DestroyBatchEncodeResult(&pber);
        return NULL;
    }
    for (int i = 0; i < m; i++) {
        if (strs[i] != NULL)
            pber->originalBits += (int)strlen(strs[i]) * 8;
        pber->encodedStrs[i] = EncodeString(pct, strs[i]);
        if (pber->encodedStrs[i] == NULL) {
            DestroyHuffmanTree(&pht);
            DestroyCodeTable(&pct);
            DestroyBatchEncodeResult(&pber);
            return NULL;
        }
        pber->encodedBits += (int)strlen(pber->encodedStrs[i]);
    }
    DestroyHuffmanTree(&pht);
    DestroyCodeTable(&pct);
    return pber;
}

char* QueryCodeTable(CodeTable* ct, char queryType, const char* queryParam) {
    if (ct == NULL || queryParam == NULL || !(queryType == 'C' || queryType == 'E'))
        return NULL;
    if (queryType == 'C') {
        char *code = FindCodeByChar(ct, queryParam[0]);
        if (code == NULL) {
            char* out = (char*)calloc(100, sizeof(char));
            if (out == NULL) return NULL;
            strcpy(out, "NULL");
            return out;
        }
        size_t len = strlen(code);
        char* out = (char*)malloc(len + 1);
        if (out == NULL) return NULL;
        memcpy(out, code, len + 1);
        return out;
    } else {
        char c = FindCharByCode(ct, queryParam);
        char* pqct = (char*)calloc(100, sizeof(char));
        if (pqct == NULL) return NULL;
        pqct[0] = c == '\0' ? '?' : c;
        pqct[1] = '\0';
        return pqct;
    }
}

CompareResult* CompareHuffmanTrees(HuffmanTree* ht1, HuffmanTree* ht2) {
    if (ht1 == NULL || ht2 == NULL) return NULL;
    CompareResult* pcr = (CompareResult*)malloc(sizeof(CompareResult));
    if (pcr == NULL) return NULL;
    pcr->height1 = GetHeight(ht1);
    pcr->height2 = GetHeight(ht2);
    pcr->wpl1 = GetWPL(ht1);
    pcr->wpl2 = GetWPL(ht2);
    pcr->ct1 = CreateCodeTable(ht1);
    pcr->ct2 = CreateCodeTable(ht2);
    return pcr;
}

TreeReport* GenerateTreeReport(HuffmanTree* ht) {
    if (ht == NULL || ht->nodes == NULL || ht->n <= 0) return NULL;
    TreeReport* ptr = (TreeReport*)malloc(sizeof(TreeReport));
    if (ptr == NULL) return NULL;
    ptr->nodeCount = GetNodeCount(ht);
    ptr->leafCount = ht->n;
    ptr->height = GetHeight(ht);
    ptr->wpl = GetWPL(ht);
    ptr->ct = CreateCodeTable(ht);
    return ptr;
}
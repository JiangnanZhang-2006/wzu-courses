#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct BSTNode {
    int data;
    struct BSTNode* left;
    struct BSTNode* right;
    struct BSTNode* parent;
} BSTNode;

BSTNode* CreateNode(int val);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

BSTNode* CreateNode(int val) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (node == NULL) return NULL;
    node->data = val;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

static Status InsertHelper(BSTNode** node, int val, BSTNode* parent) {
    if (*node == NULL) {
        *node = CreateNode(val);
        if (*node == NULL) return ERROR;
        (*node)->parent = parent;
        return OK;
    }
    if (val < (*node)->data) {
        return InsertHelper(&(*node)->left, val, *node);
    } else if (val > (*node)->data) {
        return InsertHelper(&(*node)->right, val, *node);
    } else {
        return ERROR;
    }
}

Status Insert(BSTNode** root, int val) {
    if (root == NULL) return ERROR;
    return InsertHelper(root, val, NULL);
}

Status SetParent(BSTNode* root) {
    if (root == NULL) return ERROR;
    if (root->left != NULL) {
        root->left->parent = root;
        SetParent(root->left);
    }
    if (root->right != NULL) {
        root->right->parent = root;
        SetParent(root->right);
    }
    return OK;
}

BSTNode* Search(BSTNode* root, int val) {
    if (root == NULL) return NULL;
    if (root->data == val) return root;
    if (val < root->data) {
        return Search(root->left, val);
    } else if (val > root->data) {
        return Search(root->right, val);
    }
    return NULL;
}

void InOrder(BSTNode* root, int* result, int* cnt) {
    if (root == NULL) return;
    InOrder(root->left, result, cnt);
    result[*cnt] = root->data;
    (*cnt)++;
    InOrder(root->right, result, cnt);
}

static BSTNode* bstGetMin(BSTNode* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;
    return bstGetMin(root->left);
}

static BSTNode* bstGetMax(BSTNode* root) {
    if (root == NULL) return NULL;
    if (root->right == NULL) return root;
    return bstGetMax(root->right);
}

BSTNode* GetMin(BSTNode* root) {
    return bstGetMin(root);
}

BSTNode* GetMax(BSTNode* root) {
    return bstGetMax(root);
}

BSTNode* Predecessor(BSTNode* node) {
    if (node == NULL) return NULL;
    if (node->left != NULL) {
        return bstGetMax(node->left);
    }
    BSTNode* parent = node->parent;
    while (parent != NULL && node == parent->left) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

BSTNode* Successor(BSTNode* node) {
    if (node == NULL) return NULL;
    if (node->right != NULL) {
        return bstGetMin(node->right);
    }
    BSTNode* parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

int GetHeight(BSTNode* root) {
    if (root == NULL) return 0;
    int leftHeight = GetHeight(root->left);
    int rightHeight = GetHeight(root->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

int CountNodes(BSTNode* root) {
    if (root == NULL) return 0;
    return CountNodes(root->left) + CountNodes(root->right) + 1;
}

int GetLevel(BSTNode* node) {
    if (node == NULL) return -1;
    if (node->parent == NULL) return 1;
    return GetLevel(node->parent) + 1;
}

int IsBST(BSTNode* root) {
    if (root == NULL) return 1;
    if (root->left != NULL && root->left->data > root->data) return 0;
    if (root->right != NULL && root->right->data < root->data) return 0;
    if (!IsBST(root->left) || !IsBST(root->right)) return 0;
    return 1;
}

static void ReplaceNodeInParent(BSTNode** root, BSTNode* node, BSTNode* child) {
    if (node->parent == NULL) {
        *root = child;
    } else if (node->parent->left == node) {
        node->parent->left = child;
    } else {
        node->parent->right = child;
    }
    if (child != NULL) {
        child->parent = node->parent;
    }
}

Status Delete(BSTNode** root, int val) {
    if (root == NULL) return ERROR;

    BSTNode* node = *root;
    while (node != NULL && node->data != val) {
        if (val < node->data) node = node->left;
        else node = node->right;
    }
    if (node == NULL) return ERROR;

    if (node->left != NULL && node->right != NULL) {
        BSTNode* succ = bstGetMin(node->right);
        node->data = succ->data;
        BSTNode* child = succ->right;
        ReplaceNodeInParent(root, succ, child);
        free(succ);
        return OK;
    }

    BSTNode* child = node->left != NULL ? node->left : node->right;
    ReplaceNodeInParent(root, node, child);
    free(node);
    return OK;
}

Status DeleteByPred(BSTNode** root, int val) {
    if (root == NULL) return ERROR;

    BSTNode* node = *root;
    while (node != NULL && node->data != val) {
        if (val < node->data) node = node->left;
        else node = node->right;
    }
    if (node == NULL) return ERROR;

    if (node->left != NULL && node->right != NULL) {
        BSTNode* pred = bstGetMax(node->left);
        node->data = pred->data;
        BSTNode* child = pred->left;
        ReplaceNodeInParent(root, pred, child);
        free(pred);
        return OK;
    }

    BSTNode* child = node->left != NULL ? node->left : node->right;
    ReplaceNodeInParent(root, node, child);
    free(node);
    return OK;
}

void DestroyBST(BSTNode** root) {
    if (root == NULL || *root == NULL) return;
    DestroyBST(&(*root)->left);
    DestroyBST(&(*root)->right);
    free(*root);
    *root = NULL;
}

int RangeQuery(BSTNode* root, int lo, int hi, int* result) {
    if (root == NULL || lo > hi || result == NULL) return 0;
    int count = 0;
    count += RangeQuery(root->left, lo, hi, result);
    if (root->data >= lo && root->data <= hi) {
        result[count] = root->data;
        count++;
    }
    count += RangeQuery(root->right, lo, hi, result + count); //⬅count是当前已经插入的元素个数
    return count;
}

int DeleteRange(BSTNode** root, int lo, int hi) {
    if (root == NULL) return 0;
    int count = 0;
    int *queryResult = (int*)malloc(sizeof(int) * 1000);
    if (queryResult == NULL) return 0;
    count = RangeQuery(*root, lo, hi, queryResult);
    for (int i = 0; i < count; i++) {
        Delete(root, queryResult[i]);
    }
    free(queryResult);
    return count;
}

BSTNode* FindKth(BSTNode* root, int k) {
    if (root == NULL || k <= 0 || k > CountNodes(root)) return NULL;
    int leftCount = CountNodes(root->left);
    if (k <= leftCount) {
        return FindKth(root->left, k);
    } else if (k == leftCount + 1) {
        return root;
    } else {
        return FindKth(root->right, k - leftCount - 1);
    }
}

int IsBalanced(BSTNode* root) {
    if (root == NULL) return 1;
    int leftHeight = GetHeight(root->left);
    int rightHeight = GetHeight(root->right);
    if (abs(leftHeight - rightHeight) > 1) return 0;
    if (!IsBalanced(root->left) || !IsBalanced(root->right)) return 0;
    return 1;
}

Status GetPath(BSTNode* root, int val, int* result, int* cnt) {
    if (root == NULL || result == NULL || cnt == NULL) return ERROR;

    BSTNode* node = root;
    while (node != NULL && node->data != val) {
        if (val < node->data) node = node->left;
        else node = node->right;
    }
    if (node == NULL) return ERROR;
    //需要重置cnt
    *cnt = 0;
    while (node != NULL) {
        result[*cnt] = node->data;
        (*cnt)++;
        node = node->parent;
    }
    for (int i = 0; i < *cnt / 2; i++) {
        int temp = result[i];
        result[i] = result[*cnt - i - 1];
        result[*cnt - i - 1] = temp;
    }
    return OK;
}

int CountAtLevel(BSTNode* root, int level) {
    if (root == NULL || level <= 0) return 0;
    if (level == 1) return 1;
    return CountAtLevel(root->left, level - 1) + CountAtLevel(root->right, level - 1);
}

BSTNode* LCA(BSTNode* root, int val1, int val2) {
    if (root == NULL) return NULL;
    if (Search(root, val1) == NULL) return NULL;
    if (Search(root, val2) == NULL) return NULL;

    BSTNode* cur = root;
    while (cur != NULL) {
        if (val1 < cur->data && val2 < cur->data) {
            cur = cur->left;
        } else if (val1 > cur->data && val2 > cur->data) {
            cur = cur->right;
        } else {
            return cur;
        }
    }
    return NULL;
}
#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct BSTNode {
    int data;
    int count;
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
    node->count = 1;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    return node;
}

Status Insert(BSTNode** root, int val) {
    if (root == NULL) return ERROR;

    BSTNode* node = *root;
    BSTNode* parent = NULL;
    while (node != NULL && node->data != val) {
        parent = node;
        if (val < node->data) node = node->left;
        else node = node->right;
    }
    if (node != NULL) {
        node->count++;
        return ERROR;
        //ymc说的
    }

    BSTNode* newNode = CreateNode(val);
    if (newNode == NULL) return ERROR;

    if (parent == NULL) {
        *root = newNode;
    } else if (val < parent->data) {
        parent->left = newNode;
    } else {
        parent->right = newNode;
    }
    newNode->parent = parent;
    return OK;
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
    if (val < root->data) return Search(root->left, val);
    else if (val > root->data) return Search(root->right, val);
    else return NULL;
}

void InOrder(BSTNode* root, int* result, int* cnt) {
    if (root == NULL) return;
    InOrder(root->left, result, cnt);
    for (int i = 0; i < root->count; i++) {
        result[*cnt] = root->data;
        (*cnt)++;
    }
    InOrder(root->right, result, cnt);
}

int GetHeight(BSTNode* root) {
    if (root == NULL) return 0;
    int leftHeight = GetHeight(root->left);
    int rightHeight = GetHeight(root->right);
    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

BSTNode* GetMin(BSTNode* root) {
    if (root == NULL) return NULL;
    if (root->left == NULL) return root;
    return GetMin(root->left);
}

BSTNode* GetMax(BSTNode* root) {
    if (root == NULL) return NULL;
    if (root->right == NULL) return root;
    return GetMax(root->right);
}

BSTNode* Predecessor(BSTNode* node) {
    if (node == NULL) return NULL;
    if (node->left != NULL) {
        return GetMax(node->left);
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
        return GetMin(node->right);
    }
    BSTNode* parent = node->parent;
    while (parent != NULL && node == parent->right) {
        node = parent;
        parent = parent->parent;
    }
    return parent;
}

int CountNodes(BSTNode* root) {
    if (root == NULL) return 0;
    //节点个数不包括重复的
    return CountNodes(root->left) + CountNodes(root->right) + 1;
}

int CountTotal(BSTNode* root) {
    if (root == NULL) return 0;
    return CountTotal(root->left) + CountTotal(root->right) + root->count;
}

int GetCount(BSTNode* root, int val) {
    if (root == NULL) return 0;
    BSTNode* node = Search(root, val);
    if (node == NULL) return 0;
    return node->count;
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


void ReplaceNodeInParent(BSTNode** root, BSTNode* node, BSTNode* child) {
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

    if (node->count > 1) {
        node->count--;
        return OK;
    }

    if (node->left != NULL && node->right != NULL) {
        BSTNode* succ = GetMin(node->right);
        node->data = succ->data;
        node->count = succ->count;
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

    if (node->count > 1) {
        node->count--;
        return OK;
    }

    if (node->left != NULL && node->right != NULL) {
        BSTNode* pred = GetMax(node->left);
        node->data = pred->data;
        node->count = pred->count;
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
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct WAdjNode {
    int              vertex;
    int              weight;
    struct WAdjNode* next;
} WAdjNode;

typedef struct {
    WAdjNode** heads;
    int        size;
    int        edgeCount;
} WALGraph;

typedef struct {
    int* parent;
    int* rank;
    int  size;
} UnionFind;

WALGraph* CreateGraph(int size);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

WALGraph* CreateGraph(int size)
{
    if (size <= 0) return NULL;
    WALGraph* g = (WALGraph*)malloc(sizeof(WALGraph));
    if (g == NULL) return NULL;
    g->heads = (WAdjNode**)malloc(sizeof(WAdjNode*) * size);
    if (g->heads == NULL) {
        free(g);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        g->heads[i] = NULL;
    }
    g->size = size;
    g->edgeCount = 0;
    return g;
}

WAdjNode* CreateWAdjNode(int vertex, int weight)
{
    WAdjNode* node = (WAdjNode*)malloc(sizeof(WAdjNode));
    if (node == NULL) return NULL;
    node->vertex = vertex;
    node->weight = weight;
    node->next = NULL;
    return node;
}

int HasEdge(WALGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || v < 0 || u >= g->size || v >= g->size || u == v)
        return 0;
    WAdjNode* cur = g->heads[u];
    while (cur != NULL) {
        if (cur->vertex == v) return 1;
        cur = cur->next;
    }
    return 0;
}

Status AddEdge(WALGraph* g, int u, int v, int w)
{
    if (g == NULL || u < 0 || v < 0 || u >= g->size || v >= g->size || u == v || w <= 0)
        return ERROR;
    if (HasEdge(g, u, v)) return ERROR;

    WAdjNode* node1 = CreateWAdjNode(v, w);
    if (node1 == NULL) return ERROR;
    WAdjNode* node2 = CreateWAdjNode(u, w);
    if (node2 == NULL) {
        free(node1);
        return ERROR;
    }
    node1->next = g->heads[u];
    g->heads[u] = node1;
    node2->next = g->heads[v];
    g->heads[v] = node2;
    g->edgeCount++;
    return OK;
}

static Status RemoveFromList(WAdjNode** head, int vertex)
{
    WAdjNode* cur = *head;
    WAdjNode* prev = NULL;
    while (cur != NULL) {
        if (cur->vertex == vertex) {
            if (prev == NULL) *head = cur->next;
            else prev->next = cur->next;
            free(cur);
            return OK;
        }
        prev = cur;
        cur = cur->next;
    }
    return ERROR;
}

Status RemoveEdge(WALGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || v < 0 || u >= g->size || v >= g->size || u == v)
        return ERROR;
    if (!HasEdge(g, u, v)) return ERROR;
    RemoveFromList(&g->heads[u], v);
    RemoveFromList(&g->heads[v], u);
    g->edgeCount--;
    return OK;
}

int GetWeight(WALGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || v < 0 || u >= g->size || v >= g->size || u == v)
        return 0;
    WAdjNode* cur = g->heads[u];
    while (cur != NULL) {
        if (cur->vertex == v) return cur->weight;
        cur = cur->next;
    }
    return 0;
}

int GetDegree(WALGraph* g, int v)
{
    if (g == NULL || v < 0 || v >= g->size) return -1;
    int degree = 0;
    WAdjNode* cur = g->heads[v];
    while (cur != NULL) {
        degree++;
        cur = cur->next;
    }
    return degree;
}

int GetNeighbors(WALGraph* g, int v, int* neighbors)
{
    if (g == NULL || neighbors == NULL || v < 0 || v >= g->size) return -1;
    int count = 0;
    WAdjNode* cur = g->heads[v];
    while (cur != NULL) {
        neighbors[count++] = cur->vertex;
        cur = cur->next;
    }
    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (neighbors[i] > neighbors[j]) {
                int tmp = neighbors[i];
                neighbors[i] = neighbors[j];
                neighbors[j] = tmp;
            }
        }
    }
    return count;
}

int GetEdgeCount(WALGraph* g)
{
    if (g == NULL) return 0;
    return g->edgeCount;
}

int GetVertexCount(WALGraph* g)
{
    if (g == NULL) return 0;
    return g->size;
}

void DFSVisit(WALGraph* g, int start, int* visited)
{
    if (g == NULL || visited == NULL || start < 0 || start >= g->size) return;
    if (visited[start]) return;
    visited[start] = 1;
    int* neighbors = (int*)malloc(sizeof(int) * g->size);
    if (neighbors == NULL) return;
    int cnt = GetNeighbors(g, start, neighbors);
    for (int i = 0; i < cnt; i++) {
        if (!visited[neighbors[i]]) DFSVisit(g, neighbors[i], visited);
    }
    free(neighbors);
}

int IsConnected(WALGraph* g)
{
    if (g == NULL || g->size == 0) return 0;
    if (g->size == 1) return 1;
    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) return 0;
    DFSVisit(g, 0, visited);
    for (int i = 0; i < g->size; i++) {
        if (!visited[i]) {
            free(visited);
            return 0;
        }
    }
    free(visited);
    return 1;
}

int GetConnectedComponents(WALGraph* g)
{
    if (g == NULL || g->size == 0) return 0;
    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) return 0;
    int components = 0;
    for (int i = 0; i < g->size; i++) {
        if (!visited[i]) {
            DFSVisit(g, i, visited);
            components++;
        }
    }
    free(visited);
    return components;
}

int GetMinEdge(WALGraph* g, int* u, int* v, int* w)
{
    if (g == NULL || u == NULL || v == NULL || w == NULL) return 0;
    if (g->edgeCount == 0) return 0;

    int minW = INT_MAX;
    int minU = -1, minV = -1;
    for (int i = 0; i < g->size; i++) {
        WAdjNode* cur = g->heads[i];
        while (cur != NULL) {
            int a = i, b = cur->vertex;
            if (a > b) {
                int tmp = a;
                a = b;
                b = tmp;
            }
            int wt = cur->weight;
            if (wt < minW || (wt == minW && a < minU) ||
                (wt == minW && a == minU && b < minV)) {
                minW = wt;
                minU = a;
                minV = b;
            }
            cur = cur->next;
        }
    }
    if (minU == -1) return 0;
    *u = minU;
    *v = minV;
    *w = minW;
    return 1;
}

int UFFind(UnionFind* uf, int x)
{
    if (uf == NULL || x < 0 || x >= uf->size) return -1;
    if (uf->parent[x] != x) uf->parent[x] = UFFind(uf, uf->parent[x]);
    return uf->parent[x];
}

Status UFUnion(UnionFind* uf, int x, int y)
{
    if (uf == NULL || x < 0 || x >= uf->size || y < 0 || y >= uf->size) return ERROR;
    int rootX = UFFind(uf, x);
    int rootY = UFFind(uf, y);
    if (rootX == rootY) return ERROR;
    if (uf->rank[rootX] < uf->rank[rootY]) {
        uf->parent[rootX] = rootY;
    } else if (uf->rank[rootX] > uf->rank[rootY]) {
        uf->parent[rootY] = rootX;
    } else {
        uf->parent[rootY] = rootX;
        uf->rank[rootX]++;
    }
    return OK;
}

int GetMSTWeight(int edges[][3], int cnt)
{
    if (edges == NULL || cnt <= 0) return 0;
    int total = 0;
    for (int i = 0; i < cnt; i++) total += edges[i][2];
    return total;
}

typedef struct {
    int u;
    int v;
    int w;
} EdgeInfo;

static int CompareEdges(const void* a, const void* b)
{
    const EdgeInfo* ea = (const EdgeInfo*)a;
    const EdgeInfo* eb = (const EdgeInfo*)b;
    if (ea->w != eb->w) return ea->w - eb->w;
    int minA = ea->u < ea->v ? ea->u : ea->v;
    int maxA = ea->u < ea->v ? ea->v : ea->u;
    int minB = eb->u < eb->v ? eb->u : eb->v;
    int maxB = eb->u < eb->v ? eb->v : eb->u;
    if (minA != minB) return minA - minB;
    return maxA - maxB;
}

int Kruskal(WALGraph* g, int edges[][3], int* cnt)
{
    if (g == NULL) return -1;
    if (g->size <= 1) {
        if (cnt != NULL) *cnt = 0;
        return 0;
    }
    if (!IsConnected(g)) return -1;

    int maxEdges = g->edgeCount;
    EdgeInfo* edgeList = (EdgeInfo*)malloc(sizeof(EdgeInfo) * maxEdges);
    if (edgeList == NULL) return -1;

    int ec = 0;
    for (int i = 0; i < g->size; i++) {
        WAdjNode* cur = g->heads[i];
        while (cur != NULL) {
            if (i < cur->vertex) {
                edgeList[ec].u = i;
                edgeList[ec].v = cur->vertex;
                edgeList[ec].w = cur->weight;
                ec++;
            }
            cur = cur->next;
        }
    }

    qsort(edgeList, ec, sizeof(EdgeInfo), CompareEdges);

    UnionFind uf;
    uf.size = g->size;
    uf.parent = (int*)malloc(sizeof(int) * g->size);
    uf.rank = (int*)calloc(g->size, sizeof(int));
    if (uf.parent == NULL || uf.rank == NULL) {
        free(edgeList);
        free(uf.parent);
        free(uf.rank);
        return -1;
    }
    for (int i = 0; i < g->size; i++) uf.parent[i] = i;

    int mstCnt = 0;
    for (int i = 0; i < ec && mstCnt < g->size - 1; i++) {
        int ru = UFFind(&uf, edgeList[i].u);
        int rv = UFFind(&uf, edgeList[i].v);
        if (ru != rv) {
            UFUnion(&uf, edgeList[i].u, edgeList[i].v);
            edges[mstCnt][0] = edgeList[i].u;
            edges[mstCnt][1] = edgeList[i].v;
            edges[mstCnt][2] = edgeList[i].w;
            mstCnt++;
        }
    }

    free(uf.parent);
    free(uf.rank);
    free(edgeList);

    if (mstCnt != g->size - 1) return -1;
    if (cnt != NULL) *cnt = mstCnt;
    return GetMSTWeight(edges, mstCnt);
}

int Prim(WALGraph* g, int edges[][3], int* cnt)
{
    if (g == NULL) return -1;
    if (g->size <= 1) {
        if (cnt != NULL) *cnt = 0;
        return 0;
    }
    if (!IsConnected(g)) return -1;

    int* inMST = (int*)calloc(g->size, sizeof(int));
    int* key = (int*)malloc(sizeof(int) * g->size);
    int* parent = (int*)malloc(sizeof(int) * g->size);
    if (inMST == NULL || key == NULL || parent == NULL) {
        free(inMST);
        free(key);
        free(parent);
        return -1;
    }

    for (int i = 0; i < g->size; i++) {
        key[i] = INT_MAX;
        parent[i] = -1;
    }

    inMST[0] = 1;
    WAdjNode* cur = g->heads[0];
    while (cur != NULL) {
        key[cur->vertex] = cur->weight;
        parent[cur->vertex] = 0;
        cur = cur->next;
    }

    for (int step = 1; step < g->size; step++) {
        int bestW = INT_MAX;
        int bestTo = -1;
        int bestFrom = -1;

        for (int v = 0; v < g->size; v++) {
            if (!inMST[v] && key[v] < bestW) {
                bestW = key[v];
                bestTo = v;
                bestFrom = parent[v];
            } else if (!inMST[v] && key[v] == bestW) {
                if (bestTo == -1 || v < bestTo) {
                    bestTo = v;
                    bestFrom = parent[v];
                } else if (v == bestTo && parent[v] < bestFrom) {
                    bestFrom = parent[v];
                }
            }
        }

        if (bestTo == -1) {
            free(inMST);
            free(key);
            free(parent);
            return -1;
        }

        inMST[bestTo] = 1;
        cur = g->heads[bestTo];
        while (cur != NULL) {
            int nb = cur->vertex;
            if (!inMST[nb]) {
                int w = cur->weight;
                if (w < key[nb]) {
                    key[nb] = w;
                    parent[nb] = bestTo;
                } else if (w == key[nb] && bestTo < parent[nb]) {
                    parent[nb] = bestTo;
                }
            }
            cur = cur->next;
        }
    }

    int mstCnt = 0;
    for (int i = 1; i < g->size; i++) {
        int from = parent[i];
        int to = i;
        int w = GetWeight(g, from, to);
        if (from < to) {
            edges[mstCnt][0] = from;
            edges[mstCnt][1] = to;
        } else {
            edges[mstCnt][0] = to;
            edges[mstCnt][1] = from;
        }
        edges[mstCnt][2] = w;
        mstCnt++;
    }

    if (cnt != NULL) *cnt = mstCnt;
    int total = GetMSTWeight(edges, mstCnt);

    free(inMST);
    free(key);
    free(parent);
    return total;
}

void DestroyGraph(WALGraph** pg)
{
    if (pg == NULL || *pg == NULL) return;
    WALGraph* g = *pg;
    for (int i = 0; i < g->size; i++) {
        WAdjNode* cur = g->heads[i];
        while (cur != NULL) {
            WAdjNode* next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(g->heads);
    free(g);
    *pg = NULL;
}

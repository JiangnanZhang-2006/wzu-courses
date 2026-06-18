#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct {
    int** matrix;
    int   size;
    int   edgeCount;
} WGraph;

typedef struct {
    int* parent;
    int* rank;
    int  size;
} UnionFind;

WGraph* CreateGraph(int size);
Status  AddEdge(WGraph* g, int u, int v, int w);
Status  RemoveEdge(WGraph* g, int u, int v);
int     HasEdge(WGraph* g, int u, int v);
int     GetWeight(WGraph* g, int u, int v);
int     GetDegree(WGraph* g, int v);
int     GetNeighbors(WGraph* g, int v, int* neighbors);
int     GetEdgeCount(WGraph* g);
int     GetVertexCount(WGraph* g);
void    DFSVisit(WGraph* g, int start, int* visited);
int     IsConnected(WGraph* g);
int     GetConnectedComponents(WGraph* g);
int     GetMinEdge(WGraph* g, int* u, int* v, int* w);
int     GetMSTWeight(int edges[][3], int cnt);
int     Prim(WGraph* g, int edges[][3], int* cnt);
int     Kruskal(WGraph* g, int edges[][3], int* cnt);
void    DestroyGraph(WGraph** pg);
int     GetMinWeight(WGraph* g);
int     CountEdgesByWeight(WGraph* g, int lo, int hi);
int     IsConnectedAfterRemove(WGraph* g, int u, int v);
int     GetMSTTotalWeight(WGraph* g);
int     GetMSTMaxEdge(WGraph* g, int* u, int* v, int* w);
int     IsMST(WGraph* g, int edges[][3], int cnt);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

static int IsValidVertex(WGraph* g, int v)
{
    return g != NULL && v >= 0 && v < g->size;
}

static int IsValidEdgeEndpoints(WGraph* g, int u, int v)
{
    return IsValidVertex(g, u) && IsValidVertex(g, v) && u != v;
}

static int CompareEdges(int u1, int v1, int w1, int u2, int v2, int w2)
{
    if (w1 != w2) return w1 - w2;
    int min1 = u1 < v1 ? u1 : v1;
    int min2 = u2 < v2 ? u2 : v2;
    if (min1 != min2) return min1 - min2;
    int max1 = u1 > v1 ? u1 : v1;
    int max2 = u2 > v2 ? u2 : v2;
    return max1 - max2;
}

static int ComparePrimCandidate(
    int from1, int to1, int w1, int from2, int to2, int w2)
{
    if (w1 != w2) return w1 - w2;
    if (to1 != to2) return to1 - to2;
    return from1 - from2;
}

static UnionFind* UFCreate(int size)
{
    if (size <= 0) return NULL;
    UnionFind* uf = (UnionFind*)malloc(sizeof(UnionFind));
    if (uf == NULL) return NULL;
    uf->parent = (int*)malloc(sizeof(int) * size);
    uf->rank = (int*)malloc(sizeof(int) * size);
    if (uf->parent == NULL || uf->rank == NULL) {
        free(uf->parent);
        free(uf->rank);
        free(uf);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        uf->parent[i] = i;
        uf->rank[i] = 0;
    }
    uf->size = size;
    return uf;
}

static int UFFind(UnionFind* uf, int x)
{
    if (uf->parent[x] != x) {
        uf->parent[x] = UFFind(uf, uf->parent[x]);
    }
    return uf->parent[x];
}

static int UFUnion(UnionFind* uf, int x, int y)
{
    int rx = UFFind(uf, x);
    int ry = UFFind(uf, y);
    if (rx == ry) return 0;
    if (uf->rank[rx] < uf->rank[ry]) {
        uf->parent[rx] = ry;
    } else if (uf->rank[rx] > uf->rank[ry]) {
        uf->parent[ry] = rx;
    } else {
        uf->parent[ry] = rx;
        uf->rank[rx]++;
    }
    return 1;
}

static void UFDestroy(UnionFind* uf)
{
    if (uf == NULL) return;
    free(uf->parent);
    free(uf->rank);
    free(uf);
}

WGraph* CreateGraph(int size)
{
    if (size <= 0) return NULL;
    WGraph* g = (WGraph*)malloc(sizeof(WGraph));
    if (g == NULL) return NULL;
    g->matrix = (int**)malloc(sizeof(int*) * size);
    if (g->matrix == NULL) {
        free(g);
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        g->matrix[i] = (int*)calloc(size, sizeof(int));
        if (g->matrix[i] == NULL) {
            for (int j = 0; j < i; j++) {
                free(g->matrix[j]);
            }
            free(g->matrix);
            free(g);
            return NULL;
        }
    }
    g->size = size;
    g->edgeCount = 0;
    return g;
}

Status AddEdge(WGraph* g, int u, int v, int w)
{
    if (!IsValidEdgeEndpoints(g, u, v) || w <= 0) return ERROR;
    if (g->matrix[u][v] != 0) return ERROR;
    g->matrix[u][v] = w;
    g->matrix[v][u] = w;
    g->edgeCount++;
    return OK;
}

Status RemoveEdge(WGraph* g, int u, int v)
{
    if (!IsValidEdgeEndpoints(g, u, v)) return ERROR;
    if (g->matrix[u][v] == 0) return ERROR;
    g->matrix[u][v] = 0;
    g->matrix[v][u] = 0;
    g->edgeCount--;
    return OK;
}

int HasEdge(WGraph* g, int u, int v)
{
    if (!IsValidEdgeEndpoints(g, u, v)) return 0;
    return g->matrix[u][v] != 0;
}

int GetWeight(WGraph* g, int u, int v)
{
    if (!IsValidEdgeEndpoints(g, u, v)) return 0;
    return g->matrix[u][v];
}

int GetDegree(WGraph* g, int v)
{
    if (!IsValidVertex(g, v)) return -1;
    int degree = 0;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[v][i] != 0) degree++;
    }
    return degree;
}

int GetNeighbors(WGraph* g, int v, int* neighbors)
{
    if (!IsValidVertex(g, v) || neighbors == NULL) return -1;
    int count = 0;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[v][i] != 0) {
            neighbors[count++] = i;
        }
    }
    return count;
}

int GetEdgeCount(WGraph* g)
{
    if (g == NULL) return 0;
    return g->edgeCount;
}

int GetVertexCount(WGraph* g)
{
    if (g == NULL) return 0;
    return g->size;
}

void DFSVisit(WGraph* g, int start, int* visited)
{
    if (!IsValidVertex(g, start) || visited == NULL) return;
    visited[start] = 1;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[start][i] != 0 && !visited[i]) {
            DFSVisit(g, i, visited);
        }
    }
}

int IsConnected(WGraph* g)
{
    if (g == NULL || g->size == 0) return 0;
    if (g->size == 1) return 1;
    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) return 0;
    DFSVisit(g, 0, visited);
    int connected = 1;
    for (int i = 0; i < g->size; i++) {
        if (!visited[i]) {
            connected = 0;
            break;
        }
    }
    free(visited);
    return connected;
}

int GetConnectedComponents(WGraph* g)
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

int GetMinEdge(WGraph* g, int* u, int* v, int* w)
{
    if (g == NULL || u == NULL || v == NULL || w == NULL) return 0;
    int found = 0;
    int bestU = 0, bestV = 0, bestW = 0;
    for (int i = 0; i < g->size; i++) {
        for (int j = i + 1; j < g->size; j++) {
            int weight = g->matrix[i][j];
            if (weight == 0) continue;
            if (!found || CompareEdges(i, j, weight, bestU, bestV, bestW) < 0) {
                bestU = i;
                bestV = j;
                bestW = weight;
                found = 1;
            }
        }
    }
    if (!found) return 0;
    *u = bestU;
    *v = bestV;
    *w = bestW;
    return 1;
}

int GetMSTWeight(int edges[][3], int cnt)
{
    if (edges == NULL || cnt <= 0) return 0;
    int total = 0;
    for (int i = 0; i < cnt; i++) {
        total += edges[i][2];
    }
    return total;
}

int Prim(WGraph* g, int edges[][3], int* cnt)
{
    if (g == NULL || edges == NULL || cnt == NULL) return -1;
    if (!IsConnected(g)) return -1;

    int n = g->size;
    int* inMST = (int*)calloc(n, sizeof(int));
    if (inMST == NULL) return -1;
    inMST[0] = 1;
    int mstCount = 0;

    while (mstCount < n - 1) {
        int found = 0;
        int bestFrom = -1, bestTo = -1, bestW = 0;

        for (int u = 0; u < n; u++) {
            if (!inMST[u]) continue;
            for (int v = 0; v < n; v++) {
                if (inMST[v]) continue;
                int weight = g->matrix[u][v];
                if (weight == 0) continue;
                if (!found) {
                    found = 1;
                    bestFrom = u;
                    bestTo = v;
                    bestW = weight;
                } else {
                    int cmp = ComparePrimCandidate(
                        u, v, weight, bestFrom, bestTo, bestW);
                    if (cmp < 0) {
                        bestFrom = u;
                        bestTo = v;
                        bestW = weight;
                    }
                }
            }
        }

        if (!found) {
            free(inMST);
            return -1;
        }

        int eu = bestFrom < bestTo ? bestFrom : bestTo;
        int ev = bestFrom < bestTo ? bestTo : bestFrom;
        edges[mstCount][0] = eu;
        edges[mstCount][1] = ev;
        edges[mstCount][2] = bestW;
        mstCount++;
        inMST[bestTo] = 1;
    }

    *cnt = mstCount;
    int total = GetMSTWeight(edges, mstCount);
    free(inMST);
    return total;
}

int Kruskal(WGraph* g, int edges[][3], int* cnt)
{
    if (g == NULL || edges == NULL || cnt == NULL) return -1;

    int maxEdges = g->size * (g->size - 1) / 2;
    int (*allEdges)[3] = (int (*)[3])malloc(sizeof(int[3]) * maxEdges);
    if (allEdges == NULL) return -1;

    int edgeNum = 0;
    for (int i = 0; i < g->size; i++) {
        for (int j = i + 1; j < g->size; j++) {
            if (g->matrix[i][j] != 0) {
                allEdges[edgeNum][0] = i;
                allEdges[edgeNum][1] = j;
                allEdges[edgeNum][2] = g->matrix[i][j];
                edgeNum++;
            }
        }
    }

    for (int i = 0; i < edgeNum - 1; i++) {
        for (int j = i + 1; j < edgeNum; j++) {
            int cmp = CompareEdges(
                allEdges[i][0], allEdges[i][1], allEdges[i][2],
                allEdges[j][0], allEdges[j][1], allEdges[j][2]);
            if (cmp > 0) {
                int tmp[3];
                tmp[0] = allEdges[i][0];
                tmp[1] = allEdges[i][1];
                tmp[2] = allEdges[i][2];
                allEdges[i][0] = allEdges[j][0];
                allEdges[i][1] = allEdges[j][1];
                allEdges[i][2] = allEdges[j][2];
                allEdges[j][0] = tmp[0];
                allEdges[j][1] = tmp[1];
                allEdges[j][2] = tmp[2];
            }
        }
    }

    UnionFind* uf = UFCreate(g->size);
    if (uf == NULL) {
        free(allEdges);
        return -1;
    }

    int mstCount = 0;
    for (int i = 0; i < edgeNum && mstCount < g->size - 1; i++) {
        int u = allEdges[i][0];
        int v = allEdges[i][1];
        if (UFUnion(uf, u, v)) {
            edges[mstCount][0] = u;
            edges[mstCount][1] = v;
            edges[mstCount][2] = allEdges[i][2];
            mstCount++;
        }
    }

    UFDestroy(uf);
    free(allEdges);

    if (mstCount != g->size - 1) {
        return -1;
    }

    *cnt = mstCount;
    return GetMSTWeight(edges, mstCount);
}

void DestroyGraph(WGraph** pg)
{
    if (pg == NULL || *pg == NULL) return;
    WGraph* g = *pg;
    if (g->matrix != NULL) {
        for (int i = 0; i < g->size; i++) {
            free(g->matrix[i]);
        }
        free(g->matrix);
    }
    free(g);
    *pg = NULL;
}

int GetMinWeight(WGraph* g)
{
    int u, v, w;
    if (!GetMinEdge(g, &u, &v, &w)) return -1;
    return w;
}

int CountEdgesByWeight(WGraph* g, int lo, int hi)
{
    if (g == NULL || lo > hi) return -1;
    int count = 0;
    for (int i = 0; i < g->size; i++) {
        for (int j = i + 1; j < g->size; j++) {
            int weight = g->matrix[i][j];
            if (weight != 0 && weight >= lo && weight <= hi) {
                count++;
            }
        }
    }
    return count;
}

int IsConnectedAfterRemove(WGraph* g, int u, int v)
{
    if (!IsValidEdgeEndpoints(g, u, v) || !HasEdge(g, u, v)) return -1;
    int weight = g->matrix[u][v];
    RemoveEdge(g, u, v);
    int connected = IsConnected(g);
    AddEdge(g, u, v, weight);
    return connected;
}

int GetMSTTotalWeight(WGraph* g)
{
    if (g == NULL) return -1;
    int edges[20][3];
    int cnt = 0;
    return Kruskal(g, edges, &cnt);
}

int GetMSTMaxEdge(WGraph* g, int* u, int* v, int* w)
{
    if (g == NULL || u == NULL || v == NULL || w == NULL) return 0;
    int edges[20][3];
    int cnt = 0;
    if (Prim(g, edges, &cnt) == -1) return 0;

    int found = 0;
    int bestU = 0, bestV = 0, bestW = 0;
    for (int i = 0; i < cnt; i++) {
        int eu = edges[i][0];
        int ev = edges[i][1];
        int ew = edges[i][2];
        if (!found) {
            bestU = eu;
            bestV = ev;
            bestW = ew;
            found = 1;
        } else if (ew > bestW) {
            bestU = eu;
            bestV = ev;
            bestW = ew;
        } else if (ew == bestW && CompareEdges(eu, ev, ew, bestU, bestV, bestW) < 0) {
            bestU = eu;
            bestV = ev;
            bestW = ew;
        }
    }

    if (!found) return 0;
    *u = bestU;
    *v = bestV;
    *w = bestW;
    return 1;
}

static int IsEdgeSetConnected(int size, int edges[][3], int cnt)
{
    if (size <= 0) return 0;
    UnionFind* uf = UFCreate(size);
    if (uf == NULL) return 0;
    for (int i = 0; i < cnt; i++) {
        UFUnion(uf, edges[i][0], edges[i][1]);
    }
    int root = UFFind(uf, 0);
    int connected = 1;
    for (int i = 1; i < size; i++) {
        if (UFFind(uf, i) != root) {
            connected = 0;
            break;
        }
    }
    UFDestroy(uf);
    return connected;
}

int IsMST(WGraph* g, int edges[][3], int cnt)
{
    if (g == NULL || edges == NULL || cnt <= 0) return -1;
    if (cnt != g->size - 1) return 0;

    for (int i = 0; i < cnt; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int w = edges[i][2];
        if (!IsValidEdgeEndpoints(g, u, v) || GetWeight(g, u, v) != w) {
            return 0;
        }
    }

    if (!IsEdgeSetConnected(g->size, edges, cnt)) return 0;

    int mstEdges[20][3];
    int mstCnt = 0;
    int mstWeight = Prim(g, mstEdges, &mstCnt);
    if (mstWeight == -1) return 0;

    if (GetMSTWeight(edges, cnt) != mstWeight) return 0;
    return 1;
}

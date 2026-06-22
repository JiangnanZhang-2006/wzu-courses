#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct WDAdjNode {
    int               vertex;
    int               weight;
    struct WDAdjNode* next;
} WDAdjNode;

typedef struct {
    WDAdjNode** heads;
    int         size;
    int         edgeCount;
} WDALGraph;

WDALGraph* CreateGraph(int size);
WDAdjNode* CreateWDAdjNode(int vertex, int weight);
Status     AddEdge(WDALGraph* g, int u, int v, int w);
Status     RemoveEdge(WDALGraph* g, int u, int v);
int        HasEdge(WDALGraph* g, int u, int v);
int        GetWeight(WDALGraph* g, int u, int v);
int        GetOutDegree(WDALGraph* g, int v);
int        GetInDegree(WDALGraph* g, int v);
int        GetNeighbors(WDALGraph* g, int v, int* neighbors);
int        GetEdgeCount(WDALGraph* g);
int        GetVertexCount(WDALGraph* g);
void       DFSVisit(WDALGraph* g, int start, int* visited);
int        IsReachable(WDALGraph* g, int u, int v);
Status     Dijkstra(WDALGraph* g, int src, int* dist, int* prev);
int        GetShortestPath(WDALGraph* g, int src, int dst);
int        GetShortestPathSeq(WDALGraph* g, int src, int dst, int* path);
void       DestroyGraph(WDALGraph** pg);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

static int IsValidVertex(WDALGraph* g, int v)
{
    return g != NULL && v >= 0 && v < g->size;
}

WDALGraph* CreateGraph(int size)
{
    if (size <= 0) return NULL;

    WDALGraph* g = (WDALGraph*)malloc(sizeof(WDALGraph));
    if (g == NULL) return NULL;

    g->heads = (WDAdjNode**)malloc(sizeof(WDAdjNode*) * size);
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

WDAdjNode* CreateWDAdjNode(int vertex, int weight)
{
    WDAdjNode* node = (WDAdjNode*)malloc(sizeof(WDAdjNode));
    if (node == NULL) return NULL;

    node->vertex = vertex;
    node->weight = weight;
    node->next = NULL;
    return node;
}

int HasEdge(WDALGraph* g, int u, int v)
{
    if (!IsValidVertex(g, u) || !IsValidVertex(g, v)) return 0;

    WDAdjNode* cur = g->heads[u];
    while (cur != NULL) {
        if (cur->vertex == v) return 1;
        cur = cur->next;
    }
    return 0;
}

Status AddEdge(WDALGraph* g, int u, int v, int w)
{
    if (g == NULL || !IsValidVertex(g, u) || !IsValidVertex(g, v) || u == v || w == 0 ||
        HasEdge(g, u, v))
        return ERROR;

    WDAdjNode* node = CreateWDAdjNode(v, w);
    if (node == NULL) return ERROR;

    node->next = g->heads[u];
    g->heads[u] = node;
    g->edgeCount++;
    return OK;
}

Status RemoveEdge(WDALGraph* g, int u, int v)
{
    if (g == NULL || !IsValidVertex(g, u) || !IsValidVertex(g, v) || !HasEdge(g, u, v))
        return ERROR;

    WDAdjNode* cur = g->heads[u];
    WDAdjNode* prev = NULL;
    while (cur != NULL) {
        if (cur->vertex == v) {
            if (prev == NULL)
                g->heads[u] = cur->next;
            else
                prev->next = cur->next;
            free(cur);
            g->edgeCount--;
            return OK;
        }
        prev = cur;
        cur = cur->next;
    }
    return ERROR;
}

int GetWeight(WDALGraph* g, int u, int v)
{
    if (!IsValidVertex(g, u) || !IsValidVertex(g, v)) return 0;

    WDAdjNode* cur = g->heads[u];
    while (cur != NULL) {
        if (cur->vertex == v) return cur->weight;
        cur = cur->next;
    }
    return 0;
}

int GetOutDegree(WDALGraph* g, int v)
{
    if (!IsValidVertex(g, v)) return -1;

    int count = 0;
    WDAdjNode* cur = g->heads[v];
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }
    return count;
}

int GetInDegree(WDALGraph* g, int v)
{
    if (!IsValidVertex(g, v)) return -1;

    int count = 0;
    for (int i = 0; i < g->size; i++) {
        WDAdjNode* cur = g->heads[i];
        while (cur != NULL) {
            if (cur->vertex == v) count++;
            cur = cur->next;
        }
    }
    return count;
}

static int CompareInt(const void* a, const void* b)
{
    return *(const int*)a - *(const int*)b;
}

int GetNeighbors(WDALGraph* g, int v, int* neighbors)
{
    if (g == NULL || neighbors == NULL || !IsValidVertex(g, v)) return -1;

    int count = GetOutDegree(g, v);
    if (count <= 0) return count;

    int idx = 0;
    WDAdjNode* cur = g->heads[v];
    while (cur != NULL) {
        neighbors[idx++] = cur->vertex;
        cur = cur->next;
    }
    qsort(neighbors, count, sizeof(int), CompareInt);
    return count;
}

int GetEdgeCount(WDALGraph* g)
{
    if (g == NULL) return 0;
    return g->edgeCount;
}

int GetVertexCount(WDALGraph* g)
{
    if (g == NULL) return 0;
    return g->size;
}

void DFSVisit(WDALGraph* g, int start, int* visited)
{
    if (g == NULL || visited == NULL || start < 0 || start >= g->size) return;

    int* neighbors = (int*)malloc(sizeof(int) * g->size);
    int* stack = (int*)malloc(sizeof(int) * g->size);
    if (neighbors == NULL || stack == NULL) {
        free(neighbors);
        free(stack);
        visited[start] = 1;
        return;
    }

    int top = 0;
    stack[top++] = start;
    while (top > 0) {
        int v = stack[--top];
        if (visited[v]) continue;
        visited[v] = 1;
        int count = GetNeighbors(g, v, neighbors);
        if (count <= 0) continue;
        for (int i = count - 1; i >= 0; i--) {
            int nb = neighbors[i];
            if (!visited[nb]) stack[top++] = nb;
        }
    }

    free(neighbors);
    free(stack);
}

int IsReachable(WDALGraph* g, int u, int v)
{
    if (g == NULL || !IsValidVertex(g, u) || !IsValidVertex(g, v)) return 0;
    if (u == v) return 1;

    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) return 0;

    DFSVisit(g, u, visited);
    int result = visited[v];
    free(visited);
    return result;
}

Status Dijkstra(WDALGraph* g, int src, int* dist, int* prev)
{
    if (g == NULL || dist == NULL || prev == NULL || !IsValidVertex(g, src)) return ERROR;

    int n = g->size;
    int* visited = (int*)calloc(n, sizeof(int));
    if (visited == NULL) return ERROR;

    for (int i = 0; i < n; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[src] = 0;

    for (int step = 0; step < n; step++) {
        int u = -1;
        for (int i = 0; i < n; i++) {
            if (visited[i]) continue;
            if (dist[i] == INT_MAX) continue;
            if (u == -1 || dist[i] < dist[u] || (dist[i] == dist[u] && i < u)) u = i;
        }
        if (u == -1) break;

        visited[u] = 1;
        WDAdjNode* cur = g->heads[u];
        while (cur != NULL) {
            int v = cur->vertex;
            int w = cur->weight;
            if (dist[u] != INT_MAX) {
                long long nd = (long long)dist[u] + w;
                if (nd < dist[v]) {
                    dist[v] = (int)nd;
                    prev[v] = u;
                } else if (nd == dist[v] && u < prev[v]) {
                    prev[v] = u;
                }
            }
            cur = cur->next;
        }
    }

    free(visited);
    return OK;
}

int GetShortestPath(WDALGraph* g, int src, int dst)
{
    if (g == NULL || !IsValidVertex(g, src) || !IsValidVertex(g, dst)) return -1;

    int* dist = (int*)malloc(sizeof(int) * g->size);
    int* prev = (int*)malloc(sizeof(int) * g->size);
    if (dist == NULL || prev == NULL) {
        free(dist);
        free(prev);
        return -1;
    }

    if (Dijkstra(g, src, dist, prev) == ERROR) {
        free(dist);
        free(prev);
        return -1;
    }

    int result = dist[dst];
    free(dist);
    free(prev);
    if (result == INT_MAX) return -1;
    return result;
}

int GetShortestPathSeq(WDALGraph* g, int src, int dst, int* path)
{
    if (g == NULL || path == NULL || !IsValidVertex(g, src) || !IsValidVertex(g, dst))
        return -1;

    int* dist = (int*)malloc(sizeof(int) * g->size);
    int* prev = (int*)malloc(sizeof(int) * g->size);
    if (dist == NULL || prev == NULL) {
        free(dist);
        free(prev);
        return -1;
    }

    if (Dijkstra(g, src, dist, prev) == ERROR) {
        free(dist);
        free(prev);
        return -1;
    }

    if (dist[dst] == INT_MAX) {
        free(dist);
        free(prev);
        return -1;
    }

    int* temp = (int*)malloc(sizeof(int) * g->size);
    if (temp == NULL) {
        free(dist);
        free(prev);
        return -1;
    }

    int len = 0;
    int cur = dst;
    while (cur != -1) {
        temp[len++] = cur;
        if (cur == src) break;
        cur = prev[cur];
    }

    if (cur != src) {
        free(dist);
        free(prev);
        free(temp);
        return -1;
    }

    for (int i = 0; i < len; i++) {
        path[i] = temp[len - 1 - i];
    }

    free(dist);
    free(prev);
    free(temp);
    return len;
}

void DestroyGraph(WDALGraph** pg)
{
    if (pg == NULL || *pg == NULL) return;

    WDALGraph* g = *pg;
    for (int i = 0; i < g->size; i++) {
        WDAdjNode* cur = g->heads[i];
        while (cur != NULL) {
            WDAdjNode* next = cur->next;
            free(cur);
            cur = next;
        }
    }
    free(g->heads);
    free(g);
    *pg = NULL;
}

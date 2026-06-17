#include <stdio.h>
#include <stdlib.h>

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
int        GetOutDegree(WDALGraph* g, int v);
int        GetInDegree(WDALGraph* g, int v);
int        GetNeighbors(WDALGraph* g, int v, int* neighbors);
int        GetEdgeCount(WDALGraph* g);
int        GetVertexCount(WDALGraph* g);
int        IsDAG(WDALGraph* g);
int        TopoSortKahn(WDALGraph* g, int* seq);
int        TopoSortDFS(WDALGraph* g, int* seq);
int        GetLongestPath(WDALGraph* g);
void       DestroyGraph(WDALGraph** pg);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

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
    if (g == NULL || u < 0 || u >= g->size || v < 0 || v >= g->size || u == v) {
        return 0;
    }
    WDAdjNode* cur = g->heads[u];
    while (cur != NULL) {
        if (cur->vertex == v) return 1;
        cur = cur->next;
    }
    return 0;
}

Status AddEdge(WDALGraph* g, int u, int v, int w)
{
    if (g == NULL || u < 0 || u >= g->size || v < 0 || v >= g->size || u == v || w == 0) {
        return ERROR;
    }
    if (HasEdge(g, u, v)) return ERROR;
    WDAdjNode* node = CreateWDAdjNode(v, w);
    if (node == NULL) return ERROR;
    node->next = g->heads[u];
    g->heads[u] = node;
    g->edgeCount++;
    return OK;
}

Status RemoveEdge(WDALGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || u >= g->size || v < 0 || v >= g->size || u == v) {
        return ERROR;
    }
    WDAdjNode* cur = g->heads[u];
    WDAdjNode* prev = NULL;
    while (cur != NULL) {
        if (cur->vertex == v) {
            if (prev == NULL) {
                g->heads[u] = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            g->edgeCount--;
            return OK;
        }
        prev = cur;
        cur = cur->next;
    }
    return ERROR;
}

int GetOutDegree(WDALGraph* g, int v)
{
    if (g == NULL || v < 0 || v >= g->size) return -1;
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
    if (g == NULL || v < 0 || v >= g->size) return -1;
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

static int compareInt(const void* a, const void* b)
{
    return *(const int*)a - *(const int*)b;
}

int GetNeighbors(WDALGraph* g, int v, int* neighbors)
{
    if (g == NULL || v < 0 || v >= g->size || neighbors == NULL) return -1;
    int count = 0;
    WDAdjNode* cur = g->heads[v];
    while (cur != NULL) {
        neighbors[count++] = cur->vertex;
        cur = cur->next;
    }
    if (count > 1) {
        qsort(neighbors, count, sizeof(int), compareInt);
    }
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

int IsDAG(WDALGraph* g)
{
    if (g == NULL || g->size == 0) return 0;
    int* inDegree = (int*)malloc(sizeof(int) * g->size);
    if (inDegree == NULL) return 0;
    for (int i = 0; i < g->size; i++) {
        inDegree[i] = GetInDegree(g, i);
    }
    int sorted = 0;
    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) {
        free(inDegree);
        return 0;
    }
    while (sorted < g->size) {
        int found = -1;
        for (int i = 0; i < g->size; i++) {
            if (!visited[i] && inDegree[i] == 0) {
                found = i;
                break;
            }
        }
        if (found == -1) {
            free(inDegree);
            free(visited);
            return 0;
        }
        visited[found] = 1;
        int* neighbors = (int*)malloc(sizeof(int) * g->size);
        if (neighbors == NULL) {
            free(inDegree);
            free(visited);
            return 0;
        }
        int n = GetNeighbors(g, found, neighbors);
        for (int i = 0; i < n; i++) {
            inDegree[neighbors[i]]--;
        }
        free(neighbors);
        sorted++;
    }
    free(inDegree);
    free(visited);
    return 1;
}

int TopoSortKahn(WDALGraph* g, int* seq)
{
    if (g == NULL) return 0;
    int* inDegree = (int*)malloc(sizeof(int) * g->size);
    if (inDegree == NULL) return 0;
    for (int i = 0; i < g->size; i++) {
        inDegree[i] = GetInDegree(g, i);
    }
    int count = 0;
    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) {
        free(inDegree);
        return 0;
    }
    while (count < g->size) {
        int found = -1;
        for (int i = 0; i < g->size; i++) {
            if (!visited[i] && inDegree[i] == 0) {
                found = i;
                break;
            }
        }
        if (found == -1) break;
        visited[found] = 1;
        seq[count++] = found;
        int* neighbors = (int*)malloc(sizeof(int) * g->size);
        if (neighbors == NULL) {
            free(inDegree);
            free(visited);
            return count;
        }
        int n = GetNeighbors(g, found, neighbors);
        for (int i = 0; i < n; i++) {
            inDegree[neighbors[i]]--;
        }
        free(neighbors);
    }
    free(inDegree);
    free(visited);
    return count;
}

static int dfsVisit(WDALGraph* g, int v, int* state, int* stack, int* top)
{
    state[v] = 1;
    int* neighbors = (int*)malloc(sizeof(int) * g->size);
    if (neighbors == NULL) return 0;
    int n = GetNeighbors(g, v, neighbors);
    for (int i = 0; i < n; i++) {
        int u = neighbors[i];
        if (state[u] == 1) {
            free(neighbors);
            return 0;
        }
        if (state[u] == 0 && !dfsVisit(g, u, state, stack, top)) {
            free(neighbors);
            return 0;
        }
    }
    free(neighbors);
    state[v] = 2;
    stack[(*top)++] = v;
    return 1;
}

int TopoSortDFS(WDALGraph* g, int* seq)
{
    if (g == NULL) return -1;
    int* state = (int*)calloc(g->size, sizeof(int));
    if (state == NULL) return -1;
    int* stack = (int*)malloc(sizeof(int) * g->size);
    if (stack == NULL) {
        free(state);
        return -1;
    }
    int top = 0;
    for (int i = 0; i < g->size; i++) {
        if (state[i] == 0 && !dfsVisit(g, i, state, stack, &top)) {
            free(state);
            free(stack);
            return -1;
        }
    }
    for (int i = 0; i < top; i++) {
        seq[i] = stack[top - 1 - i];
    }
    free(state);
    free(stack);
    return top;
}

int GetLongestPath(WDALGraph* g)
{
    if (g == NULL || !IsDAG(g)) return -1;
    if (g->edgeCount == 0) return 0;
    int* dist = (int*)calloc(g->size, sizeof(int));
    if (dist == NULL) return -1;
    int* seq = (int*)malloc(sizeof(int) * g->size);
    if (seq == NULL) {
        free(dist);
        return -1;
    }
    if (TopoSortKahn(g, seq) != g->size) {
        free(dist);
        free(seq);
        return -1;
    }
    int maxDist = 0;
    for (int i = 0; i < g->size; i++) {
        int v = seq[i];
        WDAdjNode* cur = g->heads[v];
        while (cur != NULL) {
            int nd = dist[v] + cur->weight;
            if (nd > dist[cur->vertex]) {
                dist[cur->vertex] = nd;
            }
            cur = cur->next;
        }
        if (dist[v] > maxDist) maxDist = dist[v];
    }
    for (int i = 0; i < g->size; i++) {
        if (dist[i] > maxDist) maxDist = dist[i];
    }
    free(dist);
    free(seq);
    return maxDist;
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

#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct {
    int** matrix;
    int   size;
    int   edgeCount;
} MGraph;

MGraph* CreateGraph(int size);
Status AddEdge(MGraph* g, int u, int v);
int HasEdge(MGraph* g, int u, int v);
int GetDegree(MGraph* g, int v);
int GetNeighbors(MGraph* g, int v, int* neighbors);
int GetEdgeCount(MGraph* g);
int GetVertexCount(MGraph* g);
void DFS(MGraph* g, int start, int* seq, int* cnt);
void BFS(MGraph* g, int start, int* seq, int* cnt);
int IsConnected(MGraph* g);
int GetConnectedComponents(MGraph* g);
Status RemoveEdge(MGraph* g, int u, int v);
void DestroyGraph(MGraph** pg);
int CountVerticesByDegree(MGraph* g, int k);
int GetMaxDegreeVertex(MGraph* g);
int GetComponentSizes(MGraph* g, int* sizes);
Status RemoveVertex(MGraph* g, int v);
int ShortestPath(MGraph* g, int src, int dst);
int IsTree(MGraph* g);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

static void dfsVisit(MGraph* g, int v, int* visited, int* seq, int* cnt)
{
    visited[v] = 1;
    seq[(*cnt)++] = v;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[v][i] == 1 && !visited[i]) {
            dfsVisit(g, i, visited, seq, cnt);
        }
    }
}

MGraph* CreateGraph(int size)
{
    if (size <= 0) return NULL;

    MGraph* g = (MGraph*)malloc(sizeof(MGraph));
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

Status AddEdge(MGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || u >= g->size || v < 0 || v >= g->size || u == v) {
        return ERROR;
    }
    if (g->matrix[u][v] == 1) return ERROR;

    g->matrix[u][v] = 1;
    g->matrix[v][u] = 1;
    g->edgeCount++;
    return OK;
}

int HasEdge(MGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || u >= g->size || v < 0 || v >= g->size || u == v) {
        return 0;
    }
    return g->matrix[u][v] == 1 ? 1 : 0;
}

int GetDegree(MGraph* g, int v)
{
    if (g == NULL || v < 0 || v >= g->size) return -1;

    int degree = 0;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[v][i] == 1) degree++;
    }
    return degree;
}

int GetNeighbors(MGraph* g, int v, int* neighbors)
{
    if (g == NULL || v < 0 || v >= g->size || neighbors == NULL) return -1;

    int cnt = 0;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[v][i] == 1) {
            neighbors[cnt++] = i;
        }
    }
    return cnt;
}

int GetEdgeCount(MGraph* g)
{
    if (g == NULL) return 0;
    return g->edgeCount;
}

int GetVertexCount(MGraph* g)
{
    if (g == NULL) return 0;
    return g->size;
}

void DFS(MGraph* g, int start, int* seq, int* cnt)
{
    if (cnt == NULL) return;
    if (g == NULL || start < 0 || start >= g->size || seq == NULL) {
        *cnt = 0;
        return;
    }

    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) {
        *cnt = 0;
        return;
    }

    *cnt = 0;
    dfsVisit(g, start, visited, seq, cnt);
    free(visited);
}

void BFS(MGraph* g, int start, int* seq, int* cnt)
{
    if (cnt == NULL) return;
    if (g == NULL || start < 0 || start >= g->size || seq == NULL) {
        *cnt = 0;
        return;
    }

    int* visited = (int*)calloc(g->size, sizeof(int));
    int* queue = (int*)malloc(sizeof(int) * g->size);
    if (visited == NULL || queue == NULL) {
        free(visited);
        free(queue);
        *cnt = 0;
        return;
    }

    int front = 0;
    int rear = 0;
    *cnt = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int v = queue[front++];
        seq[(*cnt)++] = v;
        for (int i = 0; i < g->size; i++) {
            if (g->matrix[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }

    free(visited);
    free(queue);
}

int IsConnected(MGraph* g)
{
    if (g == NULL || g->size == 0) return 0;
    if (g->size == 1) return 1;

    int* seq = (int*)malloc(sizeof(int) * g->size);
    if (seq == NULL) return 0;

    int cnt = 0;
    DFS(g, 0, seq, &cnt);
    free(seq);
    return cnt == g->size ? 1 : 0;
}

int GetConnectedComponents(MGraph* g)
{
    if (g == NULL || g->size == 0) return 0;

    int* visited = (int*)calloc(g->size, sizeof(int));
    int* seq = (int*)malloc(sizeof(int) * g->size);
    if (visited == NULL || seq == NULL) {
        free(visited);
        free(seq);
        return 0;
    }

    int components = 0;
    for (int i = 0; i < g->size; i++) {
        if (!visited[i]) {
            int cnt = 0;
            dfsVisit(g, i, visited, seq, &cnt);
            components++;
        }
    }

    free(visited);
    free(seq);
    return components;
}

Status RemoveEdge(MGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || u >= g->size || v < 0 || v >= g->size || u == v) {
        return ERROR;
    }
    if (g->matrix[u][v] == 0) return ERROR;

    g->matrix[u][v] = 0;
    g->matrix[v][u] = 0;
    g->edgeCount--;
    return OK;
}

void DestroyGraph(MGraph** pg)
{
    if (pg == NULL || *pg == NULL) return;

    MGraph* g = *pg;
    for (int i = 0; i < g->size; i++) {
        free(g->matrix[i]);
    }
    free(g->matrix);
    free(g);
    *pg = NULL;
}

int CountVerticesByDegree(MGraph* g, int k)
{
    if (g == NULL || k < 0) return -1;

    int count = 0;
    for (int i = 0; i < g->size; i++) {
        if (GetDegree(g, i) == k) count++;
    }
    return count;
}

int GetMaxDegreeVertex(MGraph* g)
{
    if (g == NULL || g->size <= 0) return -1;

    int maxVertex = 0;
    int maxDegree = GetDegree(g, 0);
    for (int i = 1; i < g->size; i++) {
        int degree = GetDegree(g, i);
        if (degree > maxDegree) {
            maxDegree = degree;
            maxVertex = i;
        }
    }
    return maxVertex;
}

int GetComponentSizes(MGraph* g, int* sizes)
{
    if (g == NULL || sizes == NULL) return -1;

    int* visited = (int*)calloc(g->size, sizeof(int));
    int* seq = (int*)malloc(sizeof(int) * g->size);
    if (visited == NULL || seq == NULL) {
        free(visited);
        free(seq);
        return -1;
    }

    int components = 0;
    for (int i = 0; i < g->size; i++) {
        if (!visited[i]) {
            int cnt = 0;
            dfsVisit(g, i, visited, seq, &cnt);
            sizes[components++] = cnt;
        }
    }

    free(visited);
    free(seq);
    return components;
}

Status RemoveVertex(MGraph* g, int v)
{
    if (g == NULL || v < 0 || v >= g->size) return ERROR;

    for (int i = 0; i < g->size; i++) {
        if (i != v && g->matrix[v][i] == 1) {
            RemoveEdge(g, v, i);
        }
    }
    return OK;
}

int ShortestPath(MGraph* g, int src, int dst)
{
    if (g == NULL || src < 0 || src >= g->size || dst < 0 || dst >= g->size) {
        return -1;
    }
    if (src == dst) return 0;

    int* dist = (int*)malloc(sizeof(int) * g->size);
    int* visited = (int*)calloc(g->size, sizeof(int));
    int* queue = (int*)malloc(sizeof(int) * g->size);
    if (dist == NULL || visited == NULL || queue == NULL) {
        free(dist);
        free(visited);
        free(queue);
        return -1;
    }

    for (int i = 0; i < g->size; i++) {
        dist[i] = -1;
    }

    int front = 0;
    int rear = 0;
    visited[src] = 1;
    dist[src] = 0;
    queue[rear++] = src;

    while (front < rear) {
        int v = queue[front++];
        if (v == dst) break;

        for (int i = 0; i < g->size; i++) {
            if (g->matrix[v][i] == 1 && !visited[i]) {
                visited[i] = 1;
                dist[i] = dist[v] + 1;
                queue[rear++] = i;
            }
        }
    }

    int result = dist[dst];
    free(dist);
    free(visited);
    free(queue);
    return result;
}

int IsTree(MGraph* g)
{
    if (g == NULL) return -1;
    if (g->size == 0) return 0;
    if (g->size == 1) return 1;
    return IsConnected(g) && g->edgeCount == g->size - 1 ? 1 : 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct {
    int** matrix;
    int   size;
    int   edgeCount;
} WDGraph;

WDGraph* CreateGraph(int size);
Status   AddEdge(WDGraph* g, int u, int v, int w);
Status   RemoveEdge(WDGraph* g, int u, int v);
int      HasEdge(WDGraph* g, int u, int v);
int      GetWeight(WDGraph* g, int u, int v);
int      GetOutDegree(WDGraph* g, int v);
int      GetInDegree(WDGraph* g, int v);
int      GetNeighbors(WDGraph* g, int v, int* neighbors);
int      GetEdgeCount(WDGraph* g);
int      GetVertexCount(WDGraph* g);
void     DFSVisit(WDGraph* g, int start, int* visited);
int      IsReachable(WDGraph* g, int u, int v);
Status   Dijkstra(WDGraph* g, int src, int* dist, int* prev);
int      GetShortestPath(WDGraph* g, int src, int dst);
int      GetShortestPathSeq(WDGraph* g, int src, int dst, int* path);
Status   BellmanFord(WDGraph* g, int src, int* dist, int* prev);
void     DestroyGraph(WDGraph** pg);
int      IsMutuallyReachable(WDGraph* g, int u, int v);
int      CountBalancedVertices(WDGraph* g);
int      CountReachableVertices(WDGraph* g, int src);
int      SumShortestPaths(WDGraph* g, int src);
int      IsShortestPath(WDGraph* g, int* path, int len);
int      GetPathHopCount(WDGraph* g, int src, int dst);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

static int is_valid_vertex(WDGraph* g, int v)
{
    return g != NULL && v >= 0 && v < g->size;
}

static void dfs_helper(WDGraph* g, int v, int* visited)
{
    visited[v] = 1;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[v][i] != 0 && !visited[i]) {
            dfs_helper(g, i, visited);
        }
    }
}

WDGraph* CreateGraph(int size)
{
    if (size <= 0) {
        return NULL;
    }

    WDGraph* g = (WDGraph*)malloc(sizeof(WDGraph));
    if (g == NULL) {
        return NULL;
    }

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

Status AddEdge(WDGraph* g, int u, int v, int w)
{
    if (g == NULL || u == v || w == 0) {
        return ERROR;
    }
    if (!is_valid_vertex(g, u) || !is_valid_vertex(g, v)) {
        return ERROR;
    }
    if (g->matrix[u][v] != 0) {
        return ERROR;
    }

    g->matrix[u][v] = w;
    g->edgeCount++;
    return OK;
}

Status RemoveEdge(WDGraph* g, int u, int v)
{
    if (g == NULL) {
        return ERROR;
    }
    if (!is_valid_vertex(g, u) || !is_valid_vertex(g, v)) {
        return ERROR;
    }
    if (g->matrix[u][v] == 0) {
        return ERROR;
    }

    g->matrix[u][v] = 0;
    g->edgeCount--;
    return OK;
}

int HasEdge(WDGraph* g, int u, int v)
{
    if (!is_valid_vertex(g, u) || !is_valid_vertex(g, v)) {
        return 0;
    }
    return g->matrix[u][v] != 0;
}

int GetWeight(WDGraph* g, int u, int v)
{
    if (!is_valid_vertex(g, u) || !is_valid_vertex(g, v)) {
        return 0;
    }
    return g->matrix[u][v];
}

int GetOutDegree(WDGraph* g, int v)
{
    if (!is_valid_vertex(g, v)) {
        return -1;
    }

    int degree = 0;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[v][i] != 0) {
            degree++;
        }
    }
    return degree;
}

int GetInDegree(WDGraph* g, int v)
{
    if (!is_valid_vertex(g, v)) {
        return -1;
    }

    int degree = 0;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[i][v] != 0) {
            degree++;
        }
    }
    return degree;
}

int GetNeighbors(WDGraph* g, int v, int* neighbors)
{
    if (!is_valid_vertex(g, v) || neighbors == NULL) {
        return -1;
    }

    int count = 0;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[v][i] != 0) {
            neighbors[count++] = i;
        }
    }
    return count;
}

int GetEdgeCount(WDGraph* g)
{
    if (g == NULL) {
        return 0;
    }
    return g->edgeCount;
}

int GetVertexCount(WDGraph* g)
{
    if (g == NULL) {
        return 0;
    }
    return g->size;
}

void DFSVisit(WDGraph* g, int start, int* visited)
{
    if (g == NULL || visited == NULL || !is_valid_vertex(g, start)) {
        return;
    }
    dfs_helper(g, start, visited);
}

int IsReachable(WDGraph* g, int u, int v)
{
    if (!is_valid_vertex(g, u) || !is_valid_vertex(g, v)) {
        return 0;
    }
    if (u == v) {
        return 1;
    }

    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) {
        return 0;
    }

    DFSVisit(g, u, visited);
    int result = visited[v];
    free(visited);
    return result;
}

Status Dijkstra(WDGraph* g, int src, int* dist, int* prev)
{
    if (g == NULL || dist == NULL || prev == NULL || !is_valid_vertex(g, src)) {
        return ERROR;
    }

    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) {
        return ERROR;
    }

    for (int i = 0; i < g->size; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[src] = 0;

    for (int count = 0; count < g->size; count++) {
        int u = -1;
        int minDist = INT_MAX;
        for (int i = 0; i < g->size; i++) {
            if (visited[i]) {
                continue;
            }
            if (dist[i] < minDist || (dist[i] == minDist && (u == -1 || i < u))) {
                minDist = dist[i];
                u = i;
            }
        }

        if (u == -1 || dist[u] == INT_MAX) {
            break;
        }

        visited[u] = 1;
        for (int v = 0; v < g->size; v++) {
            int w = g->matrix[u][v];
            if (w == 0) {
                continue;
            }
            if (dist[u] == INT_MAX) {
                continue;
            }
            if (dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                prev[v] = u;
            } else if (dist[u] + w == dist[v] && (prev[v] == -1 || u < prev[v])) {
                prev[v] = u;
            }
        }
    }

    free(visited);
    return OK;
}

int GetShortestPath(WDGraph* g, int src, int dst)
{
    if (!is_valid_vertex(g, src) || !is_valid_vertex(g, dst)) {
        return -1;
    }

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

    int result = dist[dst] == INT_MAX ? -1 : dist[dst];
    free(dist);
    free(prev);
    return result;
}

int GetShortestPathSeq(WDGraph* g, int src, int dst, int* path)
{
    if (!is_valid_vertex(g, src) || !is_valid_vertex(g, dst) || path == NULL) {
        return -1;
    }

    int* dist = (int*)malloc(sizeof(int) * g->size);
    int* prev = (int*)malloc(sizeof(int) * g->size);
    if (dist == NULL || prev == NULL) {
        free(dist);
        free(prev);
        return -1;
    }

    if (Dijkstra(g, src, dist, prev) == ERROR || dist[dst] == INT_MAX) {
        free(dist);
        free(prev);
        return -1;
    }

    int len = 0;
    int cur = dst;
    while (cur != -1) {
        path[len++] = cur;
        if (cur == src) {
            break;
        }
        cur = prev[cur];
    }

    for (int i = 0, j = len - 1; i < j; i++, j--) {
        int tmp = path[i];
        path[i] = path[j];
        path[j] = tmp;
    }

    free(dist);
    free(prev);
    return len;
}

Status BellmanFord(WDGraph* g, int src, int* dist, int* prev)
{
    if (g == NULL || dist == NULL || prev == NULL || !is_valid_vertex(g, src)) {
        return ERROR;
    }

    for (int i = 0; i < g->size; i++) {
        dist[i] = INT_MAX;
        prev[i] = -1;
    }
    dist[src] = 0;

    for (int k = 0; k < g->size - 1; k++) {
        for (int u = 0; u < g->size; u++) {
            if (dist[u] == INT_MAX) {
                continue;
            }
            for (int v = 0; v < g->size; v++) {
                int w = g->matrix[u][v];
                if (w == 0) {
                    continue;
                }
                if (dist[u] + w < dist[v]) {
                    dist[v] = dist[u] + w;
                    prev[v] = u;
                } else if (dist[u] + w == dist[v] && (prev[v] == -1 || u < prev[v])) {
                    prev[v] = u;
                }
            }
        }
    }

    for (int u = 0; u < g->size; u++) {
        if (dist[u] == INT_MAX) {
            continue;
        }
        for (int v = 0; v < g->size; v++) {
            int w = g->matrix[u][v];
            if (w == 0) {
                continue;
            }
            if (dist[u] + w < dist[v]) {
                return ERROR;
            }
        }
    }

    return OK;
}

void DestroyGraph(WDGraph** pg)
{
    if (pg == NULL || *pg == NULL) {
        return;
    }

    WDGraph* g = *pg;
    if (g->matrix != NULL) {
        for (int i = 0; i < g->size; i++) {
            free(g->matrix[i]);
        }
        free(g->matrix);
    }
    free(g);
    *pg = NULL;
}

int IsMutuallyReachable(WDGraph* g, int u, int v)
{
    if (g == NULL || !is_valid_vertex(g, u) || !is_valid_vertex(g, v)) {
        return -1;
    }
    if (u == v) {
        return 1;
    }
    return IsReachable(g, u, v) && IsReachable(g, v, u);
}

int CountBalancedVertices(WDGraph* g)
{
    if (g == NULL) {
        return -1;
    }

    int count = 0;
    for (int i = 0; i < g->size; i++) {
        if (GetOutDegree(g, i) == GetInDegree(g, i)) {
            count++;
        }
    }
    return count;
}

int CountReachableVertices(WDGraph* g, int src)
{
    if (g == NULL || !is_valid_vertex(g, src)) {
        return -1;
    }

    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) {
        return -1;
    }

    DFSVisit(g, src, visited);
    int count = 0;
    for (int i = 0; i < g->size; i++) {
        if (i != src && visited[i]) {
            count++;
        }
    }

    free(visited);
    return count;
}

int SumShortestPaths(WDGraph* g, int src)
{
    if (g == NULL || !is_valid_vertex(g, src)) {
        return -1;
    }

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

    int sum = 0;
    for (int i = 0; i < g->size; i++) {
        if (i != src && dist[i] != INT_MAX) {
            sum += dist[i];
        }
    }

    free(dist);
    free(prev);
    return sum;
}

int IsShortestPath(WDGraph* g, int* path, int len)
{
    if (g == NULL || path == NULL || len <= 1) {
        return -1;
    }

    for (int i = 0; i < len; i++) {
        if (!is_valid_vertex(g, path[i])) {
            return 0;
        }
    }

    int total = 0;
    for (int i = 0; i < len - 1; i++) {
        if (!HasEdge(g, path[i], path[i + 1])) {
            return 0;
        }
        total += GetWeight(g, path[i], path[i + 1]);
    }

    int shortest = GetShortestPath(g, path[0], path[len - 1]);
    if (shortest == -1) {
        return 0;
    }
    return total == shortest ? 1 : 0;
}

int GetPathHopCount(WDGraph* g, int src, int dst)
{
    if (g == NULL || !is_valid_vertex(g, src) || !is_valid_vertex(g, dst)) {
        return -1;
    }
    if (src == dst) {
        return 0;
    }

    int* path = (int*)malloc(sizeof(int) * g->size);
    if (path == NULL) {
        return -1;
    }

    int len = GetShortestPathSeq(g, src, dst, path);
    free(path);
    if (len == -1) {
        return -1;
    }
    return len - 1;
}

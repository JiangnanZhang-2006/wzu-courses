#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct {
    int** matrix;
    int   size;
    int   edgeCount;
} WDGraph;

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

static int IsValidVertex(WDGraph* g, int v)
{
    return g != NULL && v >= 0 && v < g->size;
}

WDGraph* CreateGraph(int size)
{
    if (size <= 0) return NULL;

    WDGraph* g = (WDGraph*)malloc(sizeof(WDGraph));
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

Status AddEdge(WDGraph* g, int u, int v, int w)
{
    if (g == NULL || u == v || w == 0) return ERROR;
    if (!IsValidVertex(g, u) || !IsValidVertex(g, v)) return ERROR;
    if (g->matrix[u][v] != 0) return ERROR;

    g->matrix[u][v] = w;
    g->edgeCount++;
    return OK;
}

Status RemoveEdge(WDGraph* g, int u, int v)
{
    if (g == NULL || u == v) return ERROR;
    if (!IsValidVertex(g, u) || !IsValidVertex(g, v)) return ERROR;
    if (g->matrix[u][v] == 0) return ERROR;

    g->matrix[u][v] = 0;
    g->edgeCount--;
    return OK;
}

int HasEdge(WDGraph* g, int u, int v)
{
    if (g == NULL || u == v) return 0;
    if (!IsValidVertex(g, u) || !IsValidVertex(g, v)) return 0;
    return g->matrix[u][v] != 0 ? 1 : 0;
}

int GetOutDegree(WDGraph* g, int v)
{
    if (!IsValidVertex(g, v)) return -1;

    int deg = 0;
    for (int j = 0; j < g->size; j++) {
        if (g->matrix[v][j] != 0) deg++;
    }
    return deg;
}

int GetInDegree(WDGraph* g, int v)
{
    if (!IsValidVertex(g, v)) return -1;

    int deg = 0;
    for (int i = 0; i < g->size; i++) {
        if (g->matrix[i][v] != 0) deg++;
    }
    return deg;
}

int GetNeighbors(WDGraph* g, int v, int* neighbors)
{
    if (!IsValidVertex(g, v) || neighbors == NULL) return -1;

    int cnt = 0;
    for (int j = 0; j < g->size; j++) {
        if (g->matrix[v][j] != 0) {
            neighbors[cnt++] = j;
        }
    }
    return cnt;
}

int GetEdgeCount(WDGraph* g)
{
    if (g == NULL) return 0;
    return g->edgeCount;
}

int GetVertexCount(WDGraph* g)
{
    if (g == NULL) return 0;
    return g->size;
}

int IsDAG(WDGraph* g)
{
    if (g == NULL || g->size == 0) return 0;

    int* indeg = (int*)malloc(sizeof(int) * g->size);
    int* used = (int*)calloc(g->size, sizeof(int));
    if (indeg == NULL || used == NULL) {
        free(indeg);
        free(used);
        return 0;
    }

    for (int i = 0; i < g->size; i++) {
        indeg[i] = GetInDegree(g, i);
    }

    int count = 0;
    while (count < g->size) {
        int u = -1;
        for (int i = 0; i < g->size; i++) {
            if (!used[i] && indeg[i] == 0) {
                u = i;
                break;
            }
        }
        if (u == -1) break;

        used[u] = 1;
        count++;
        for (int v = 0; v < g->size; v++) {
            if (g->matrix[u][v] != 0) {
                indeg[v]--;
            }
        }
    }

    free(indeg);
    free(used);
    return count == g->size ? 1 : 0;
}

int TopoSortKahn(WDGraph* g, int* seq)
{
    if (g == NULL) return 0;

    int* indeg = (int*)malloc(sizeof(int) * g->size);
    int* used = (int*)calloc(g->size, sizeof(int));
    if (indeg == NULL || used == NULL) {
        free(indeg);
        free(used);
        return 0;
    }

    for (int i = 0; i < g->size; i++) {
        indeg[i] = GetInDegree(g, i);
    }

    int count = 0;
    while (count < g->size) {
        int u = -1;
        for (int i = 0; i < g->size; i++) {
            if (!used[i] && indeg[i] == 0) {
                u = i;
                break;
            }
        }
        if (u == -1) break;

        if (seq != NULL) seq[count] = u;
        used[u] = 1;
        count++;
        for (int v = 0; v < g->size; v++) {
            if (g->matrix[u][v] != 0) {
                indeg[v]--;
            }
        }
    }

    free(indeg);
    free(used);
    return count;
}

static int dfsCycle;
static int dfsTopCnt;
static int* dfsPost;
static int* dfsColor;
static WDGraph* dfsGraph;

static void dfsTopoVisit(int u)
{
    dfsColor[u] = 1;
    for (int v = 0; v < dfsGraph->size; v++) {
        if (dfsGraph->matrix[u][v] == 0) continue;
        if (dfsColor[v] == 0) {
            dfsTopoVisit(v);
            if (dfsCycle) return;
        } else if (dfsColor[v] == 1) {
            dfsCycle = 1;
            return;
        }
    }
    dfsColor[u] = 2;
    dfsPost[dfsTopCnt++] = u;
}

int TopoSortDFS(WDGraph* g, int* seq)
{
    if (g == NULL) return -1;

    dfsGraph = g;
    dfsCycle = 0;
    dfsTopCnt = 0;
    dfsPost = (int*)malloc(sizeof(int) * g->size);
    dfsColor = (int*)calloc(g->size, sizeof(int));
    if (dfsPost == NULL || dfsColor == NULL) {
        free(dfsPost);
        free(dfsColor);
        return -1;
    }

    for (int i = 0; i < g->size; i++) {
        if (dfsColor[i] == 0) {
            dfsTopoVisit(i);
            if (dfsCycle) {
                free(dfsPost);
                free(dfsColor);
                return -1;
            }
        }
    }

    if (seq != NULL) {
        for (int i = 0; i < g->size; i++) {
            seq[i] = dfsPost[g->size - 1 - i];
        }
    }

    free(dfsPost);
    free(dfsColor);
    return g->size;
}

int GetLongestPath(WDGraph* g)
{
    if (g == NULL || !IsDAG(g)) return -1;
    if (g->edgeCount == 0) return 0;

    int* seq = (int*)malloc(sizeof(int) * g->size);
    int* dist = (int*)calloc(g->size, sizeof(int));
    if (seq == NULL || dist == NULL) {
        free(seq);
        free(dist);
        return -1;
    }

    if (TopoSortKahn(g, seq) != g->size) {
        free(seq);
        free(dist);
        return -1;
    }

    int ans = 0;
    for (int k = 0; k < g->size; k++) {
        int u = seq[k];
        for (int v = 0; v < g->size; v++) {
            int w = g->matrix[u][v];
            if (w == 0) continue;
            if (dist[u] + w > dist[v]) {
                dist[v] = dist[u] + w;
            }
            if (dist[v] > ans) ans = dist[v];
        }
    }

    free(seq);
    free(dist);
    return ans;
}

void DestroyGraph(WDGraph** pg)
{
    if (pg == NULL || *pg == NULL) return;

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

int CountSourceVertices(WDGraph* g)
{
    if (g == NULL) return -1;

    int cnt = 0;
    for (int i = 0; i < g->size; i++) {
        if (GetInDegree(g, i) == 0) cnt++;
    }
    return cnt;
}

int IsTopoOrder(WDGraph* g, int* seq, int len)
{
    if (g == NULL || seq == NULL || len != g->size) return -1;

    int* pos = (int*)malloc(sizeof(int) * g->size);
    int* seen = (int*)calloc(g->size, sizeof(int));
    if (pos == NULL || seen == NULL) {
        free(pos);
        free(seen);
        return -1;
    }

    for (int i = 0; i < len; i++) {
        int v = seq[i];
        if (v < 0 || v >= g->size || seen[v]) {
            free(pos);
            free(seen);
            return 0;
        }
        seen[v] = 1;
        pos[v] = i;
    }

    for (int u = 0; u < g->size; u++) {
        for (int v = 0; v < g->size; v++) {
            if (g->matrix[u][v] != 0 && pos[u] >= pos[v]) {
                free(pos);
                free(seen);
                return 0;
            }
        }
    }

    free(pos);
    free(seen);
    return 1;
}

int GetKthTopoVertex(WDGraph* g, int k)
{
    if (g == NULL || k < 0 || k >= g->size) return -1;
    if (!IsDAG(g)) return -1;

    int* seq = (int*)malloc(sizeof(int) * g->size);
    if (seq == NULL) return -1;

    if (TopoSortKahn(g, seq) != g->size) {
        free(seq);
        return -1;
    }

    int ans = seq[k];
    free(seq);
    return ans;
}

int HasPath(WDGraph* g, int src, int dst)
{
    if (g == NULL || !IsValidVertex(g, src) || !IsValidVertex(g, dst)) return -1;
    if (src == dst) return 1;

    int* visited = (int*)calloc(g->size, sizeof(int));
    int* queue = (int*)malloc(sizeof(int) * g->size);
    if (visited == NULL || queue == NULL) {
        free(visited);
        free(queue);
        return -1;
    }

    int front = 0, rear = 0;
    queue[rear++] = src;
    visited[src] = 1;

    while (front < rear) {
        int u = queue[front++];
        if (u == dst) {
            free(visited);
            free(queue);
            return 1;
        }
        for (int v = 0; v < g->size; v++) {
            if (g->matrix[u][v] != 0 && !visited[v]) {
                visited[v] = 1;
                queue[rear++] = v;
            }
        }
    }

    free(visited);
    free(queue);
    return 0;
}

int GetLongestPathFrom(WDGraph* g, int src)
{
    if (g == NULL || !IsValidVertex(g, src)) return -1;
    if (!IsDAG(g)) return -1;
    if (GetOutDegree(g, src) == 0) return 0;

    int* seq = (int*)malloc(sizeof(int) * g->size);
    int* dist = (int*)malloc(sizeof(int) * g->size);
    if (seq == NULL || dist == NULL) {
        free(seq);
        free(dist);
        return -1;
    }

    for (int i = 0; i < g->size; i++) {
        dist[i] = -1;
    }
    dist[src] = 0;

    if (TopoSortKahn(g, seq) != g->size) {
        free(seq);
        free(dist);
        return -1;
    }

    int ans = 0;
    for (int k = 0; k < g->size; k++) {
        int u = seq[k];
        if (dist[u] < 0) continue;
        for (int v = 0; v < g->size; v++) {
            int w = g->matrix[u][v];
            if (w == 0) continue;
            if (dist[u] + w > dist[v]) {
                dist[v] = dist[u] + w;
            }
            if (dist[v] > ans) ans = dist[v];
        }
    }

    free(seq);
    free(dist);
    return ans;
}

int IsDAGAfterRemove(WDGraph* g, int u, int v)
{
    if (g == NULL || u == v) return -1;
    if (!IsValidVertex(g, u) || !IsValidVertex(g, v)) return -1;
    if (g->matrix[u][v] == 0) return -1;

    int w = g->matrix[u][v];
    g->matrix[u][v] = 0;
    g->edgeCount--;

    int ans = IsDAG(g) ? 1 : 0;

    g->matrix[u][v] = w;
    g->edgeCount++;

    return ans;
}

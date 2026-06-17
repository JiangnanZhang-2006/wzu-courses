#include <stdio.h>
#include <stdlib.h>

typedef enum { OK = 1, ERROR = 0 } Status;

typedef struct AdjNode {
    int             vertex;
    struct AdjNode* next;
} AdjNode;

typedef struct {
    AdjNode** heads;
    int       size;
    int       edgeCount;
} ALGraph;

ALGraph*   CreateGraph(int size);
AdjNode*   CreateAdjNode(int vertex);
Status     AddEdgeHead(ALGraph* g, int u, int v);
Status     AddEdgeTail(ALGraph* g, int u, int v);
int        HasEdge(ALGraph* g, int u, int v);
Status     RemoveEdge(ALGraph* g, int u, int v);
int        GetDegree(ALGraph* g, int v);
int        GetNeighbors(ALGraph* g, int v, int* neighbors);
int        GetEdgeCount(ALGraph* g);
int        GetVertexCount(ALGraph* g);
void       DFS(ALGraph* g, int start, int* seq, int* cnt);
void       BFS(ALGraph* g, int start, int* seq, int* cnt);
int        IsConnected(ALGraph* g);
int        GetConnectedComponents(ALGraph* g);
int        HasCycle(ALGraph* g);
void       DestroyGraph(ALGraph** pg);

int main()
{
    return 0;
}

/******************** 学生提交的函数将被拼接在此处 ********************/

static void sortAscending(int* arr, int n)
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arr[i] > arr[j]) {
                int tmp = arr[i];
                arr[i] = arr[j];
                arr[j] = tmp;
            }
        }
    }
}

static Status appendTail(AdjNode** head, AdjNode* node)
{
    if (*head == NULL) {
        *head = node;
        return OK;
    }
    AdjNode* cur = *head;
    while (cur->next != NULL) {
        cur = cur->next;
    }
    cur->next = node;
    return OK;
}

static int removeFromList(AdjNode** head, int vertex)
{
    AdjNode* cur = *head;
    AdjNode* prev = NULL;
    while (cur != NULL) {
        if (cur->vertex == vertex) {
            if (prev == NULL) {
                *head = cur->next;
            } else {
                prev->next = cur->next;
            }
            free(cur);
            return 1;
        }
        prev = cur;
        cur = cur->next;
    }
    return 0;
}

static void dfsVisit(ALGraph* g, int v, int* visited, int* seq, int* cnt)
{
    visited[v] = 1;
    seq[*cnt] = v;
    (*cnt)++;

    int* neighbors = (int*)malloc(sizeof(int) * g->size);
    if (neighbors == NULL) {
        return;
    }
    int n = GetNeighbors(g, v, neighbors);
    for (int i = 0; i < n; i++) {
        if (!visited[neighbors[i]]) {
            dfsVisit(g, neighbors[i], visited, seq, cnt);
        }
    }
    free(neighbors);
}

static int dfsCycle(ALGraph* g, int v, int parent, int* visited)
{
    visited[v] = 1;

    int* neighbors = (int*)malloc(sizeof(int) * g->size);
    if (neighbors == NULL) {
        return 0;
    }
    int n = GetNeighbors(g, v, neighbors);
    for (int i = 0; i < n; i++) {
        int nb = neighbors[i];
        if (!visited[nb]) {
            if (dfsCycle(g, nb, v, visited)) {
                free(neighbors);
                return 1;
            }
        } else if (nb != parent) {
            free(neighbors);
            return 1;
        }
    }
    free(neighbors);
    return 0;
}

ALGraph* CreateGraph(int size)
{
    if (size <= 0) {
        return NULL;
    }

    ALGraph* g = (ALGraph*)malloc(sizeof(ALGraph));
    if (g == NULL) {
        return NULL;
    }

    g->heads = (AdjNode**)malloc(sizeof(AdjNode*) * size);
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

AdjNode* CreateAdjNode(int vertex)
{
    AdjNode* node = (AdjNode*)malloc(sizeof(AdjNode));
    if (node == NULL) {
        return NULL;
    }
    node->vertex = vertex;
    node->next = NULL;
    return node;
}

int HasEdge(ALGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || v < 0 || u >= g->size || v >= g->size || u == v) {
        return 0;
    }

    AdjNode* cur = g->heads[u];
    while (cur != NULL) {
        if (cur->vertex == v) {
            return 1;
        }
        cur = cur->next;
    }
    return 0;
}

Status AddEdgeHead(ALGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || v < 0 || u >= g->size || v >= g->size || u == v) {
        return ERROR;
    }
    if (HasEdge(g, u, v)) {
        return ERROR;
    }

    AdjNode* nodeU = CreateAdjNode(v);
    AdjNode* nodeV = CreateAdjNode(u);
    if (nodeU == NULL || nodeV == NULL) {
        free(nodeU);
        free(nodeV);
        return ERROR;
    }

    nodeU->next = g->heads[u];
    g->heads[u] = nodeU;
    nodeV->next = g->heads[v];
    g->heads[v] = nodeV;
    g->edgeCount++;
    return OK;
}

Status AddEdgeTail(ALGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || v < 0 || u >= g->size || v >= g->size || u == v) {
        return ERROR;
    }
    if (HasEdge(g, u, v)) {
        return ERROR;
    }

    AdjNode* nodeU = CreateAdjNode(v);
    AdjNode* nodeV = CreateAdjNode(u);
    if (nodeU == NULL || nodeV == NULL) {
        free(nodeU);
        free(nodeV);
        return ERROR;
    }

    if (appendTail(&g->heads[u], nodeU) == ERROR ||
        appendTail(&g->heads[v], nodeV) == ERROR) {
        free(nodeU);
        free(nodeV);
        return ERROR;
    }

    g->edgeCount++;
    return OK;
}

Status RemoveEdge(ALGraph* g, int u, int v)
{
    if (g == NULL || u < 0 || v < 0 || u >= g->size || v >= g->size || u == v) {
        return ERROR;
    }
    if (!HasEdge(g, u, v)) {
        return ERROR;
    }

    removeFromList(&g->heads[u], v);
    removeFromList(&g->heads[v], u);
    g->edgeCount--;
    return OK;
}

int GetDegree(ALGraph* g, int v)
{
    if (g == NULL || v < 0 || v >= g->size) {
        return -1;
    }

    int degree = 0;
    AdjNode* cur = g->heads[v];
    while (cur != NULL) {
        degree++;
        cur = cur->next;
    }
    return degree;
}

int GetNeighbors(ALGraph* g, int v, int* neighbors)
{
    if (g == NULL || v < 0 || v >= g->size || neighbors == NULL) {
        return -1;
    }

    int count = 0;
    AdjNode* cur = g->heads[v];
    while (cur != NULL) {
        neighbors[count++] = cur->vertex;
        cur = cur->next;
    }
    sortAscending(neighbors, count);
    return count;
}

int GetEdgeCount(ALGraph* g)
{
    if (g == NULL) {
        return 0;
    }
    return g->edgeCount;
}

int GetVertexCount(ALGraph* g)
{
    if (g == NULL) {
        return 0;
    }
    return g->size;
}

void DFS(ALGraph* g, int start, int* seq, int* cnt)
{
    if (g == NULL || start < 0 || start >= g->size || seq == NULL || cnt == NULL) {
        if (cnt != NULL) {
            *cnt = 0;
        }
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

void BFS(ALGraph* g, int start, int* seq, int* cnt)
{
    if (g == NULL || start < 0 || start >= g->size || seq == NULL || cnt == NULL) {
        if (cnt != NULL) {
            *cnt = 0;
        }
        return;
    }

    int* visited = (int*)calloc(g->size, sizeof(int));
    int* queue = (int*)malloc(sizeof(int) * g->size);
    int* neighbors = (int*)malloc(sizeof(int) * g->size);
    if (visited == NULL || queue == NULL || neighbors == NULL) {
        free(visited);
        free(queue);
        free(neighbors);
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
        seq[*cnt] = v;
        (*cnt)++;

        int n = GetNeighbors(g, v, neighbors);
        for (int i = 0; i < n; i++) {
            int nb = neighbors[i];
            if (!visited[nb]) {
                visited[nb] = 1;
                queue[rear++] = nb;
            }
        }
    }

    free(visited);
    free(queue);
    free(neighbors);
}

int IsConnected(ALGraph* g)
{
    if (g == NULL || g->size == 0) {
        return 0;
    }
    if (g->size == 1) {
        return 1;
    }

    int* seq = (int*)malloc(sizeof(int) * g->size);
    if (seq == NULL) {
        return 0;
    }

    int cnt = 0;
    DFS(g, 0, seq, &cnt);
    free(seq);
    return cnt == g->size ? 1 : 0;
}

int GetConnectedComponents(ALGraph* g)
{
    if (g == NULL || g->size == 0) {
        return 0;
    }

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
            DFS(g, i, seq, &cnt);
            for (int j = 0; j < cnt; j++) {
                visited[seq[j]] = 1;
            }
            components++;
        }
    }

    free(visited);
    free(seq);
    return components;
}

int HasCycle(ALGraph* g)
{
    if (g == NULL || g->size == 0) {
        return 0;
    }

    int* visited = (int*)calloc(g->size, sizeof(int));
    if (visited == NULL) {
        return 0;
    }

    for (int i = 0; i < g->size; i++) {
        if (!visited[i]) {
            if (dfsCycle(g, i, -1, visited)) {
                free(visited);
                return 1;
            }
        }
    }

    free(visited);
    return 0;
}

void DestroyGraph(ALGraph** pg)
{
    if (pg == NULL || *pg == NULL) {
        return;
    }

    ALGraph* g = *pg;
    for (int i = 0; i < g->size; i++) {
        AdjNode* cur = g->heads[i];
        while (cur != NULL) {
            AdjNode* next = cur->next;
            free(cur);
            cur = next;
        }
    }

    free(g->heads);
    free(g);
    *pg = NULL;
}

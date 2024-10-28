#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define MAX_EDGES 1000

typedef struct {
    int u, v, weight;
} Edge;

typedef struct {
    Edge edges[MAX_EDGES];
    int edge_count;
} GraphType;

int parent[MAX_VERTICES];

void graph_init(GraphType* g) {
    g->edge_count = 0;
}

void add_edge(GraphType* g, int u, int v, int weight) {
    g->edges[g->edge_count].u = u;
    g->edges[g->edge_count].v = v;
    g->edges[g->edge_count].weight = weight;
    g->edge_count++;
}

int find(int v) {
    if (parent[v] == -1) return v;
    return find(parent[v]);
}

void union_set(int u, int v) {
    parent[v] = u;
}

int compare(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

void QuickKruskal(GraphType* g) {
    int uRoot, vRoot;

    for (int i = 0; i < MAX_VERTICES; i++) {
        parent[i] = -1;
    }

    qsort(g->edges, g->edge_count, sizeof(Edge), compare);

    printf("Quick Based Kruskal\n");
    for (int i = 0; i < g->edge_count; i++) {
        uRoot = find(g->edges[i].u);
        vRoot = find(g->edges[i].v);

        if (uRoot != vRoot) {
            printf("Edge (%d,%d) select %d\n", g->edges[i].u, g->edges[i].v, g->edges[i].weight);
            union_set(uRoot, vRoot);
        }
    }
}

typedef struct {
    Edge* edges;
    int size;
    int capacity;
} MinHeap;

MinHeap* create_min_heap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->edges = (Edge*)malloc(capacity * sizeof(Edge));
    return minHeap;
}

void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

void min_heapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->edges[left].weight < minHeap->edges[smallest].weight)
        smallest = left;
    if (right < minHeap->size && minHeap->edges[right].weight < minHeap->edges[smallest].weight)
        smallest = right;
    if (smallest != idx) {
        swap(&minHeap->edges[idx], &minHeap->edges[smallest]);
        min_heapify(minHeap, smallest);
    }
}

Edge extract_min(MinHeap* minHeap) {
    if (minHeap->size == 0) {
        Edge e = { 0, 0, 0 };
        return e;
    }
    Edge root = minHeap->edges[0];
    minHeap->edges[0] = minHeap->edges[minHeap->size - 1];
    minHeap->size--;
    min_heapify(minHeap, 0);
    return root;
}

void insert_edge(MinHeap* minHeap, Edge edge) {
    if (minHeap->size == minHeap->capacity) return;
    minHeap->edges[minHeap->size++] = edge;
    for (int i = minHeap->size / 2 - 1; i >= 0; i--) {
        min_heapify(minHeap, i);
    }
}

void MinHeapKruskal(GraphType* g) {
    int uRoot, vRoot;
    MinHeap* minHeap = create_min_heap(g->edge_count);

    for (int i = 0; i < g->edge_count; i++) {
        insert_edge(minHeap, g->edges[i]);
    }

    for (int i = 0; i < MAX_VERTICES; i++) {
        parent[i] = -1;
    }

    printf("\nMinHeap Based Kruskal\n");
    while (minHeap->size > 0) {
        Edge edge = extract_min(minHeap);
        uRoot = find(edge.u);
        vRoot = find(edge.v);

        if (uRoot != vRoot) {
            printf("Edge (%d,%d) select %d\n", edge.u, edge.v, edge.weight);
            union_set(uRoot, vRoot);
        }
    }
    free(minHeap->edges);
    free(minHeap);
}

void GenerateGraph(GraphType* g) {
    add_edge(g, 1, 2, 3);
    add_edge(g, 2, 5, 1);
    add_edge(g, 3, 4, 2);
    add_edge(g, 2, 4, 4);
    add_edge(g, 3, 8, 5);
    add_edge(g, 3, 7, 6);
    add_edge(g, 2, 6, 7);
    add_edge(g, 9, 10, 10);
    add_edge(g, 8, 10, 15);
}

int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    GenerateGraph(g);

    QuickKruskal(g);
    MinHeapKruskal(g);

    free(g);
    return 0;
}

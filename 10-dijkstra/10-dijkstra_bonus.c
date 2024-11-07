#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10

typedef struct Node {
    int vertex;
    int weight;
    struct Node* next;
} Node;

typedef struct {
    Node* adj[MAX_VERTICES + 1];
    int num_vertices;
} GraphType;

typedef struct {
    int vertex;
    int distance;
} HeapNode;

typedef struct {
    HeapNode heap[MAX_VERTICES + 1];
    int size;
} MinHeap;

typedef struct {
    int distance[MAX_VERTICES + 1];
    int found[MAX_VERTICES + 1];
    int found_order[MAX_VERTICES];
    int found_count;
} DijkstraResult;

void init_graph(GraphType* g) {
    g->num_vertices = 0;
    for (int i = 1; i <= MAX_VERTICES; i++) {
        g->adj[i] = NULL;
    }
}

void add_edge(GraphType* g, int u, int v, int weight) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->vertex = v;
    node->weight = weight;
    node->next = g->adj[u];
    g->adj[u] = node;
}

void generate_graph(GraphType* g) {
    g->num_vertices = 10;

    add_edge(g, 1, 2, 3);
    add_edge(g, 1, 6, 11);
    add_edge(g, 1, 7, 12);
    add_edge(g, 2, 5, 1);
    add_edge(g, 2, 6, 7);
    add_edge(g, 2, 7, 8);
    add_edge(g, 2, 3, 5);
    add_edge(g, 2, 4, 4);
    add_edge(g, 3, 4, 2);
    add_edge(g, 3, 7, 6);
    add_edge(g, 3, 8, 5);
    add_edge(g, 4, 5, 13);
    add_edge(g, 4, 8, 14);
    add_edge(g, 4, 10, 16);
    add_edge(g, 5, 10, 17);
    add_edge(g, 5, 9, 18);
    add_edge(g, 5, 6, 9);
    add_edge(g, 7, 8, 13);
    add_edge(g, 9, 10, 10);
}

// Min-heap 초기화
void min_heap_init(MinHeap* heap) {
    heap->size = 0;
}

// Min-heap에 요소 추가
void min_heap_push(MinHeap* heap, int vertex, int distance) {
    heap->size++;
    int i = heap->size;
    while (i > 1 && distance < heap->heap[i / 2].distance) {
        heap->heap[i] = heap->heap[i / 2];
        i /= 2;
    }
    heap->heap[i].vertex = vertex;
    heap->heap[i].distance = distance;
}

// Min-heap에서 최소값을 추출
HeapNode min_heap_pop(MinHeap* heap) {
    HeapNode min = heap->heap[1];
    HeapNode last = heap->heap[heap->size--];
    int i = 1, child;

    while (i * 2 <= heap->size) {
        child = i * 2;
        if (child < heap->size && heap->heap[child + 1].distance < heap->heap[child].distance)
            child++;
        if (last.distance <= heap->heap[child].distance)
            break;
        heap->heap[i] = heap->heap[child];
        i = child;
    }
    heap->heap[i] = last;
    return min;
}

// Min-heap이 비어있는지 확인
int min_heap_is_empty(MinHeap* heap) {
    return heap->size == 0;
}

void dijkstra(GraphType* g, int start, DijkstraResult* result) {
    for (int i = 1; i <= g->num_vertices; i++) {
        result->distance[i] = INT_MAX;
        result->found[i] = 0;
    }
    result->distance[start] = 0;
    result->found_count = 0;

    MinHeap heap;
    min_heap_init(&heap);
    min_heap_push(&heap, start, 0);

    while (!min_heap_is_empty(&heap)) {
        HeapNode u_node = min_heap_pop(&heap);
        int u = u_node.vertex;

        if (result->found[u]) continue;

        result->found[u] = 1;
        result->found_order[result->found_count++] = u;

        printf("Distance: ");
        for (int k = 1; k <= g->num_vertices; k++) {
            if (result->distance[k] == INT_MAX)
                printf("* ");
            else
                printf("%d ", result->distance[k]);
        }
        printf("\nFound: ");
        for (int k = 1; k <= g->num_vertices; k++) {
            printf("%d ", result->found[k]);
        }
        printf("\n\n");

        Node* curr = g->adj[u];
        while (curr != NULL) {
            int v = curr->vertex;
            int weight = curr->weight;

            if (!result->found[v] && result->distance[u] + weight < result->distance[v]) {
                result->distance[v] = result->distance[u] + weight;
                min_heap_push(&heap, v, result->distance[v]);
            }
            curr = curr->next;
        }
    }

    printf("Found Order: ");
    for (int i = 0; i < result->found_count; i++) {
        printf("%d ", result->found_order[i]);
    }
    printf("\n");
}

int main() {
    GraphType graph;
    init_graph(&graph);
    generate_graph(&graph);

    DijkstraResult result;
    dijkstra(&graph, 1, &result);

    return 0;
}

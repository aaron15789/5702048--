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

// 그래프 초기화 함수: 간선 수를 0으로 설정
void graph_init(GraphType* g) {
    g->edge_count = 0;
}

// 간선 추가 함수: 그래프에 새로운 간선을 추가
void add_edge(GraphType* g, int u, int v, int weight) {
    g->edges[g->edge_count].u = u;
    g->edges[g->edge_count].v = v;
    g->edges[g->edge_count].weight = weight;
    g->edge_count++;
}

// 특정 정점의 루트 찾기 함수: 경로 압축 기법을 사용하여 루트를 찾음
int find(int v) {
    if (parent[v] == -1) return v;
    return find(parent[v]);
}

// 두 집합을 합치는 함수: 두 정점의 부모를 설정하여 집합을 통합
void union_set(int u, int v) {
    parent[v] = u;
}

// 간선 가중치 비교 함수: Kruskal 알고리즘에서 사용
int compare(const void* a, const void* b) {
    Edge* edgeA = (Edge*)a;
    Edge* edgeB = (Edge*)b;
    return edgeA->weight - edgeB->weight;
}

// Kruskal 알고리즘을 사용한 최소 신장 트리 생성 함수 (Quick Sort 사용)
void QuickKruskal(GraphType* g) {
    int uRoot, vRoot;

    // 부모 배열 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        parent[i] = -1;
    }

    // 간선 정렬
    qsort(g->edges, g->edge_count, sizeof(Edge), compare);

    printf("Quick Based Kruskal\n");
    // 간선을 하나씩 선택하여 최소 신장 트리 구성
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

// 최소 힙 생성 함수: 주어진 용량으로 최소 힙을 초기화
MinHeap* create_min_heap(int capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->capacity = capacity;
    minHeap->size = 0;
    minHeap->edges = (Edge*)malloc(capacity * sizeof(Edge));
    return minHeap;
}

// 두 간선 교환 함수
void swap(Edge* a, Edge* b) {
    Edge temp = *a;
    *a = *b;
    *b = temp;
}

// 최소 힙 유지 함수: 주어진 인덱스에서 최소 힙 속성을 유지
void min_heapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    // 왼쪽 자식과 비교하여 더 작은 값을 찾음
    if (left < minHeap->size && minHeap->edges[left].weight < minHeap->edges[smallest].weight)
        smallest = left;
    // 오른쪽 자식과 비교하여 더 작은 값을 찾음
    if (right < minHeap->size && minHeap->edges[right].weight < minHeap->edges[smallest].weight)
        smallest = right;
    // 가장 작은 값이 현재 인덱스가 아니면 교환하고 재귀 호출
    if (smallest != idx) {
        swap(&minHeap->edges[idx], &minHeap->edges[smallest]);
        min_heapify(minHeap, smallest);
    }
}

// 최소 힙에서 최소 간선을 추출하는 함수
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

// 최소 힙에 간선을 추가하는 함수
void insert_edge(MinHeap* minHeap, Edge edge) {
    if (minHeap->size == minHeap->capacity) return;
    minHeap->edges[minHeap->size++] = edge;
    // 새로운 간선 추가 후 힙 속성 유지
    for (int i = minHeap->size / 2 - 1; i >= 0; i--) {
        min_heapify(minHeap, i);
    }
}

// Kruskal 알고리즘을 사용한 최소 신장 트리 생성 함수 (최소 힙 사용)
void MinHeapKruskal(GraphType* g) {
    int uRoot, vRoot;
    MinHeap* minHeap = create_min_heap(g->edge_count);

    // 모든 간선을 최소 힙에 삽입
    for (int i = 0; i < g->edge_count; i++) {
        insert_edge(minHeap, g->edges[i]);
    }

    // 부모 배열 초기화
    for (int i = 0; i < MAX_VERTICES; i++) {
        parent[i] = -1;
    }

    printf("\nMinHeap Based Kruskal\n");
    // 최소 힙에서 간선을 하나씩 추출하여 최소 신장 트리 구성
    while (minHeap->size > 0) {
        Edge edge = extract_min(minHeap);
        uRoot = find(edge.u);
        vRoot = find(edge.v);

        if (uRoot != vRoot) {
            printf("Edge (%d,%d) select %d\n", edge.u, edge.v, edge.weight);
            union_set(uRoot, vRoot);
        }
    }
    // 메모리 해제
    free(minHeap->edges);
    free(minHeap);
}

// 그래프 생성을 위한 간선 추가 함수
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

// 메인 함수: 그래프를 초기화하고 Kruskal 알고리즘 실행
int main(void) {
    GraphType* g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);
    GenerateGraph(g);

    QuickKruskal(g);
    MinHeapKruskal(g);

    free(g);
    return 0;
}

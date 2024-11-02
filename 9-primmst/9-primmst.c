#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_VERTICES 10

typedef struct {
    int edges[MAX_VERTICES + 1][MAX_VERTICES + 1]; // 1-based index
    int num_vertices;
} GraphType;

void graph_init(GraphType* g) {
    g->num_vertices = 0;
    for (int i = 1; i <= MAX_VERTICES; i++) {
        for (int j = 1; j <= MAX_VERTICES; j++) {
            g->edges[i][j] = (i == j) ? 0 : INT_MAX; // 자기 자신과의 거리는 0, 나머지는 무한대
        }
    }
}

void GenerateGraph(GraphType* g) {
    // 그래프의 정점 수 설정
    g->num_vertices = 10;

    // 간선의 가중치 설정 (주어진 데이터 사용)
    g->edges[1][2] = 3;
    g->edges[1][6] = 11;
    g->edges[1][7] = 12;
    g->edges[2][5] = 1;
    g->edges[2][6] = 7;
    g->edges[2][7] = 8;
    g->edges[2][3] = 5;
    g->edges[2][4] = 4;
    g->edges[3][4] = 2;
    g->edges[3][7] = 6;
    g->edges[3][8] = 5;
    g->edges[4][5] = 13;
    g->edges[4][8] = 14;
    g->edges[4][10] = 16;
    g->edges[5][10] = 17;
    g->edges[5][9] = 18;
    g->edges[5][6] = 9;
    g->edges[7][8] = 13;
    g->edges[9][10] = 10;
    // g->edges[9][10] = 15; // 중복된 간선 수정 필요
}

void FindPrimMST(GraphType* g) {
    int selected[MAX_VERTICES + 1] = { 0 }; // 선택된 정점
    int num_edges = 0; // 선택된 간선 수
    selected[1] = 1; // 첫 정점 선택 (정점 1)
    printf("prim MST Algorithm\n");
    printf("정점 1 추가\n"); // 정점 1 추가 출력

    while (num_edges < g->num_vertices - 1) {
        int min = INT_MAX;
        int u = -1, v = -1;

        // 가장 작은 가중치의 간선 찾기
        for (int i = 1; i <= g->num_vertices; i++) {
            if (selected[i]) {
                for (int j = 1; j <= g->num_vertices; j++) {
                    if (!selected[j] && g->edges[i][j] < min) {
                        min = g->edges[i][j];
                        u = i;
                        v = j;
                    }
                }
            }
        }

        // 간선 선택
        if (u != -1 && v != -1) {
            selected[v] = 1; // 정점 추가
            printf("정점 %d 추가\n", v); // 정점 번호는 1부터 시작
            num_edges++;
        }
    }
}

int main(void) {
    GraphType* g;
    g = (GraphType*)malloc(sizeof(GraphType));
    graph_init(g);

    GenerateGraph(g);

    FindPrimMST(g);

    free(g);
    return 0;
}

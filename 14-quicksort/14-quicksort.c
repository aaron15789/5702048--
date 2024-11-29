#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0;  // 비교 횟수
int moveCount = 0;        // 이동 횟수

void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

void printArray(int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Partition 함수
int partition(int* array, int low, int high) {
    int pivot = array[high];
    moveCount++; // pivot 값을 temp에 넣음

    int i = low - 1;
    for (int j = low; j < high; j++) {
        comparisonCount++; // 비교
        if (array[j] <= pivot) {
            i++;
            // Swap
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
            moveCount += 3; // temp에 넣고 다시 교환
        }
    }

    // Pivot 위치 이동
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    moveCount += 3;

    return i + 1;
}

// 반복적 퀵정렬
void doQuickSort(int* array, int low, int high, int* rounds, int isFirst) {
    int stack[SIZE];
    int top = -1;

    stack[++top] = low;
    stack[++top] = high;

    while (top >= 0) {
        high = stack[top--];
        low = stack[top--];

        int pivotIndex = partition(array, low, high);

        // 정렬 중간 과정을 출력
        if (isFirst && *rounds < 14) {
            for (int i = 40; i < 60; i++) {
                printf("%d ", array[i]);
            }
            printf("\n\n");
            (*rounds)++;
        }

        // 왼쪽 부분 추가
        if (pivotIndex - 1 > low) {
            stack[++top] = low;
            stack[++top] = pivotIndex - 1;
        }

        // 오른쪽 부분 추가
        if (pivotIndex + 1 < high) {
            stack[++top] = pivotIndex + 1;
            stack[++top] = high;
        }
    }
}

int main(int argc, char* argv[]) {
    srand(time(NULL));

    int array[SIZE];
    int totalComparisons = 0;
    int totalMoveCount = 0;

    for (int i = 0; i < 20; i++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (i == 0) {
            printf("Quick Sort Run\n");

            int rounds = 0;
            doQuickSort(array, 0, SIZE - 1, &rounds, 1);

            printf("Result\n");
            printArray(array, SIZE);
        }
        else {
            int dummyRounds = 0;
            doQuickSort(array, 0, SIZE - 1, &dummyRounds, 0);
        }

        totalComparisons += comparisonCount;
        totalMoveCount += moveCount;
    }

    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoveCount / 20.0);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100

int comparisonCount = 0;
int moveCount = 0;

// 랜덤 데이터 생성 함수
void generateRandomData(int list[]) {
    for (int i = 0; i < SIZE; i++) {
        list[i] = rand() % 1000; // 0 ~ 999 범위의 랜덤 숫자
    }
}

// 배열 출력 함수
void printArray(int list[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", list[i]);
        if ((i + 1) % 10 == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

// 선택 정렬 함수
void doSelectionSort(int list[]) {
    printf("Selection Sort:\n");
    int temp, minIndex;
    int data[SIZE];
    for (int i = 0; i < SIZE; i++) {
        data[i] = list[i];
    }

    for (int i = 0; i < SIZE - 1; i++) {
        minIndex = i;
        for (int j = i + 1; j < SIZE; j++) {
            comparisonCount++;
            if (data[j] < data[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            temp = data[i];
            data[i] = data[minIndex];
            data[minIndex] = temp;
            moveCount++;
        }
        // 정렬 과정을 출력 (10번째부터 20단위, 마지막)
        if ((i + 1) % 20 == 10 || i == SIZE - 2) {
            printf("Step %d:\n", i + 1);
            printArray(data, SIZE);
        }
    }
}

// 삽입 정렬 함수
void doInsertionSort(int list[]) {

    int totalComparisons = 0;
    int data[SIZE];
    int temp, j;

    for (int attempt = 0; attempt < 20; attempt++) {
        // 랜덤 데이터를 복사
        for (int i = 0; i < SIZE; i++) {
            data[i] = list[i];
        }

        // 비교 횟수 초기화
        comparisonCount = 0;

        // 삽입 정렬
        for (int i = 1; i < SIZE; i++) {
            temp = data[i];
            for (j = i - 1; j >= 0 && data[j] > temp; j--) {
                data[j + 1] = data[j];
                comparisonCount++;
            }
            data[j + 1] = temp;
        }

        // 비교 횟수 누적
        totalComparisons += comparisonCount;
    }

    // 평균 비교 횟수 계산
    float averageComparisons = totalComparisons / 20.0;

    // 결과 출력
    printf("Insertion Sort Compare Average: %.2f\n", averageComparisons);
    printf("Insertion Sort Result:\n");
    printArray(data, SIZE);
}


// 버블 정렬 함수
void doBubbleSort(int list[]) {

    int totalMoves = 0;
    int data[SIZE];
    int temp;

    for (int attempt = 0; attempt < 20; attempt++) {
        // 랜덤 데이터를 복사
        for (int i = 0; i < SIZE; i++) {
            data[i] = list[i];
        }

        // 이동 횟수 초기화
        moveCount = 0;

        // 버블 정렬
        for (int i = 0; i < SIZE - 1; i++) {
            for (int j = 0; j < SIZE - 1 - i; j++) {
                if (data[j] > data[j + 1]) {
                    temp = data[j];
                    data[j] = data[j + 1];
                    data[j + 1] = temp;
                    moveCount += 3; // Swap에 대해 이동 3회
                }
            }
        }

        // 이동 횟수 누적
        totalMoves += moveCount;
    }

    // 평균 이동 횟수 계산
    float averageMoves = totalMoves / 20.0;

    // 결과 출력
    printf("Bubble Sort Move Average: %.2f\n", averageMoves);
    printf("Bubble Sort Result:\n");
    printArray(data, SIZE);
}


int main() {
    srand(time(NULL));
    int randomData[SIZE];

    generateRandomData(randomData);
    printf("Original Data:\n");
    printArray(randomData, SIZE);

    doSelectionSort(randomData);
    doInsertionSort(randomData);
    doBubbleSort(randomData);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 100

// 난수를 생성하여 배열을 채움
void generateRandomNumbers(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = rand() % 1000;
    }
}

// 배열 출력 함수
void printArray(int array[]) {
    for (int i = 0; i < ARRAY_SIZE; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Shell Sort 함수
void doShellSort(int array[], int gapType, int* totalComparisonCount, int* totalMoveCount) {
    int tempArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) tempArray[i] = array[i];  // 원본 배열 보존
    int gap, i, j, temp;

    *totalComparisonCount = 0;
    *totalMoveCount = 0;

    if (gapType == 2) { // n/2 방식
        for (gap = ARRAY_SIZE / 2; gap > 0; gap /= 2) {
            int comparisonCount = 0, moveCount = 0; // 현재 gap에서의 비교 및 이동 횟수
            printf("\nCurrent gap (n/2): %d\n", gap);
            for (i = gap; i < ARRAY_SIZE; i++) {
                temp = tempArray[i];
                moveCount++; // temp에 값 저장
                for (j = i; j >= gap && tempArray[j - gap] > temp; j -= gap) {
                    tempArray[j] = tempArray[j - gap];
                    comparisonCount++; // 비교 수행
                    moveCount++;       // 값 이동
                }
                if (j >= gap) comparisonCount++; // 마지막 비교를 카운트
                tempArray[j] = temp;
                moveCount++; // temp 값을 배열에 저장
            }
            *totalComparisonCount += comparisonCount;
            *totalMoveCount += moveCount;
            printf("Array after gap %d:\n", gap);
            printArray(tempArray);
            printf("Comparisons for this gap: %d, Moves for this gap: %d\n", comparisonCount, moveCount);
        }
    }
    else if (gapType == 3) { // n/3 방식
        for (gap = ARRAY_SIZE / 3; gap > 0; gap /= 3) {
            int comparisonCount = 0, moveCount = 0; // 현재 gap에서의 비교 및 이동 횟수
            printf("\nCurrent gap (n/3): %d\n", gap);
            for (i = gap; i < ARRAY_SIZE; i++) {
                temp = tempArray[i];
                moveCount++; // temp에 값 저장
                for (j = i; j >= gap && tempArray[j - gap] > temp; j -= gap) {
                    tempArray[j] = tempArray[j - gap];
                    comparisonCount++; // 비교 수행
                    moveCount++;       // 값 이동
                }
                if (j >= gap) comparisonCount++; // 마지막 비교를 카운트
                tempArray[j] = temp;
                moveCount++; // temp 값을 배열에 저장
            }
            *totalComparisonCount += comparisonCount;
            *totalMoveCount += moveCount;
            printf("Array after gap %d:\n", gap);
            printArray(tempArray);
            printf("Comparisons for this gap: %d, Moves for this gap: %d\n", comparisonCount, moveCount);
        }
    }

    // 최종 정렬된 배열 출력
    printf("\nSorted Array:\n");
    printArray(tempArray);
}

// 삽입 정렬 함수
void doInsertionSort(int array[], int* comparisonCount, int* moveCount) {
    int tempArray[ARRAY_SIZE];
    for (int i = 0; i < ARRAY_SIZE; i++) tempArray[i] = array[i];  // 원본 배열 보존
    int i, j, temp;

    *comparisonCount = 0;
    *moveCount = 0;

    for (i = 1; i < ARRAY_SIZE; i++) {
        temp = tempArray[i];
        (*moveCount)++; // temp에 값 저장
        for (j = i - 1; j >= 0 && tempArray[j] > temp; j--) {
            tempArray[j + 1] = tempArray[j];
            (*comparisonCount)++; // 비교 수행
            (*moveCount)++;       // 값 이동
        }
        if (j >= 0) (*comparisonCount)++; // 마지막 비교를 카운트
        tempArray[j + 1] = temp;
        (*moveCount)++; // temp 값을 배열에 저장
    }

    // 최종 정렬된 배열 출력
    printf("Sorted Array:\n");
    printArray(tempArray);
}

// main 함수
int main() {
    int array[ARRAY_SIZE];
    int totalComparisonCount, totalMoveCount;

    srand(time(0));
    generateRandomNumbers(array);

    // n/2 방식의 Shell Sort 수행 및 출력
    printf("Shell Sort (n/2):\n");
    doShellSort(array, 2, &totalComparisonCount, &totalMoveCount);
    printf("Shell Sort (n/2) - Total Comparisons: %d, Total Moves: %d\n\n", totalComparisonCount, totalMoveCount);

    // n/3 방식의 Shell Sort 수행 및 출력
    printf("Shell Sort (n/3):\n");
    doShellSort(array, 3, &totalComparisonCount, &totalMoveCount);
    printf("Shell Sort (n/3) - Total Comparisons: %d, Total Moves: %d\n\n", totalComparisonCount, totalMoveCount);

    // 삽입 정렬 수행 및 출력
    printf("Insertion Sort:\n");
    doInsertionSort(array, &totalComparisonCount, &totalMoveCount);
    printf("Insertion Sort - Total Comparisons: %d, Total Moves: %d\n", totalComparisonCount, totalMoveCount);

    return 0;
}

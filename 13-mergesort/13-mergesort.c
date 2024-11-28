#include <stdio.h>
#include <stdlib.h>

#define SIZE 100
#define MAX_VALUE 999

int comparisonCount = 0; // 비교 횟수
int moveCount = 0;       // 이동 횟수

// 랜덤 배열 생성
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % (MAX_VALUE + 1);
    }
}

// 배열 부분 출력 (처음 10개 + 중앙 근처)
void printPartialArray(int* array) {
    for (int i = 0; i < 10; i++) { // 처음 10개 값
        printf("%3d ", array[i]);
    }
    printf("| ");
    for (int i = SIZE / 2 - 1; i < SIZE / 2 + 10; i++) { // 중앙 - 1 ~ 중앙 + 10
        printf("%3d ", array[i]);
    }
    printf("\n");
}

// 병합 함수
void merge(int* array, int left, int mid, int right, int* stepCount, int isFirstRun) {
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    int* leftArray = (int*)malloc(leftSize * sizeof(int));
    int* rightArray = (int*)malloc(rightSize * sizeof(int));

    // 왼쪽, 오른쪽 서브 배열 복사
    for (int i = 0; i < leftSize; i++) {
        leftArray[i] = array[left + i];
        moveCount++; // 값을 temp에 넣는 이동
    }
    for (int i = 0; i < rightSize; i++) {
        rightArray[i] = array[mid + 1 + i];
        moveCount++; // 값을 temp에 넣는 이동
    }

    int i = 0, j = 0, k = left;

    // 병합 과정
    while (i < leftSize && j < rightSize) {
        comparisonCount++; // 비교 수행
        if (leftArray[i] <= rightArray[j]) {
            array[k] = leftArray[i];
            moveCount++; // 값을 temp에서 배열로 가져옴
            i++;
        }
        else {
            array[k] = rightArray[j];
            moveCount++; // 값을 temp에서 배열로 가져옴
            j++;
        }
        k++;
    }

    // 왼쪽 배열 잔여 요소 복사
    while (i < leftSize) {
        array[k] = leftArray[i];
        moveCount++; // 값을 temp에서 배열로 가져옴
        i++;
        k++;
    }

    // 오른쪽 배열 잔여 요소 복사
    while (j < rightSize) {
        array[k] = rightArray[j];
        moveCount++; // 값을 temp에서 배열로 가져옴
        j++;
        k++;
    }

    free(leftArray);
    free(rightArray);

    // 병합 후 출력 (10번마다, 첫 실행에 한해 출력)
    if (isFirstRun && (*stepCount % 10 == 0)) {
        printPartialArray(array);
    }

    (*stepCount)++;
}

// 반복적인 합병 정렬
void iterativeMergeSort(int* array, int isFirstRun) {
    int subArraySize, leftStart;
    int stepCount = 0; // 출력 카운터

    for (subArraySize = 1; subArraySize <= SIZE - 1; subArraySize *= 2) {
        for (leftStart = 0; leftStart < SIZE - 1; leftStart += 2 * subArraySize) {
            int mid = leftStart + subArraySize - 1;
            int rightEnd = (leftStart + 2 * subArraySize - 1 < SIZE - 1)
                ? leftStart + 2 * subArraySize - 1
                : SIZE - 1;

            merge(array, leftStart, mid, rightEnd, &stepCount, isFirstRun);
        }
    }
}

// 배열 전체 출력 (최종 결과용)
void printArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

// 메인 함수
int main() {
    int array[SIZE];
    int totalComparisons = 0, totalMoves = 0;

    for (int rounds = 0; rounds < 20; rounds++) {
        generateRandomArray(array);
        comparisonCount = 0;
        moveCount = 0;

        if (rounds == 0) {
            printf("Merge Sort Run\n");
            iterativeMergeSort(array, 1); // 첫 실행 시 출력 활성화

            printf("\nResult\n");
            printArray(array); // 최종 정렬된 결과 출력
        }
        else {
            iterativeMergeSort(array, 0); // 이후 실행에서는 출력 비활성화
        }

        totalComparisons += comparisonCount;
        totalMoves += moveCount;
    }

    // 평균 비교 및 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalComparisons / 20.0);
    printf("Average Moves: %.2f\n", totalMoves / 20.0);

    return 0;
}

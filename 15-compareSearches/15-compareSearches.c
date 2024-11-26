#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 1000

int compareCount = 0; // 전역변수

// 랜덤 배열 생성
void generateRandomArray(int* array) {
    for (int i = 0; i < SIZE; i++) {
        array[i] = rand() % 1000; // 0~999 사이의 숫자
    }
}

// 순차 탐색
int linearSearch(int* array, int target) {
    int localCompareCount = 0;
    for (int i = 0; i < SIZE; i++) {
        localCompareCount++;
        if (array[i] == target) {
            return localCompareCount;
        }
    }
    return localCompareCount; // 찾지 못했을 경우
}

// 평균 순차 탐색 비교 횟수
double getAverageLinearSearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 100; i++) {
        int key = rand() % 1000;       // 배열의 인덱스를 랜덤하게 선택
        int target = array[key];       // 해당 인덱스의 값을 목표로 설정
        totalCompareCount += linearSearch(array, target);
    }
    return (double)totalCompareCount / 100.0;
}

// 퀵 정렬: 배열 정렬 및 비교 횟수 계산
void quickSort(int* array, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(array, low, high);
        quickSort(array, low, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, high);
    }
}

int partition(int* array, int low, int high) {
    int pivot = array[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        compareCount++;
        if (array[j] < pivot) {
            i++;
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }
    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;
    return i + 1;
}

void getQuickSortCompareCount(int* array) {
    compareCount = 0; // 비교 횟수 초기화
    quickSort(array, 0, SIZE - 1);
}

// 평균 이진 탐색 비교 횟수
int binarySearch(int* array, int low, int high, int target) {
    int localCompareCount = 0;
    while (low <= high) {
        localCompareCount++;
        int mid = low + (high - low) / 2;
        if (array[mid] == target) {
            return localCompareCount;
        }
        if (array[mid] < target) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return localCompareCount; // 찾지 못했을 경우
}

double getAverageBinarySearchCompareCount(int* array) {
    int totalCompareCount = 0;
    for (int i = 0; i < 100; i++) {
        int key = rand() % 1000;       // 배열의 인덱스를 랜덤하게 선택
        int target = array[key];       // 해당 인덱스의 값을 목표로 설정
        totalCompareCount += binarySearch(array, 0, SIZE - 1, target);
    }
    return (double)totalCompareCount / 100.0;
}

// 배열 출력
void printArray(int* array) {
    printf("Array Sorting Result:\n");
    for (int i = 0; i < 20; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
    for (int i = SIZE - 20; i < SIZE; i++) {
        printf("%3d ", array[i]);
    }
    printf("\n");
}

// 메인 함수
int main(int argc, char* argv[]) {
    srand(time(NULL));
    int array[SIZE];

    // 랜덤 배열 생성
    generateRandomArray(array);

    // 평균 순차 탐색 비교 횟수 출력
    printf("Average Linear Search Compare Count: %.2f\n", getAverageLinearSearchCompareCount(array));

    // 퀵 정렬 및 비교 횟수 출력
    getQuickSortCompareCount(array);
    printf("Quick Sort Compare Count: %d\n", compareCount);

    // 정렬된 배열에서 평균 이진 탐색 비교 횟수 출력
    printf("Average Binary Search Compare Count: %.2f\n\n", getAverageBinarySearchCompareCount(array));

    // 정렬된 배열 출력
    printArray(array);

    return 0;
}

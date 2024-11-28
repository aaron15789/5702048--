#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 1000

int compareCount = 0; //전역변수

// 랜덤 배열 생성
void generateRandomArray(int* array) {
	for (int i = 0; i < SIZE; i++) {
		array[i] = rand() % 10000;
	}
}

//퀵 정렬
void QuickSort(int* array, int low, int high) {
	if (low < high) {
		int pivotIndex = partition(array, low, high);
		QuickSort(array, low, pivotIndex - 1);
		QuickSort(array, pivotIndex + 1, high);
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

// 평균 이진 탐색 비교 횟수
int binarySearch(int* array, int low, int high, int target) {
	int localCompareCount = 0;
	while (low <= high) {
		localCompareCount++;
		int mid = low + (high - low) / 2;
		if (array[mid] == target) {
			return localCompareCount;
		}

		localCompareCount++;
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

// 평균 보간 탐색 비교 횟수
int interpol_search(int* array, int n, int key, int* compareCount)
{
	int low = 0, high = n - 1;
	*compareCount = 0;  // 비교 횟수 초기화

	while ((array[high] >= key) && (key >= array[low])) {

		// 보간 공식
		int j = low + ((float)(key - array[low]) / (array[high] - array[low]) * (high - low));

		(*compareCount)++; // j 계산 및 범위 확인
		if (j < low || j > high) { // 보간 위치가 배열 범위를 벗어나면 종료
			break;
		}

		(*compareCount)++; // key > array[j] 비교
		if (key > array[j]) {
			low = j + 1;
		}
		else {
			(*compareCount)++; // key < array[j] 비교
			if (key < array[j]) {
				high = j - 1;
			}
			else {
				(*compareCount)++; // key == array[j] 비교
				return j;          // 탐색 성공
			}
		}
	}

	(*compareCount)++; // 마지막 비교
	if (array[low] == key) {
		return low;
	}
	else {
		(*compareCount)++; // 실패 시 마지막 비교
		return -1;         // 탐색 실패
	}
}

double getAverageInterpolationSearchComparecount(int* array) {
	int totalCompareCount = 0;

	for (int i = 0; i < 100; i++) {
		int key = rand() % SIZE;       // 배열의 인덱스를 랜덤하게 선택
		int target = array[key];       // 해당 인덱스의 값을 목표로 설정

		int compareCount = 0;          // 비교 횟수 변수 (스택 내 안전한 변수)
		interpol_search(array, SIZE, target, &compareCount); // 탐색 수행
		totalCompareCount += compareCount;
	}

	return (double)totalCompareCount / 100.0; // 평균 비교 횟수 반환
}

// 배열 출력
void printArray(int* array) {
	printf("Array Sorting Result:\n");
	for (int i = 0; i < 20; i++) {
		printf("%4d ", array[i]);
	}
	printf("\n");
	for (int i = SIZE - 20; i < SIZE; i++) {
		printf("%4d ", array[i]);
	}
	printf("\n");
}

int main(int argc, char* argv[]) {
	srand(time(NULL));
	int array[SIZE];
	generateRandomArray(array);
	QuickSort(array, 0, SIZE - 1);
	printArray(array);
	printf("Average Compare Count of Binary Search: %.2f\n",
		getAverageBinarySearchCompareCount(array));
	printf("Average Compare Count of Interpolation Search: %.2f\n",
		getAverageInterpolationSearchComparecount(array));
	return 0;
}

#QuickSort {Result Image}
![image](https://github.com/user-attachments/assets/c7f6c912-5e13-446a-8b41-1aacc740f606)
![image](https://github.com/user-attachments/assets/e5587c51-8ee1-4916-9464-6088e20efd95)
![image](https://github.com/user-attachments/assets/61199c3a-5dbf-409a-b880-5eb013fe47cb)

1. 선택정렬(Selection Sort) : 요소 위치 변경 횟수를 줄여 버블정렬을 일부 개선한 알고리즘. 정렬 순서가 맞지 않으면 무조건 자리를 바꿔줬던 버블정렬과 달리, 1회 iteration마다 최소값(혹은 최대값)을 찾고 단 한번만 해당 요소 위치를 바꿔줌.

2. 삽입정렬(insertion sort) : 모든 요소에 대해 앞에서부터 차례대로 이미 정렬된 배열(sorted list)과 비교하여 sorted list 내 자신의 위치를 찾아 삽입함으로써 정렬을 완성, 입력데이터가 이미 정렬된 상태라면 O(n)O(n)

의 빠른 속도를 보이지만 그렇지 않은 경우 다른 기법을 적용하는 것이 나음.

3. 버블정렬(Bubble sort) : 주어진 배열의 마지막 위치에 있는 요소를, 정렬되지 않은 직전 요소부터 첫 요소에 이르기까지 비교해 정렬 순서가 맞지 않은 모든 case에 대해 요소 위치를 바꿔줌. 이를 요소 수만큼 반복. 가장 간단하지만 비효율적인 알고리즘.

4. 쉘정렬(shell sort) : 정렬되지 않은 배열의 경우 비효율적인 삽입정렬을 개선한 기법. 주어진 배열의 일정 간격(gap)만큼의 요소들에 대해 삽입정렬을 반복 수행.

5. 합병정렬(merge sort) : 리스트를 잘게 쪼갠 뒤 둘씩 크기를 비교해 정렬하고 분리된 리스트를 재귀적으로 합쳐서 정렬을 완성, 분할된 리스트를 저장해둘 공간이 필요해 메모리 소모량이 큰 편

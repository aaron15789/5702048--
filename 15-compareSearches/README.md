#CompareSearches{Result Image}
![image](https://github.com/user-attachments/assets/aa6672d0-b88c-4102-828e-20dec7360776)
![image](https://github.com/user-attachments/assets/36e605d0-adae-4afc-aa95-e3de07af0c1b)
![image](https://github.com/user-attachments/assets/37230460-4df2-469b-8d15-b54b197b4c44)
퀵 정렬에서 비교 한 번 수행
이 후 이진 탐색은 이 정렬된 배열에서 작동하여, 탐색 과정에서 평균적으로 약 10회 미만의 비교로 목표 값을 찾을 수 있음.
즉, 순차 탐색의 평균 비교횟수가 500회인 것을 보면 이보다 훨씬 적은 횟수로 비교 가능
이진 탐색의 특성을 살펴보면 
1. 탐색 범위를 절반으로 줄이는 방식
=> 순차 탐색은 모든 요소 확인<->이진 탐색은 매번 탐색 범위 절반으로 줄읾

2. 정렬의 효과

3. 시간 복잡도 차이
=> 순차 탐색은 O(n),이진탐색은 O(log n)

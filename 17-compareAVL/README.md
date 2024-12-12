# AVL Tree {Result Image}
![image](https://github.com/user-attachments/assets/e46cd47a-e353-4297-883e-0b83ac3e88c8)
![image](https://github.com/user-attachments/assets/bbf9f639-5523-4a05-9ab3-88349772b0c6)
![image](https://github.com/user-attachments/assets/3716131f-a159-4d5c-9b34-ac378fdfc071)
이진탐색트리
평균적으로 균형 잡힌 BST의 경우 탐색 횟수는 O(log n)입니다. 그러나 데이터가 정렬된 상태로 삽입되면 트리가 편향되어 최악의 경우 O(n)까지 증가할 수 있습니다.

AVL 트리
AVL 트리는 항상 균형을 유지하므로, 탐색 횟수는 항상 O(log n)입니다. 이는 AVL 트리가 최악의 경우에도 균형을 유지하기 때문입니다.

이를 토대로 균형상태와 탐색의 효율성을 비교해보면
AVL 트리는 삽입 및 삭제 시 추가적인 회전 작업을 통해 균형을 유지하므로, 탐색 성능이 항상 일정하게 유지됩니다.
반면, BST는 삽입 및 삭제 시 균형을 고려하지 않기 때문에, 특정 데이터 삽입 패턴에 따라 성능이 크게 저하될 수 있습니다.

탐색 효율성은
AVL 트리는 탐색 시 항상 O(log n)의 성능을 보장하므로, 대규모 데이터셋에서 더 효율적입니다.
BST는 데이터의 삽입 순서에 따라 성능이 달라지므로, 예측할 수 없는 성능을 보일 수 있습니다.

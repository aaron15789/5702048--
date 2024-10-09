#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left;
    struct ThreadNode* right;
    int isThreaded; // 1: 오른쪽이 스레드, 0: 일반 오른쪽 자식
} ThreadNode;


TreeNode* Insert(TreeNode* node, int data) {
    if (node == NULL) {
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = data;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (data < node->data) {
        node->left = Insert(node->left, data);
    }
    else {
        node->right = Insert(node->right, data);
    }
    return node;
}

TreeNode* GenerateBinaryTree(int inputData[]) {
    TreeNode* root = NULL;
    for (int i = 0; i < 15; i++) { 
        root = Insert(root, inputData[i]);
    }
    return root;
}


void BinaryTreeInOrder(TreeNode* root) {
    if (root == NULL) return;
    BinaryTreeInOrder(root->left);
    printf("%d ", root->data);
    BinaryTreeInOrder(root->right);
}

// 스레드 이진 트리 생성
void CreateThreadedTree(TreeNode* root, ThreadNode** prev, ThreadNode** tRoot) {
    if (root == NULL) return;

    // 왼쪽 서브트리를 재귀적으로 방문
    CreateThreadedTree(root->left, prev, tRoot);

    // 새로운 스레드 노드 생성
    ThreadNode* newNode = (ThreadNode*)malloc(sizeof(ThreadNode));
    newNode->data = root->data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->isThreaded = 0;

    // 이전 노드와 연결
    if (*prev != NULL) {
        (*prev)->right = newNode;
        (*prev)->isThreaded = 1; 
    }
    else {
        *tRoot = newNode; // 첫 번째 노드가 루트 노드
    }

    *prev = newNode; // 현재 노드를 이전 노드로 설정

    // 오른쪽 서브트리를 재귀적으로 방문
    CreateThreadedTree(root->right, prev, tRoot);
}

ThreadNode* GenerateThreadTree(TreeNode* root) {
    ThreadNode* prev = NULL;
    ThreadNode* tRoot = NULL;
    CreateThreadedTree(root, &prev, &tRoot);
    return tRoot;
}

// 스레드 이진 트리 중위 순회
void ThreadTreeInOrder(ThreadNode* root) {
    ThreadNode* current = root;
    while (current != NULL) {
        while (current->left != NULL) {
            current = current->left;
        }
        printf("%d ", current->data);

        // 오른쪽 자식이 스레드인 경우
        if (current->isThreaded) {
            current = current->right; // 스레드로 이동
        }
        else {
            current = current->right; // 일반 오른쪽 자식으로 이동
        }
    }
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };

    
    TreeNode* root = GenerateBinaryTree(inputData);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    
    ThreadNode* tRoot = GenerateThreadTree(root);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(tRoot);
    printf("\n");

    // 메모리 해제
    free(root);
    free(tRoot);

    return 0;
}

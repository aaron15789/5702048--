#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int key;
    struct Node* left, * right;
    int height;  // AVL 전용
} Node;

int compareCount = 0;
int searchCount = 0;

// AVL 관련 함수
int getHeight(Node* node) {
    return node ? node->height : 0;
}

int getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T = x->right;
    x->right = y;
    y->left = T;
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    return x;
}

Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T = y->left;
    y->left = x;
    x->right = T;
    x->height = 1 + (getHeight(x->left) > getHeight(x->right) ? getHeight(x->left) : getHeight(x->right));
    y->height = 1 + (getHeight(y->left) > getHeight(y->right) ? getHeight(y->left) : getHeight(y->right));
    return y;
}

Node* insertAVL(Node* node, int key) {
    if (!node) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        newNode->height = 1;
        return newNode;
    }
    if (key < node->key) {
        node->left = insertAVL(node->left, key);
    }
    else if (key > node->key) {
        node->right = insertAVL(node->right, key);
    }
    else {
        return node;
    }

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

Node* deleteAVL(Node* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = deleteAVL(root->left, key);
    }
    else if (key > root->key) {
        root->right = deleteAVL(root->right, key);
    }
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = root->right;
            while (temp->left) temp = temp->left;
            root->key = temp->key;
            root->right = deleteAVL(root->right, temp->key);
        }
    }

    if (!root) return root;

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0) {
        return rotateRight(root);
    }
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0) {
        return rotateLeft(root);
    }
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}

//AVL트리 탐색
Node* searchAVL(Node* node, int key) {
    if (!node) return NULL;
    compareCount++;
    if (key == node->key) return node;
    compareCount++;
    if (key < node->key) return searchAVL(node->left, key);
    return searchAVL(node->right, key);
}

// 이진 탐색 트리 관련 함수
Node* insert(Node* node, int key) {
    if (!node) {
        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->key = key;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else if (key > node->key) {
        node->right = insert(node->right, key);
    }
    return node;
}

Node* delete(Node* root, int key) {
    if (!root) return root;

    if (key < root->key) {
        root->left = delete(root->left, key);
    }
    else if (key > root->key) {
        root->right = delete(root->right, key);
    }
    else {
        if (!root->left || !root->right) {
            Node* temp = root->left ? root->left : root->right;
            if (!temp) {
                temp = root;
                root = NULL;
            }
            else {
                *root = *temp;
            }
            free(temp);
        }
        else {
            Node* temp = root->right;
            while (temp->left) temp = temp->left;
            root->key = temp->key;
            root->right = delete(root->right, temp->key);
        }
    }
    return root;
}

//이진탐색트리 탐색
Node* search(Node* node, int key) {
    if (!node) return NULL;
    compareCount++;
    if (key == node->key) return node;
    compareCount++;
    if (key < node->key) return search(node->left, key);
    return search(node->right, key);
}

// 트리 메모리 해제
void freeTree(Node* node) {
    if (!node) return;
    freeTree(node->left);
    freeTree(node->right);
    free(node);
}

// AVL과 BST 작업 수행
void doAVLBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000; 
        if (A == 0) {
            root = insertAVL(root, B);
        }
        else if (A == 1) {
            root = deleteAVL(root, B);
        }
        else {
            searchCount++;
            searchAVL(root, B);
        }
    }
}

void doBinaryBatch(Node* root) {
    for (int i = 0; i < 2000; i++) {
        int A = rand() % 3;
        int B = rand() % 1000;
        if (A == 0) {
            root = insert(root, B);
        }
        else if (A == 1) {
            root = delete(root, B);
        }
        else {
            searchCount++;
            search(root, B);
        }
    }
}

// 메인 함수
int main(int argc, char* argv[]) {
    Node* root = NULL;
    srand(time(NULL));
    float allCount = 0.0;

    // AVL 트리 작업
    doAVLBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average AVL compare count: %.2f\n", allCount);

    // 메모리 해제
    freeTree(root);
    root = NULL;
    compareCount = searchCount = 0;

    // 이진 탐색 트리 작업
    doBinaryBatch(root);
    allCount = (float)compareCount / searchCount;
    printf("average Bin compare count: %.2f\n", allCount);

    freeTree(root);
    return 0;
}

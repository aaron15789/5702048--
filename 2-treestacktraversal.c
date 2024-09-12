#include <stdio.h>
#include <stdlib.h>

typedef int value;

typedef struct tree_node {
    value data;
    struct tree_node* left, * right;
} TreeNode;

typedef TreeNode* element;

typedef struct StackNode {
    element data;
    struct StackNode* link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) {
    s->top = NULL;
}

int is_empty(LinkedStackType* s) {
    return (s->top == NULL);
}

void push(LinkedStackType* s, element item) {
    StackNode* newStackNode = (StackNode*)malloc(sizeof(StackNode));
    newStackNode->data = item;
    newStackNode->link = s->top;
    s->top = newStackNode;
    printf("push(%d) ", item->data); // push 작업 출력
}

element pop(LinkedStackType* s) {
    if (is_empty(s)) return NULL;
    StackNode* temp = s->top;
    element data = temp->data;
    s->top = temp->link;
    printf("pop(%d) ", data->data); // pop 작업 출력
    free(temp);
    return data;
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode; // 왼쪽 자식
    }
    else {
        node->right = newNode; // 오른쪽 자식
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 9);

    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);

    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);

    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);

    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);

    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);

    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

void LinkPreorder(TreeNode* root) {
    if (root == NULL) return;

    LinkedStackType s;
    init(&s);
    push(&s, root);

    while (!is_empty(&s)) {
        TreeNode* node = pop(&s);
        printf("visit(%d)\n", node->data); // 노드 방문 출력
        if (node->right) push(&s, node->right);
        if (node->left) push(&s, node->left);
    }
}

void LinkInorder(TreeNode* root) {
    LinkedStackType s;
    TreeNode* nptr = root;
    init(&s);

    while (nptr != NULL || !is_empty(&s)) {
        while (nptr != NULL) {
            push(&s, nptr);
            nptr = nptr->left;
        }
        nptr = pop(&s);
        printf("visit(%d)\n", nptr->data); // 노드 방문 출력
        nptr = nptr->right;
    }
}

void LinkPostorder(TreeNode* root) {
    if (root == NULL) return;

    LinkedStackType s1, s2;
    init(&s1);
    init(&s2);
    push(&s1, root);

    while (!is_empty(&s1)) {
        TreeNode* node = pop(&s1);
        push(&s2, node);
        if (node->left) push(&s1, node->left);
        if (node->right) push(&s1, node->right);
    }

    while (!is_empty(&s2)) {
        TreeNode* node = pop(&s2);
        printf("visit(%d)\n", node->data); // 노드 방문 출력
    }
}

void LinkOrders(TreeNode* root) {
    printf("전위 순회: ");
    LinkPreorder(root);
    printf("\n중위 순회: ");
    LinkInorder(root);
    printf("\n후위 순회: ");
    LinkPostorder(root);
    printf("\n");
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode)); // 노드 생성
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);
    LinkOrders(root);

    // 메모리 해제
    free(root); // 루트 노드 메모리 해제
    return 0;
}

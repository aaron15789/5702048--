#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef TreeNode* element;	
typedef struct QueueNode {	
    element data;
    struct QueueNode* link;
} QueueNode;

typedef struct {		
    QueueNode* front, * rear;
} LinkedQueueType;

void init(LinkedQueueType* q) {
    q->front = q->rear = NULL;
}

int is_empty(LinkedQueueType* q) {
    return (q->front == NULL);
}


void enqueue(LinkedQueueType* q, element data) {
    QueueNode* temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->data = data; 		
    temp->link = NULL; 		
    if (is_empty(q)) { 		
        q->front = temp;
        q->rear = temp;
    }
    else { 		
        q->rear->link = temp;  
        q->rear = temp;
    }
}


element dequeue(LinkedQueueType* q) {
    QueueNode* temp = q->front;
    element data;
    if (is_empty(q)) {		
        fprintf(stderr, "큐가 비어있음\n");
        exit(1);
    }
    else {
        data = temp->data; 	
        q->front = q->front->link; 
        if (q->front == NULL) 	
            q->rear = NULL;
        free(temp); 		
        return data; 		
    }
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode; 
    }
    else {
        node->right = newNode; 
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

int GetSumOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    LinkedQueueType q;
    init(&q);
    enqueue(&q, root);
    int sum = 0;

    while (!is_empty(&q)) {
        TreeNode* current = dequeue(&q);
        sum += current->data;

        if (current->left) enqueue(&q, current->left);
        if (current->right) enqueue(&q, current->right);
    }

    return sum;
}

int GetNumberOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    LinkedQueueType q;
    init(&q);
    enqueue(&q, root);
    int count = 0;

    while (!is_empty(&q)) {
        TreeNode* current = dequeue(&q);
        count++;

        if (current->left) enqueue(&q, current->left);
        if (current->right) enqueue(&q, current->right);
    }

    return count;
}

int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return -1;

    LinkedQueueType q;
    init(&q);
    enqueue(&q, root);
    int height = 0;

    while (!is_empty(&q)) {
        int nodeCount = 0;
        QueueNode* temp = q.front;

        
        while (temp != NULL) {
            nodeCount++;
            temp = temp->link;
        }

        height++;
        for (int i = 0; i < nodeCount; i++) {
            TreeNode* current = dequeue(&q);
            if (current->left) enqueue(&q, current->left);
            if (current->right) enqueue(&q, current->right);
        }
    }

    return height;
}

int GetNumberOfLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;

    LinkedQueueType q;
    init(&q);
    enqueue(&q, root);
    int leafCount = 0;

    while (!is_empty(&q)) {
        TreeNode* current = dequeue(&q);

        if (current->left == NULL && current->right == NULL) {
            leafCount++;
        }
        else {
            if (current->left) enqueue(&q, current->left);
            if (current->right) enqueue(&q, current->right);
        }
    }

    return leafCount;
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode)); 
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateLinkTree(root);

    printf("노드의 합: %d\n", GetSumOfNodes(root));
    printf("노드의 개수: %d\n", GetNumberOfNodes(root));
    printf("트리의 높이: %d\n", GetHeightOfTree(root));
    printf("리프 노드의 개수: %d\n", GetNumberOfLeafNodes(root));

    
    return 0;
}

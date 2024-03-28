#include<stdio.h>
#include<stdlib.h>

struct Node {
    int val;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->val = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* findMaximum(struct Node* root) {

    while(root->right != NULL) {
        root = root->right;
    }
    return root;
}

int findPredecessorIterative(struct Node* root, int key) {

    struct Node* pred = NULL;

    while(1) {
        if (key < root->val) {
            root = root->left;
        }else if(key > root->val) {
            pred = root;
            root = root->right;
        }else {
            if(root->left != NULL) {
                pred = findMaximum(root->left);
            }
            break;
        }

        if(root == NULL) {
            return -1;
        }
    }

    return pred ? pred->val : -1;
}

void inorderTraversal(struct Node* root) {

    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left);
    printf("%d ", root->val);
    inorderTraversal(root->right);
}

int main() {

    struct Node* tree = createNode(5);
    tree->left = createNode(2);
    tree->right = createNode(12);
    tree->left->left = createNode(1);
    tree->left->right = createNode(3);
    tree->right->left = createNode(9);
    tree->right->right = createNode(21);

    printf("Inorder Predecessor: ");
    inorderTraversal(tree);

    int key = 9;
    int predecessor = findPredecessorIterative(tree, key);
    if (predecessor != -1) {
        printf("\nPredecessor of %d: %d\n", key, predecessor);
    } else {
        printf("Predecessor of %d not found.\n", key);
    }

    return 0;
}
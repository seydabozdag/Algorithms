#include<stdio.h>
#include<stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

struct Node* createNode(int value) {

    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if(newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->data = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

struct Node* insertNode(struct Node* root, int value) {

    if(root == NULL) {
        return createNode(value);
    }

    if(value < root->data) {
        root->left = insertNode(root->left, value);
    }else {
        root->right = insertNode(root->right, value);
    }

    return root;
}

struct Node* findMin(struct Node* node) {

    if (node->left == NULL) {
        return node;
    }

    return findMin(node->left);
}

struct Node* findInorderSuccessor(struct Node* root, struct Node* target) {

    if(root == NULL || target == NULL) {
        return NULL;
    }

    if(target->right != NULL) {
        return findMin(target->right);
    }else {
        struct Node* successor = NULL;
        struct Node* current = root;

        while(current != NULL) {
            if(target->data < current->data) {
                successor = current;
                current = current->left;
            }else if (target->data > current->data) {
                current = current->right;
            }else {
                break; 
            }
        }

        return successor;
    }
}

void inorderTraversal(struct Node* root) {

    if (root == NULL) {
        return;
    }

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

int main() {

    struct Node* root = NULL;

    root = insertNode(root, 20);
    insertNode(root, 9);
    insertNode(root, 25);
    insertNode(root, 5);
    insertNode(root, 12);
    insertNode(root, 27);
    insertNode(root, 11);
    insertNode(root, 14);

    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");

    struct Node* target = root->left->right; 
    printf("Target node: %d\n", target->data);

    struct Node* successor =  findInorderSuccessor(root, target);

    if (successor != NULL) {
        printf("Inorder Successor of %d: %d\n", target->data, successor->data);
    } else {
        printf("Inorder Successor of %d not found.\n", target->data);
    }

    return 0;
}
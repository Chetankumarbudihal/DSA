#include <stdio.h>
#include <stdlib.h>

// Structure for a BST node
typedef struct Node {
    int data;
    int size;
    struct Node* left;
    struct Node* right;
} Node;

FILE *fp1,*fp2,*fp3,*fp4;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->size = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in the BST
Node* insertNode(Node* root, int data) {
    if (root == NULL) {
        return createNode(data);
    }

    if (data < root->data) {
        root->left = insertNode(root->left, data);
        root->size++;  // Increment the size of left subtree
    } else {
        root->right = insertNode(root->right, data);
    }

    return root;
}

// Function to find the size of the left subtree
int findSize(Node* root) {
    if (root == NULL) {
        return 0;
    }

    return root->size;
}

// Function to perform type 1 query
Node* type1Query(Node* root, int i, int j, Node** modifiedNodes) {
    // Find the i-th node and its parent node
    Node* node = root;
    Node* parent = NULL;
    int count = findSize(node->left) + 1;

    while (count != i) {
        parent = node;
        if (i < count) {
            node = node->left;
            count -= (findSize(node->right) + 1);
        } else {
            node = node->right;
            count += (findSize(node->left) + 1);
        }
    }

    // Update the modifiedNodes array with the nodes to be moved
    for (int k = 0; k < j - i + 1; k++) {
        modifiedNodes[k] = node;
        node = node->right;
    }

    // Update the BST by removing the nodes from i to j
    if (parent == NULL) {
        root = node;
    } else {
        if (parent->left == node) {
            parent->left = node;
        } else {
            parent->right = node;
        }
    }

    return root;
}

// Function to perform type 2 query
Node* type2Query(Node* root, int i, int j, Node** modifiedNodes) {
    // Find the i-th node and its parent node
    Node* node = root;
    Node* parent = NULL;
    int count = findSize(node->left) + 1;

    while (count != i) {
        parent = node;
        if (i < count) {
            node = node->left;
            count -= (findSize(node->right) + 1);
        } else {
            node = node->right;
            count += (findSize(node->left) + 1);
        }
    }

    // Update the modifiedNodes array with the nodes to be moved
    for (int k = 0; k < j - i + 1; k++) {
        modifiedNodes[k] = node;
        node = node->right;
    }

    // Update the BST by removing the nodes from i to j
    if (parent == NULL) {
        root = node;
    } else {
        if (parent->left == node) {
            parent->left = node;
        } else {
            parent->right = node;
        }
    }

    return root;
}

// Function to print the resulting array and its size
void printResultArray(Node** modifiedNodes, int size,FILE *fp4) {
    printf("%d\n", size);
    for (int i = 0; i < size; i++) {
        fprintf(fp4,"%d ", modifiedNodes[i]->data);
    }
    printf("\n");
}

// Function to free the memory allocated for the BST
void freeBST(Node* root) {
    if (root == NULL) {
        return;
    }

    freeBST(root->left);
    freeBST(root->right);
    free(root);
}

int main() {
    int N, M;
    fp1=fopen("options.txt","r");
    fp2=fopen("elemets.txt","r");
    fp3=fopen("queries.txt","r");
    fscanf(fp1,"%d %d", &N, &M);

    // Build the initial BST representing the array
    Node* root = NULL;
    for (int i = 1; i <= N; i++) {
        int data;
        fscanf(fp2,"%d", &data);
        root = insertNode(root, data);
    }

    Node** modifiedNodes = (Node**)malloc(M * sizeof(Node*));

    // Process the queries
    for (int i = 0; i < M; i++) {
        int type, iVal, jVal;
        fscanf(fp3,"%d %d %d", &type, &iVal, &jVal);

        if (type == 1) {
            root = type1Query(root, iVal, jVal, modifiedNodes);
        } else if (type == 2) {
            root = type2Query(root, iVal, jVal, modifiedNodes);
        }
    }
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fp4=fopen("modifiedelements.txt","w")
    // Print the resulting array and its size
    printResultArray(modifiedNodes, M,fp4);
    fclose(fp4);
    // Free the memory allocated for the BST
    freeBST(root);
    free(modifiedNodes);

    return 0;
}

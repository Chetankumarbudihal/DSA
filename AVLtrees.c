#include <stdio.h>
#include <stdlib.h>
#include<time.h>
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};
typedef struct Node *NODE;
FILE *fp,*fpr;
int f=0;
int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(NODE node) {
    if (node == NULL)
        return 0;
    return node->height;
}

NODE createNode(int key) {
    NODE newNode = (NODE)malloc(sizeof(struct Node));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

NODE rightRotate(NODE y) {
    NODE x = y->left;
    NODE T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

NODE leftRotate(NODE x) {
    NODE y = x->right;
    NODE T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(NODE node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

NODE insert(NODE node, int key) {
    if (node == NULL)
        return createNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Duplicate keys are not allowed in AVL tree
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void PreOrder(NODE node,FILE *fp) {
    if (node != NULL) {
        fprintf(fp,"%d\n", node->key);
        PreOrder(node->left,fp);
        PreOrder(node->right,fp);
        f++;
    }
}

int main() {
    NODE root = NULL;
    int n,x;
    double start,stop;
    fpr=fopen("random.txt","w+");
    fp=fopen("AVLtree.txt","w+");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        fprintf(fpr,"%d ",rand()%100);
    }
    rewind(fpr);
    start=clock();
    for(int i=0;i<n;i++)
    {
        fscanf(fpr,"%d",&x);
        root = insert(root,x);
    }
    stop=clock();
    printf("Time taken: %lf\n",(stop-start)/CLOCKS_PER_SEC);
    fprintf(fp,"Inorder traversal of the constructed AVL tree: \n");
    PreOrder(root,fp);
    printf("%d elements in the tree",f);
    fclose(fp);
    return 0;
}

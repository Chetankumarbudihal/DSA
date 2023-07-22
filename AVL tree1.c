#include<stdio.h>
#include<stdlib.h>
#include<time.h>
struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

typedef struct Node *NODE;
FILE *fp,*fpr;
int f;

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int height(NODE node)
{
    if (node == NULL)
        return 0;
    return node->height;
}

NODE newNode(int key)
{
    NODE node = (NODE)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

NODE rightRotate(NODE y)
{
    NODE x = y->left;
    NODE T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

NODE leftRotate(NODE x)
{
    NODE y = x->right;
    NODE T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

int getBalance(NODE node)
{
    if (node == NULL)
        return 0;

    return height(node->left) - height(node->right);
}

NODE insert(NODE node, int key) {
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);

    else if (key > node->key)
        node->right = insert(node->right, key);

    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    if (balance > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

NODE minValueNode(NODE node)
{
    NODE current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

NODE deleteNode(NODE root, int key)
{
    if (root == NULL)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);

    else if (key > root->key)
        root->right = deleteNode(root->right, key);

    else
    {
        if ((root->left == NULL) || (root->right == NULL))
        {
            NODE temp = root->left ? root->left : root->right;
n
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else
                *root = *temp;
            free(temp);
        }

        else
        {
            NODE temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
        return root;
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void preOrder(NODE root,FILE *fp)
{
    if (root != NULL)
    {
        fprintf(fp,"%d ", root->key);
        preOrder(root->left,fp);
        preOrder(root->right,fp);
        f++;
    }
}

main()
{
    int n,x;
    double start,stop;
    NODE root = NULL;
    fpr=fopen("random.txt","w+");
    fp=fopen("AVLtree.txt","w");
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        fprintf(fpr,"%d ",rand()%1000);
    }
    rewind(fpr);
    start=clock();
    while(!feof(fpr))
    {
        fscanf(fpr,"%d",&x);
        root=insert(root,x);
    }
    stop=clock();

    fprintf(fp,"Preorder traversal of the AVL tree: ");
    f=0;
    preOrder(root,fp);
    printf("%d is the number of elements in the AVL tree\n",f);
    root = deleteNode(root, 41);
    fprintf(fp,"\nPreorder traversal after deletion of 41: ");
    f=0;
    preOrder(root,fp);
    printf("%d is the number of elements in the AVL tree\n",f);
    printf("%lf is the time taken.",(stop-start)/CLOCKS_PER_SEC);
}

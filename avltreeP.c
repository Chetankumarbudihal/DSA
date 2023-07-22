#include<stdio.h>
#include<stdlib.h>
struct NODE
{
    int data;
    struct NODE *left;
    struct NODE *right;
    int height;
};

typedef struct NODE *Node;

int balance(Node node)
{
    return (hgt(node->left)-hgt(node->right));
}

int hgt(Node node)
{
    if(node == NULL)
        return 0;
    else return node->height;
}

int maxof(int a, int b)
{

    return (a>b ? a: b);
}

Node createNode(int key)
{
    Node newn = (Node)malloc(sizeof(struct NODE));
    newn->data = key;
    newn->left = NULL;
    newn->right = NULL;
    newn->height = 1;
    return newn;
}

Node rightRotate(Node x)
{
    Node y = x->left;
    Node T2 = y->right;

    y->right = x;
    x->left = T2;

    y->height = 1 + maxof(hgt(y->left),hgt(y->right));
    x->height = 1 + maxof(hgt(x->left),hgt(x->right));

    return y;

}

Node leftRotate(Node x)
{
    Node y = x->right;
    Node T2 = y->left;

    y->left = x;
    x->right = T2;

    y->height = 1 + maxof(hgt(y->left),hgt(y->right));
    x->height = 1 + maxof(hgt(x->left),hgt(x->right));

    return y;

}

Node insert(Node node,int key)
{
    if(node == NULL)
        return createNode(key);
    else if(key < node->data)
        node->left = insert(node->left,key);
    else if(key > node->data)
        node->right = insert(node->right,key);

    node->height = 1 + maxof(hgt(node->left),hgt(node->right));

    int b = balance(node);

    if(b > 1 && key < node->left->data)
        return rightRotate(node);

    else if(b < -1 && key > node->right->data)
        return leftRotate(node);

    else if(b > 1 && key > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    else if(b < -1 && key < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void printPreorder(Node root)
{
    if(root != NULL)
    {
        printf("%d->",root->data);
        printPreorder(root->left);

        printPreorder(root->right);
    }
}

Node maxNode(Node node)
{
    Node temp = node;
    while(temp->right != NULL)
        temp = temp->right;
    return temp;
}

Node dlt(Node node,int key)
{
    if(node == NULL)
        return node;

    else if(key < node->data)
        node->left = dlt(node->left,key);

    else if(key > node->data)
        node->right = dlt(node->right,key);

    else{
        if(node->left == NULL)
        {
            Node temp = node->right;
            node = node->right;
            free(temp);
            return node;
        }
        else if(node->right == NULL)
        {
            Node temp = node->left;
            node = node->left;
            free(temp);
            return node;
        }
        else
        {
            Node temp = maxNode(node->left);
            node->data = temp->data;
            node->left = dlt(node->left,temp->data);

            int b = balance(node);

            if(b > 1 && balance(node->left) >= 0)
                return rightRotate(node);
            else if(b < -1 && balance(node->right) <= 0)
                return leftRotate(node);
            else if(b > 1 && balance(node->left) < 0)
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
            else if(b < -1 && balance(node->right) > 0)
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }
    }
    return node;
}

int main()
{
    Node root = NULL;
    int n,x;
    scanf("%d",&n);
    for(int i=0;i<n;i++)
    {
        scanf("%d",&x);
        root = insert(root,x);
    }
    printPreorder(root);
    /*printf("\n");
    root = dlt(root,41);

    printPreorder(root);*/
}

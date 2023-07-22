#include<stdio.h>
#include<stdlib.h>
//defining a structure
struct NODE{
    int key;
    struct NODE *left;
    struct NODE *right;
    int height;
};

typedef struct NODE *Node;
//creating the new node
Node createNode(int key)
{
    Node newn=(Node)malloc(sizeof(struct NODE));
    newn->key = key;
    newn->left = NULL;
    newn->right = NULL;
    newn->height = 1;
    return newn;
}

//Calculating the height of the node
int hgt(Node x)
{
    if(x == NULL)
        return 0;
    else return x->height;
}

//Maximum of height of left and right node
int max(int a,int b)
{
    return (a>b ? a : b);
}

// Check for the balance
int getBalance(Node root)
{
    return (hgt(root->left)-hgt(root->right));
}

// Rotate Left
Node leftRotate(Node x)
{
    Node y = x->right;
    Node T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(hgt(x->left),hgt(x->right));
    y->height = 1 + max(hgt(y->left),hgt(y->right));

    return y;
}

//Rotate Right
Node rightRotate(Node x)
{
    Node y = x->left;
    Node T2 = y->right;

    y->right = x;
    x->left = T2;

    x->height = 1 + max(hgt(x->left),hgt(x->right));
    y->height = 1 + max(hgt(y->left),hgt(y->right));

    return y;
}

// Insert the node in the tree
Node insert(Node node,int key)
{
    if(node == NULL)
        return createNode(key);
    else if(key < node->key)
        node->left = insert(node->left,key);
    else if(key > node->key)
        node->right = insert(node->right,key);

    node->height= 1 + max(hgt(node->left),hgt(node->right));

    int b = getBalance(node);

    if(b < -1 && key > node->right->key)
        return leftRotate(node);

    else if(b > 1 && key < node->left->key)
        return rightRotate(node);

    else if(b < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    else if(b > 1 && key > node->left->key)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    return node;
}

// getting the next immediate greater value in the tree
Node minNode(Node root)
{
    Node temp = root;
    while(temp->left != NULL)
        temp = temp->left;
    return temp;
}

Node dlt(Node root,int key)
{
    if(root == NULL)
        return root;
    else{
        if(key < root->key)
            root->left = dlt(root->left,key);
        else if(key > root->key)
            root->right = dlt(root->right,key);
        else
        {
            if(root->left == NULL)
            {
                Node temp=root;
                root = root->right;
                free(temp);
                return root;
            }
            else if(root->right == NULL)
            {
                Node temp=root;
                root = root->left;
                free(temp);
                return root;
            }
            else
            {
                Node temp = minNode(root->right);

                root->key = temp->key;

                root->right = dlt(root->right,temp->key);
            }
        }

        root->height = 1 + max(hgt(root->left),hgt(root->right));

        int b = getBalance(root);

        if(b < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        else if(b > 1 && getBalance(root->right) >= 0)
            return rightRotate(root);

        else if(b < -1 && getBalance(root->right) > 0)
        {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        else if(b > 1 && getBalance(root->right) < 0)
        {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        return root;
    }

}

//Printing the number in Preorder
void Preorder(Node node)
{
    if(node!=NULL)
    {
        printf("%d->",node->key);
        Preorder(node->left);
        Preorder(node->right);
    }
}

main()
{
    Node root=NULL;

    root = insert(root,54);
    root = insert(root,98);
    root = insert(root,91);
    root = insert(root,55);
    root = insert(root,14);
    root = insert(root,13);
    root = insert(root,52);
    root = insert(root,41);
    root = insert(root,22);
    root = insert(root,9);

    Preorder(root);

    root = dlt(root,41);

    printf("\n");
    Preorder(root);
}

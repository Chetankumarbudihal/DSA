#include<stdio.h>
#include<stdlib.h>
struct node{
    int data;
    struct node *left;
    struct node *right
    };
typedef struct node *NODE;
FILE *fp,*fpi,*fpr,*fpo;
NODE createNode(int ele)
{
    NODE newNode=(NODE)malloc(sizeof(struct node));
    newNode->data=ele;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}
NODE insertNode(NODE root,char ele)
{
    if(root==NULL)
    {
        root=createNode(ele);
    }
    else if(ele < root->data)
    {
        root->left=insertNode(root->left,ele);
    }
    else
    {
        root->right=insertNode(root->right,ele);
    }
    return root;
}
void displayInorder(NODE root,FILE *fpi)
{

    if(root!=NULL){

    displayInorder(root->left,fpi);
    fprintf(fpi,"%c  ",root->data);
    displayInorder(root->right,fpi);
    }
}
void displayPreorder(NODE root,FILE *fpr)
{

    if(root!=NULL){
    fprintf(fpr,"%c  ",root->data);
    displayPreorder(root->left,fpr);
    displayPreorder(root->right,fpr);
    }
}
void displayPostorder(NODE root,FILE *fpo)
{
    if(root!=NULL){

    displayPostorder(root->left,fpo);
    displayPostorder(root->right,fpo);
    fprintf(fpo,"%c  ",root->data);
    }
}
main()
{
    char a[52]="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    NODE root=NULL;
    char ele;
    int x;
    fp=fopen("random.txt","w");
    for(int i=0;i<100;i++)
    {
        x=rand()%52;
        printf("%d %c \n",x,a[x]);
        fprintf(fp,"%c",a[x]);
    }
    fclose(fp);
    fp=fopen("random.txt","r");
    fpo=fopen("postorder.txt","w+");
    fpr=fopen("preorder.txt","w+");
    fpi=fopen("inorder.txt","w+");
    for(int i=0;i<100;i++)
    {
        fscanf(fp,"%c",&ele);
        root=insertNode(root,ele);
    }
    printf("\nElements in INORDER:");
    displayInorder(root,fpi);
    printf("\nElements in PREORDER:");
    displayPreorder(root,fpr);
    printf("\nElements in POSTORDER:");
    displayPostorder(root,fpo);
    fclose(fp);
    fclose(fpi);
    fclose(fpr);
    fclose(fpo);
}

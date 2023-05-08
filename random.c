#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void store(void);
  struct Node{
    int data;
    struct Node*nxt;
    };
typedef struct Node *node;
node head;
node getnode(){
    node nw;
    nw=(node)malloc(sizeof(node));
    if(nw==NULL)
    {
        printf("memory not allocated");
    }
    nw->nxt=NULL;
    int a1;
    nw->data=0;
    return nw;
}


node insterend(head)
{
    node nw;
    node cur;
    int a1;
    printf("\nnumber of elements=\n");
    scanf("%d",&a1);
    a1=a1+1;
      FILE* pr1;
      int x;
    pr1=fopen("store.txt","r");
   for(int i=0;i<a1;i++)
   {
       nw=getnode();
       fscanf(pr1,"%d",&x);
       nw->data=x;


    if(head==NULL)
    {
        head=nw;
    }
    else
    {
        cur=head;
        while(cur->nxt!=NULL)
        {
            cur=cur->nxt;
        }
        cur->nxt=nw;
    }
  }
 fclose(pr1);
    int a;
    node cur1,cur2;
    cur1=head;
    cur2=cur1->nxt;
    while(cur1->nxt!=NULL)
    {
        if((cur1->data)>(cur2->data))
        {
            a=cur1->data;
            cur1->data=cur2->data;
            cur2->data=a;
        }
        cur1=cur1->nxt;
        cur2=cur1->nxt;
    }
    FILE*pr;
    cur1=head;
    pr=fopen("chetan.txt","w");
    cur1=head;
      do{
         fprintf(pr," %d",cur1->data);
         printf(" %d",cur1->data);
         cur1=cur1->nxt;
      }while(cur1->nxt!=NULL);
    fclose(pr);
}
void store(void)
{
     int k,n,a,b;
    printf("total numbers =\n");
    scanf("%d",&n);
    FILE* pr;
    pr=fopen("store.txt","w");
    printf("enter the range of number a,b(a must be less than b)\n");
    scanf("%d%d",&a,&b);
    char x[10]={' '};
    for(int i=0;i<n;i++)
    {
        k=rand()%(b-a+1);
        printf("%d ",k);
        fprintf(pr,"%d",k);
        fprintf(pr,"%s",x);
    }
    fclose(pr);
}

int main()
{
 store();
 time_t a,b;
 a=time(NULL);
 insterend( head);
 b=time(NULL);
 float t=b-a;
 printf("total time = %f",t);

}




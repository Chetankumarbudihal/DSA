#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void store_to_arry(int n,int arr1[100]);
void store(int n);
void sort(int n,int arr1[100]);


main()
{
int arr1[100],n;
store(n);
store_to_arry(n,arr1);
sort(n,arr1);
}
void store(int n)
{
     int k,a,b;
    printf("total numbers =\n");
    scanf("%d",&n);
    FILE* pr;
    pr=fopen("storeR2F.txt","w");
    printf("enter the range of number a,b(a must be less than b)\n");
    scanf("%d%d",&a,&b);
    char x[10]={' '};
    for(int i=0;i<n;i++)
    {
        k=rand()%(a-b+1)+a;
        printf("%d ",k);
        fprintf(pr,"%d",k);
        fprintf(pr,"%s",x);
    }
    fclose(pr);
}
void store_to_arry(int n,int arr1[100])
{
    FILE*pr2;
    pr2=fopen("storeR2F.txt","r");
    for(int i=0;i<n;i++)
    {
        fscanf(pr2,"%d",&arr1[i]);
        printf(" %d",arr1[i]);
    }
    fclose(pr2);
}
void sort(int n,int arr1[100])
{
    int temp;
    for(int i=0;i<n;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(arr1[i]>arr1[j])
            {
                temp=arr1[j];
                arr1[j]=arr1[i];
                arr1[i]=temp;
            }
        }
    }
    FILE*pr3;
    pr3=fopen("storeS2F.txt","w");
    for(int i=0;i<n;i++)
    {
        fprintf(pr3,"%d",&arr1[i]);
        printf(" %d",arr1[i]);
    }
    fclose(pr3);
}


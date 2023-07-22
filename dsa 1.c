#include<stdio.h>

main()
{
    FILE*ptr;
    ptr=fopen("files1.txt","w");
    int n;
    fscanf(ptr,"%d",&n);
    printf("%d",n);
}

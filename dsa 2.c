
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 main()
{
    FILE* ptr;FILE* ptr1;
    ptr=fopen("myfile1.txt","r");
    int n;
    fscanf(ptr,"%d",&n);
    printf("%d",n);
    int a[n];
    for(int i=0;i<n;i++)
    {
      fscanf(ptr,"%d",&a[i]);
    }
    for(int i=0;i<n;i++)
    {
      printf("%d",a[i]);
    }
    fclose(ptr);

    ptr1=fopen("myfile2.txt","w");
    for(int i=n-1;i>=0;i--)
    {
        fprintf(ptr1,"%d",a[i]);
    }
    fclose(ptr1);
    return 0;


}

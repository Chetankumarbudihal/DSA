#include<stdio.h>
#include<stdlib.h>
#include<string.h>

 main()
{
    FILE*ptr=NULL;
    ptr=fopen("myfile1.txt","w");
    char a[20];
    gets(a);
    fprintf(ptr,"%s",a);
    puts(a);

    return 0;


}

#include <stdio.h>
#include<stdlib.h>

void foo(int* &ptr)  // use reference
{
    int localvar = 10;
    ptr = (int *)malloc(sizeof(int));
    *ptr = localvar;
}

int main(){
    int *heapvar = NULL;
    foo(heapvar);  // pass pointer 
    printf("%d\n", *heapvar);
    free(heapvar);
    return 0;
}


// original : heapvar are not changed, therefore it remains NULL 
// void foo(int *ptr)
// {
//     int localvar = 10;
//     ptr = (int *)malloc(sizeof(int));
//     *ptr = localvar;
// }

// int main(){
//     int *heapvar=NULL;
//     foo(heapvar);
//     printf("%d\n", *heapvar);
//     return 0 ;
// }
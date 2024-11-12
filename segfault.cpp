#include <stdio.h>
#include<stdlib.h>

void foo(int* &ptr)  // 使用參考來修改指標
{
    int localvar = 10;
    ptr = (int *)malloc(sizeof(int));
    *ptr = localvar;
}

int main(){
    int *heapvar = NULL;
    foo(heapvar);  // 直接傳遞指標
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
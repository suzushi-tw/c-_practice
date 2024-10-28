#include <stdio.h>

// 修正 Increment 函數
void Increment(int *value)
{
    (*value)++;
}

// 定義 LOG 函數
void LOG(int value)
{
    printf("Value: %d\n", value);
}

int main()
{
    int a = 5;
    int b = 8;

    int &ref = a;
    ref = b;

    Increment(&a); // 傳遞指標
    Increment(&b);

    printf("a:%d\n", a);
    printf("ref:%d\n", ref);
    printf("b:%d\n", b);

    return 0;
}
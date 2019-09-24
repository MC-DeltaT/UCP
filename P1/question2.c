#include <stdio.h>


int main(void)
{
    int num1;
    int num2;

    printf("Enter integer 1: ");
    scanf("%d", &num1);

    printf("Enter integer 2: ");
    scanf("%d", &num2);

    if (num2 == 0)
    {
        printf("not divisible\n");
    }
    else if (num1 % num2 == 0)
    {
        printf("divisible\n");
    }
    else
    {
        printf("not divisible\n");
    }

    return 0;
}

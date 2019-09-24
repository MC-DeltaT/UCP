#include <stdio.h>


int factorial(int);


int main()
{
    int num;
    do
    {
        printf("Enter an integer: ");
        scanf("%d", &num);

        if (num >= 0)
        {
            int fact = factorial(num);
            printf("Factorial of %d is %d\n", num, fact);
        }
    } while (num >= 0);

    return 0;
}


/* Calculates the factorial of n. n must be >= 0. */
int factorial(int n)
{
    int result;
    int i;
    
    result = 1;
    for (i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

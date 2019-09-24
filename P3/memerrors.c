#include <stdio.h>
#include <stdlib.h>

void test1();
void test2();
void test3();
void test4();
void test5();


int main(int argc, char* argv[]) 
{
    int n;

    if(argc != 2) 
    {
        printf("Usage: %s <number>\n", argv[0]);
    }
    else 
    {
        n = atoi(argv[1]);
        switch(n) 
        {
            case 1: test1(); break;
            case 2: test2(); break;
            case 3: test3(); break;
            case 4: test4(); break;
            case 5: test5(); break;
                
            default:
                printf("Choose a number from 1 to 5\n");
        }
    }
    return 0;
}

void test1()
{
    int var;
    /* var should be initialised first. */
    if(var > 0)
        printf(">0\n");
    else
        printf("<=0\n");
}

void test2()
{
    int var;
    /* var should be initialised first. */
    printf("%d\n", var);
}

void test3() 
{
    int *ptr;
    ptr = (int*)malloc(sizeof(int));
    /* ptr should be freed here. */
}

void test4() 
{
    int *ptr;
    ptr = (int*)malloc(sizeof(int));
    free(ptr);
    /* Shouldn't free the same memory twice. */
    free(ptr);
}

void test5() 
{
    int *ptr;
    ptr = (int*)malloc(sizeof(int));
    free(ptr);
    /* Shouldn't access freed memory. */
    *ptr = 50;
}

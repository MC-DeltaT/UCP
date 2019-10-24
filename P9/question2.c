#include <time.h>


void sleep(unsigned long seconds)
{
    time_t start = time(NULL);
    time_t end = start + seconds;

    while (time(NULL) < end) {}
}



int main(void)
{
    sleep(5);

    return 0;
}

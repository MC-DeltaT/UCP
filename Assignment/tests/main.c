/* Unit test entry point. */

#include "board_test.h"
#include "linked_list_test.h"
#include "settings_test.h"

#include <stdlib.h>
#include <time.h>


int main(void)
{
    srand(time(NULL));

    boardTest();
    linkedListTest();
    settingsTest();

    return 0;
}

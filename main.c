#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main(int argc, char* argv[])
{
    PRIORITY_QUEUE stat = priority_queue_init_default();
    int i = 1;
    int j = 10;
    Status no = SUCCESS;

    while(i != 11 && j != 0 && no != FAILURE)
    {
        no = priority_queue_insert(stat, i, j);
        if (no == SUCCESS)
        {
            printf("INSERT: Data: %d, Priority: %d\n", j, i);
        }
        i++;
        j--;
    }

    while (priority_queue_is_empty(stat) == FALSE)
    {
        printf("The front of the priority queue is: %d\n", priority_queue_front(stat, &no));
        priority_queue_service(stat);
    }
    
    
    priority_queue_destroy(&stat);

    return 0;
}

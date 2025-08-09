#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

int32_t main()
{
    pid_t id;
    int32_t status;

    id = fork();

    if (id > 0)
    {
        /* This is the parent */
        printf("[PARENT] Parent ID: %d\n", getpid());
        printf("[PARENT] Child ID: %d\n", id);

        sleep(20);
    }
    else if (id == 0)
    {
        /* This is the child */
        printf("[CHILD] ID: %d\n", getpid());
        sleep(10);
    }
    else
    {
        printf("Error on fork()!\n");
    }

    return 0;
}
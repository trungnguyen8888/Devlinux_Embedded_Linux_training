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

        sleep(5);
    }
    else if (id == 0)
    {
        /* This is the child */
        printf("[CHILD] ID: %d\n", getpid());

        for (int32_t i = 0; i < 20; i++)
        {
            sleep(1);
            printf("[PARENT] ID: %d printed in child process!\n", getppid());
        }
    }
    else
    {
        printf("Error on fork()!\n");
    }

    return 0;
}
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

        /* Wait for the child termination */
        if (wait(&status) > (-1))
        {
            if (WIFEXITED(status) != false)
            {
                printf("Status returned by the child %d: %d\n", id, WEXITSTATUS(status));
            }
            else
            {
                printf("Error on WIFEXITED()!\n");
            }
        }
        else
        {
            printf("Error on wait()!\n");
        }
    }
    else if (id == 0)
    {
        /* This is the child */
        printf("[CHILD] ID: %d\n", getpid());
        exit(10);
    }
    else
    {
        printf("Error on fork()!\n");
    }

    return 0;
}
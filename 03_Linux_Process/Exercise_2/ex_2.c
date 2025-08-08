#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/wait.h>

#define OVERWRITTEN (1)

void parent_goes(const pid_t child_id);
void child_goes(const char *set_cmd);

void parent_goes(const pid_t child_id)
{
    int32_t status;

    /* Wait for the child termination */
    if (wait(&status) > (-1))
    {
        if (WIFEXITED(status) != false)
        {
            printf("Status returned by the child %d: %d\n", child_id, WEXITSTATUS(status));
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

void child_goes(const char *set_cmd)
{
    const char *cmd = (const char *)getenv(set_cmd);

    if ((NULL != cmd) && ('\0' != cmd[0]))
    {
        execlp(cmd, cmd, (char *)NULL);

        /*
            This code is executed once execlp() has an error occurence.
            On success, this following code is never executed.
        */
        printf("[ERR] execlp() fails!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("[ERR] %s is not set!\n", set_cmd);
    }
}

int32_t main()
{
    pid_t id;
    int32_t status;
    const char *set_command = "MY_COMMAND";

    /* Set the user-defined environmental variable MY_COMMAND */
    if (setenv(set_command, "ls", OVERWRITTEN) == 0)
    {
        /* Create a new child process */
        id = fork();

        if (id > 0)
        {
            parent_goes((const pid_t)id);
        }
        else if (id == 0)
        {
            child_goes(set_command);
        }
        else
        {
            printf("Failed on fork()!\n");
        }
    }
    else
    {
        printf("Error on setenv()!\n");
    }

    return 0;
}
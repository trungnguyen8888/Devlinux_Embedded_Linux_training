#include <stdint.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>

int32_t main(int32_t argc, char *argv[])
{
    struct stat file_info;

    if (argc > 1)
    {
        memset(&file_info, 0, sizeof(struct stat));

        printf("File path: %s\n", argv[1]);

        if (lstat((const char *)argv[1], &file_info) == 0)
        {
            if (S_ISREG(file_info.st_mode) != 0)
            {
                printf("It's a regular file.\n");
            }
            else if (S_ISDIR(file_info.st_mode) != 0)
            {
                printf("It's a directory.\n");
            }
            else if (S_ISLNK(file_info.st_mode) != 0)
            {
                printf("It's a symbolic link.\n");
            }
            else
            {
                /* Do nothing */
            }

            printf("File size: %ld bytes.\n", (int64_t)file_info.st_size);
            printf("Last modified: %s\n", ctime(&file_info.st_mtime));

        }
        else
        {
            printf("Failed to get file info!\n");
        }
    }
    else
    {
        printf("Usage: ./filestat <file_path>\n");
    }

    return 0;
}
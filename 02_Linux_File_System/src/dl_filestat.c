/*********************************************************************************************
 Start of file
 ********************************************************************************************/
/*********************************************************************************************
 Includes
 ********************************************************************************************/
#include "dl_filestat.h"

/*********************************************************************************************
 Function implementations
 ********************************************************************************************/
/*********************************************************************************************
 * Function         dl_get_file_info
 * Description      Get information about the file.
 * Param(In)        path_name       The file location dispatched by user
 * Retval           err_code        Return error code
                                    DL_ERROR_OK: Normal operation
                                    DL_ERROR_ARG_NULL: path_name is NULL
                                    DL_ERROR_INVALID_PARM: path_name is invalid
                                    DL_ERORR_FAIL: Failure
 ********************************************************************************************/
e_dl_errorcode_t dl_get_file_info(
    const char  *const path_name
)
{
    /* Variable declarations */
    struct stat file_info     = {0};            /*< Struct of file information  */
    e_dl_errorcode_t err_code = DL_ERROR_OK;    /*< Return code                 */

    /* Check parameters */
    if (NULL == path_name)
    {
        perror(path_name);
        err_code = DL_ERROR_ARG_NULL;
    }
    else if (('\0' == *path_name) || (0 == strcmp(path_name, "")))
    {
        perror(path_name);
        err_code = DL_ERROR_INVALID_PARM;
    }
    else if (lstat(path_name, &file_info) == 0)
    {
        /*
         ** [02_01]:
         ** Check if that file is a regular file, a directory or a link
        */
        if (S_ISREG(file_info.st_mode))
        {
            printf("It's a regular file.\n");
        }
        else if (S_ISDIR(file_info.st_mode))
        {
            printf("It's a directory.\n");
        }
        else if (S_ISLNK(file_info.st_mode))
        {
            printf("It's a symbolic link.\n");
        }
        else
        {
            /* Do nothing */
        }
        /*
         ** End of [02_01]
        */

        /* Get the file size and last modification time */
        printf("File size: %ld bytes.\n", (int64_t)file_info.st_size);
        printf("Last modified: %s", ctime(&file_info.st_mtime));
    }
    else
    {
        printf("Failed to get file info!\n");
        err_code = DL_ERORR_FAIL;
    }

	/* Return the result */
    return err_code;
}
/*********************************************************************************************
 End of file
 ********************************************************************************************/
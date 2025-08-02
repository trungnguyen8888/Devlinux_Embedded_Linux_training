/*********************************************************************************************
 Start of file
 ********************************************************************************************/
/*********************************************************************************************
 Includes
 ********************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "dl_strutils.h"

/*********************************************************************************************
 Macro definitions
 ********************************************************************************************/
#define EXPECTED_ERRCODE    "DL_ERROR_OK"

/*********************************************************************************************
 Internal functions
 ********************************************************************************************/
static void verify_result(
    const st_return_info_t *const p_result,
    const char *message,
    ...
);

/*********************************************************************************************
 Function implementations
 ********************************************************************************************/
/*********************************************************************************************
 * Function         verify_result
 * Description      Verify the result of a function.
 * Param(In)        p_result        Pointer to result struct
 * Param(In)        message         Notification to user about the result
 * Param(In)        ...             Input to %d, %s, etc. format in message
 * Retval           None
 ********************************************************************************************/
static void verify_result(
    const st_return_info_t *const p_result,
    const char *message,
    ...
)
{
    /* Declare function's variables */
    va_list arg;

    if ((NULL != p_result) && (NULL != message))
    {
        if (0 == strcmp(EXPECTED_ERRCODE, p_result->errcode))
        {
            /* Success */
            va_start(arg, message);
            vprintf(message, arg);
            va_end(arg);
        }
        else
        {
            /* Mark unused */
            (void)arg;
    
            /* Failure */
            printf("%s err: %s\n", p_result->func_name, p_result->errcode);
        }
    }
    else
    {
        /* Mark unused */
        (void)arg;
    }
}

/*********************************************************************************************
 Main
 ********************************************************************************************/
int32_t main(void)
{
    /* Declare and initialise variables */
    st_return_info_t result = {
        .func_name = "",
        .errcode   = ""
    };
    char str_1[]   = "Evol & Love";
    char str_2[]   = "   Freedom is not free   ";
    char str_3[]   = "8386";
    int32_t number = 0;
    int32_t ret    = EXIT_SUCCESS;

    /* Reverse the string */
    result = dl_str_reverse(str_1);
    verify_result((const st_return_info_t *const)&result, "%s\n", str_1);
    if (0 != strcmp(EXPECTED_ERRCODE, result.errcode))
    {
        ret = EXIT_FAILURE;
    }

    /* Remove leading and trailing whitespaces in a string */
    result = dl_str_trim(str_2);
    verify_result((const st_return_info_t *const)&result, "%s\n", ('\0' == str_2[0]) ? "\\0" : str_2);
    if ((EXIT_SUCCESS == ret) && (0 == strcmp(EXPECTED_ERRCODE, result.errcode)))
    {
        ret = EXIT_FAILURE;
    }

    /* Convert a string to integer */
    result = dl_str_to_int(str_3, &number);
    verify_result((const st_return_info_t *const)&result, "%d\n", number);
    if ((EXIT_SUCCESS == ret) && (0 == strcmp(EXPECTED_ERRCODE, result.errcode)))
    {
        ret = EXIT_FAILURE;
    }

    /* Return the program result */
    return ret;
}
/*********************************************************************************************
 End of file
 ********************************************************************************************/
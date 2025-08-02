/*********************************************************************************************
 Start of file
 ********************************************************************************************/
#ifndef DL_STRUTILS_H
#define DL_STRUTILS_H

/*********************************************************************************************
 Includes
 ********************************************************************************************/
#include <stdint.h>
#include <string.h>

/*********************************************************************************************
 Macro definitions
 ********************************************************************************************/

/*********************************************************************************************
 Global Typedef definitions
 ********************************************************************************************/
typedef struct st_return_info {
    const char  *func_name;     /* Function name        */
    const char  *errcode;       /* Error code in string */
} st_return_info_t;

/*********************************************************************************************
 Function definitions
 ********************************************************************************************/
/*********************************************************************************************
 * Function         dl_str_reverse
 * Description      Reverse a string
 * Param(In-Out)    str       String to be reversed
 * Retval           Struct st_return_info_t that stores result info
 ********************************************************************************************/
st_return_info_t dl_str_reverse(
    char str[]
);

/*********************************************************************************************
 * Function         dl_str_trim
 * Description      Remove leading and trailing whitespaces in a string
 * Param(In-Out)    str       String to be trimmed
 * Retval           Struct st_return_info_t that stores result info
 ********************************************************************************************/
st_return_info_t dl_str_trim(
    char str[]
);

/*********************************************************************************************
 * Function         dl_str_to_int
 * Description      Convert a string to integer
 * Param(In)        str       String to be convert to integer
 * Param(Out)       p_number  Pointer to the memory that stores output number after converted
 * Retval           Struct st_return_info_t that stores result info
 ********************************************************************************************/
st_return_info_t dl_str_to_int(
    const char  str[],
    int32_t     *p_number
);

#endif  /* DL_STRUTILS_H */
/*********************************************************************************************
 End of file
 ********************************************************************************************/
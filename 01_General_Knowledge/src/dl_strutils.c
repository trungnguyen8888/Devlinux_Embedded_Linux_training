/*********************************************************************************************
 Start of file
 ********************************************************************************************/
/*********************************************************************************************
 Includes
 ********************************************************************************************/
#include "dl_strutils.h"

/*********************************************************************************************
 Macro definitions
 ********************************************************************************************/
#define STRINGIFY(x)    #x

/*********************************************************************************************
 Internal datatypes
 ********************************************************************************************/
typedef enum e_dl_errorcode {
    DL_ERROR_OK             = 0,        /*< Successful operation            */
    DL_ERROR_ARG_NULL       = (-1),     /*< Function's parameter is NULL    */
    DL_ERROR_INVALID_PARM   = (-2)      /*< Function's parameter is invalid */
} e_dl_errorcode_t;

/*********************************************************************************************
 Internal functions
 ********************************************************************************************/
static const char *dl_stringify_errorcode(
    const e_dl_errorcode_t err_code
);

static int32_t dl_power(
    const int32_t base,
    const int32_t exponent
);

static int32_t dl_integerise_character(
    const char character
);

/*********************************************************************************************
 Function implementations
 ********************************************************************************************/
/*********************************************************************************************
 * Function         dl_stringify_errorcode
 * Description      Stringify an error code.
                    If the error code is invalid, this function returns ""
 * Param(In)        err_code        Error code that needs stringifying
 * Retval           Stringified error code. For example, "DL_ERROR_OK"
 ********************************************************************************************/
static const char *dl_stringify_errorcode(
    const e_dl_errorcode_t err_code
)
{
    const char *err_code_string;

    switch (err_code)
    {
        case DL_ERROR_OK:           err_code_string = STRINGIFY(DL_ERROR_OK); break;
        case DL_ERROR_ARG_NULL:     err_code_string = STRINGIFY(DL_ERROR_ARG_NULL); break;
        case DL_ERROR_INVALID_PARM: err_code_string = STRINGIFY(DL_ERROR_INVALID_PARM); break;
        default:                    err_code_string = ""; break;
    }

    return err_code_string;
}

/*********************************************************************************************
 * Function         dl_integerise_character
 * Description      Convert a charactor to an integer. For example, "1" -> 1
                    Only "0" -> "9" If the error code is invalid, this function returns ""
 * Param(In)        character       Character that needs converting. Only valid '0' -> '9'.
 * Retval           Integer number converted from character
 ********************************************************************************************/
static int32_t dl_integerise_character(
    const char character
)
{
    return (int32_t)(character - '0');
}

/*********************************************************************************************
 * Function         dl_power
 * Description      Calculate the power of a number.
 * Param(In)        base            The base
 * Param(In)        exponent        The exponent
 * Retval           Result of base to the power of exponent
 ********************************************************************************************/
static int32_t dl_power(
    const int32_t base,
    const int32_t exponent
)
{
    int32_t i;
    int32_t result;

    for (i = 0, result = 1; i < exponent; i++)
    {
        result = result * base;
    }

    return result;
}

/*********************************************************************************************
 * Function         dl_str_reverse
 * Description      Reverse a string
 * Param(In-Out)    str       String to be reversed
 * Retval           Struct st_return_info_t that stores result info
 ********************************************************************************************/
st_return_info_t dl_str_reverse(
    char str[]
)
{
    int32_t i;
    int32_t j;
    size_t  len;
    char    tmp;
    e_dl_errorcode_t err_code = DL_ERROR_OK;
    st_return_info_t   result;

    if (NULL == str)
    {
        err_code = DL_ERROR_ARG_NULL;
    }
    else if ('\0' == str[0])
    {
        err_code = DL_ERROR_INVALID_PARM;
    }
    else
    {
        len = strlen(str);

        /*
         ** Reverse the string in place by swapping characters from both ends.
         ** This loops from the outside in until all characters are swapped.
         */
        for (i = 0, j = (int32_t)(len - 1U); i < j; i++, j--)
        {
            tmp = str[i];
            str[i] = str[j];
            str[j] = tmp;
        }
    }

    /* Retrieve the result */
    result.func_name = __func__;
    result.errcode   = dl_stringify_errorcode(err_code);

    return result;
}

/*********************************************************************************************
 * Function         dl_str_trim
 * Description      Remove leading and trailing whitespaces in a string
 * Param(In-Out)    str       String to be trimmed
 * Retval           Struct st_return_info_t that stores result info
 ********************************************************************************************/
st_return_info_t dl_str_trim(
    char str[]
)
{
    int32_t start;
    int32_t end;
    int32_t i;
    e_dl_errorcode_t err_code = DL_ERROR_OK;
    st_return_info_t   result;

    if (NULL == str)
    {
        err_code = DL_ERROR_ARG_NULL;
    }
    else if ('\0' == str[0])
    {
        err_code = DL_ERROR_INVALID_PARM;
    }
    else
    {
        /* Initialize variables */
        start = 0;
        end   = (int32_t)strlen(str) - 1;
    
        /* Move start to the 1st non-whitespace character */
        while ((start < end) && (' ' == str[start]))
        {
            start++;
        }
    
        /* Move end to the last non-whitespace character */
        while ((end > start) && (' ' == str[end]))
        {
            end--;
        }
    
        if (' ' == str[start])
        {
            /*
             ** This case is when the string has whitespaces only,
             ** so remove all whitespaces
             */
            str[0] = '\0';
        }
        else
        {
            /*
             ** When the string has at least one non-whitespace character,
             ** we move the characters to the beginning of the string.
             */
            for (i = 0; i <= (end - start); i++)
            {
                str[i] = str[start + i];
            }
        
            str[i] = '\0';
        }
    }

    /* Retrieve the result */
    result.func_name = __func__;
    result.errcode   = dl_stringify_errorcode(err_code);

    return result;
}

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
)
{
    int32_t start;
    int32_t i;
    int32_t number;
    int32_t gap;
    int32_t len;
    e_dl_errorcode_t err_code = DL_ERROR_OK;
    st_return_info_t result;

    if ((NULL == str) || (NULL == p_number))
    {
        err_code = DL_ERROR_ARG_NULL;
    }
    else if ('\0' == str[0])
    {
        err_code = DL_ERROR_INVALID_PARM;
    }
    else
    {
        len = (int32_t)strlen(str);

        /*
         ** Check if the string is a negative or positive number.
         ** If negative, ignore the minus mark (-)
         */
        i = ('-' == str[0]) ? 1 : 0;

        /*
         ** Verify if there is a non-digit characer in the string.
         ** The string must not contain a non-digit character.
         */
        while (i < len)
        {
            if ((str[i] < '0') || ('9' < str[i]))
            {
                err_code = DL_ERROR_INVALID_PARM;
                break;
            }

            i++;
        }
    }

    if (DL_ERROR_OK == err_code)
    {
        /* Inititalize variables */
        start = ('-' == str[0]) ? 1 : 0;    /**< Ignore the minus mark (-) if negative number */
        number = 0;

        /* Integrise the string from the most significant digit */
        while (start < len)
        {
            gap = len - start;
            number += (dl_integerise_character((const char)str[start]) * dl_power(10, (gap - 1)));
            start++;
        }

        /* Negative number */
        if ('-' == str[0])
        {
            number *= (-1);
        }

        /* Retrieve the result */
        *p_number = number;
    }

    /* Retrieve the result */
    result.func_name = __func__;
    result.errcode   = dl_stringify_errorcode(err_code);

    return result;
}
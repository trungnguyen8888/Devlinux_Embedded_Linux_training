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
#define STRINGIFY(x)        #x
#define IS_SPACE_OR_TAB(c)  ((' ' == c) || ('\t' == c))

/*********************************************************************************************
 Internal datatypes
 ********************************************************************************************/
typedef enum e_dl_errorcode {
    DL_ERROR_OK           = 0,      /*< Successful operation            */
    DL_ERROR_ARG_NULL     = (-1),   /*< Function's parameter is NULL    */
    DL_ERROR_INVALID_PARM = (-2)    /*< Function's parameter is invalid */
} e_dl_errorcode_t;

/*********************************************************************************************
 Internal functions
 ********************************************************************************************/
static const char *dl_stringify_errorcode(
    const e_dl_errorcode_t err_code
);

static int32_t dl_power(
    int32_t base,
    int64_t exponent
);

static inline int32_t dl_integerise_character(
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
    /* Variable declarations */
    const char *err_code_string;    /**< Error code in text */

    /* Stringify error code */
    switch (err_code)
    {
        case DL_ERROR_OK:           err_code_string = STRINGIFY(DL_ERROR_OK); break;
        case DL_ERROR_ARG_NULL:     err_code_string = STRINGIFY(DL_ERROR_ARG_NULL); break;
        case DL_ERROR_INVALID_PARM: err_code_string = STRINGIFY(DL_ERROR_INVALID_PARM); break;
        default:                    err_code_string = ""; break;
    }

    /* Return the stringified error code */
    return err_code_string;
}

/*********************************************************************************************
 * Function         dl_integerise_character
 * Description      Convert a character to an integer. For example, "1" -> 1
                    Only "0" -> "9" If the error code is invalid, this function returns ""
 * Param(In)        character       Character that needs converting. Only valid '0' -> '9'.
 * Retval           Integer number converted from character
 ********************************************************************************************/
static inline int32_t dl_integerise_character(
    const char character
)
{
    /* Return the integerised number */
    return (int32_t)(character - '0');
}

/*********************************************************************************************
 * Function         dl_power
 * Description      Perform exponentiation: calculate base raised to the power of exponent.
 *                  This implementation uses fast exponentiation (binary exponentiation by
 *                  squaring), which reduces the complexity from O(exponent) to O(log exponent).
 * Param(In)        base        The base number
 * Param(In)        exponent    The exponent (must be non-negative)
 * Retval           The result of base^exponent
 ********************************************************************************************/

static int32_t dl_power(
    int32_t base,
    int64_t exponent
)
{
    /* Variable declarations */
    int32_t result;

    /* Initialise variables */
    result = 1;

    /*
     ** [01_01]:
     ** Idea:
     ** - Every integer exponent can be written in binary.
     ** - Only the bits set to 1 contribute to the final result.
     ** - Each loop:
     **     + If (exponent & 1): multiply result by the current base.
     **     + Square the base (base *= base).
     **     + Shift exponent right (exponent >>= 1).
     **
     ** Example: base = 8, exponent = 5 (binary 101₂)
     **         -> 8^5 = 8^(2^2) * 8^(2^0) = 4096 * 8 = 32768
     **
     ** Example: base = 8, exponent = 6 (binary 110₂)
     **         -> 8^6 = 8^(2^2) * 8^(2^1) = 4096 * 64 = 262144
     */
    while (0 < exponent)
    {
        if ((exponent & 1) == 1)
        {
            /* Current bit of exponent is 1 → multiply this base into result */
            result = result * base;
        }

        /*
         ** Move to the next bit:
         ** - Square the base for the next power of two
         ** - Shift exponent right to process its next bit
         */
        base = base * base;
        exponent >>= 1;
    }
    /*
     ** End of [01_01]
     */

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
    /* Variable declarations */
    e_dl_errorcode_t err_code = DL_ERROR_OK;    /**< Error code          */
    st_return_info_t result;                    /**< Result sent to user */

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
        /* Variable declarations */
        size_t i;
        size_t j;
        const size_t len = strlen(str); /**< The length of the string */

        /*
         ** [01_02]:
         ** Reverse the string in place by swapping characters from both ends.
         ** This loops from the outside in until all characters are swapped.
         */
        for (i = 0, j = len - 1; i < j; i++, j--)
        {
            char tmp = str[i];
            str[i]   = str[j];
            str[j]   = tmp;
        }
        /*
         ** End of [01_02]
         */
    }

    /* Retrieve the result */
    result.func_name = __func__;
    result.errcode   = dl_stringify_errorcode(err_code);

    /* Return the result */
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
    /* Variable declarations */
    e_dl_errorcode_t err_code = DL_ERROR_OK;    /**< Error code          */
    st_return_info_t result;                    /**< Result sent to user */

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
        /* Variable declarations */
        size_t start;                   /**< Index of the first non-space-or-tab character (in the original string) */
        const size_t len = strlen(str); /**< Length of the string before trimmed                                    */

        /* Initialise variables */
        start = 0;
    
        /* Locate the 1st non-space-or-tab character */
        while ((start < len) && IS_SPACE_OR_TAB(str[start]))
        {
            start++;
        }

        if (start == len)
        {
            /* String contains only spaces/tabs --> Empty it! */
            str[0] = '\0';
        }
        else
        {
            /* Variable declarations */
            size_t end = len - 1; /**< Index of the last non-space-or-tab character (in the original string) */
            
            /* Locate the last non-space-or-tab character */
            while ((end > start) && IS_SPACE_OR_TAB(str[end]))
            {
                end--;
            }
    
            /*
             ** [01_03]:
             ** When the string has at least one non-space-or-tab character,
             ** shift the middle segment to the beginning (overlap-safe)
             */
            size_t out_len = end - start + 1;
            (void)memmove(str, &str[start], out_len);       
            str[out_len] = '\0';
            /*
             ** End of [01_03]
            */
        }
    }

    /* Retrieve the result */
    result.func_name = __func__;
    result.errcode   = dl_stringify_errorcode(err_code);

    /* Return the result */
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
    /* Variable declarations */
    size_t len;                                 /**< The length of the string */
    e_dl_errorcode_t err_code = DL_ERROR_OK;    /**< Error code          */
    st_return_info_t result;                    /**< Result sent to user */

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
        /* Variable declarations */
        size_t idx;     /**< The position in the string */

        /*
         ** Check if the string is a negative or positive number.
         ** If negative, ignore the minus mark (-)
         */
        idx = ('-' == str[0]) ? 1 : 0;

        /*
         ** [01_04]:
         ** Verify if there is a non-digit character in the string.
         ** The string must not contain a non-digit character.
         */
        len = strlen(str);
        while (idx < len)
        {
            if ((str[idx] < '0') || ('9' < str[idx]))
            {
                err_code = DL_ERROR_INVALID_PARM;
                break;
            }

            idx++;
        }
        /*
         ** End of [01_04]
         */
    }

    if (DL_ERROR_OK == err_code)
    {
        /* Variable declarations */
        size_t  start;      /**< The position of the 1st number in the string */
        int32_t number;     /**< Parsed integer result                        */
        size_t  gap;        /**< The length from start position               */

        /* Initialise variables */
        start = ('-' == str[0]) ? 1 : 0;    /**< Ignore the minus mark (-) if negative number */
        number = 0;

        /* Integerise the string from the most significant digit */
        while (start < len)
        {
            gap = len - start;
            number += (dl_integerise_character((const char)str[start]) * dl_power(10, (int64_t)(gap - 1)));
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

    /* Return the result */
    return result;
}
/*********************************************************************************************
 End of file
 ********************************************************************************************/
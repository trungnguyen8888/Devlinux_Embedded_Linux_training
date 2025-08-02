#include "strutils.h"

#define STRINGIFY(x)    #x

enum e_errcode_return {
    SUCCESS         = 0,
    ARG_NULL        = (-1),
    INVALID_PARM    = (-2)
};

typedef enum e_errcode_return   e_errcode_return_t;

static char *convert_errcode(const e_errcode_return_t err_code);
static int32_t power(const int32_t base, const int32_t exponent);
static int32_t integerise_character(const char character);

static char *convert_errcode(const e_errcode_return_t err_code)
{
    char *err_code_string;

    switch (err_code)
    {
        case SUCCESS:       err_code_string = STRINGIFY(SUCCESS); break;
        case ARG_NULL:      err_code_string = STRINGIFY(ARG_NULL); break;
        case INVALID_PARM:  err_code_string = STRINGIFY(INVALID_PARM); break;
        default:            err_code_string = NULL; break;
    }

    return err_code_string;
}

static int32_t integerise_character(const char character)
{
    return (int32_t)(character - '0');
}

static int32_t power(const int32_t base, const int32_t exponent)
{
    int32_t i;
    int32_t result;

    for (i = 0, result = 1; i < exponent; i++)
    {
        result = result * base;
    }

    return result;
}

st_return_info_t str_reverse(char str[])
{
    int32_t i;
    int32_t j;
    size_t  len;
    char    tmp;
    e_errcode_return_t err_code = SUCCESS;
    st_return_info_t   result;

    if (NULL == str)
    {
        err_code = ARG_NULL;
    }
    else if ('\0' == str[0])
    {
        err_code = INVALID_PARM;
    }
    else
    {
        len = strlen(str);

        for (i = 0, j = (int32_t)(len - 1U); i < j; i++, j--)
        {
            tmp = str[i];
            str[i] = str[j];
            str[j] = tmp;
        }
    }

    /* Prepare the result information */
    result.func_name = (char *)__func__;
    result.errcode   = convert_errcode(err_code);

    return result;
}

st_return_info_t str_trim(char str[])
{
    int32_t start;
    int32_t end;
    int32_t i;
    e_errcode_return_t err_code = SUCCESS;
    st_return_info_t   result;

    if (NULL == str)
    {
        err_code = ARG_NULL;
    }
    else if ('\0' == str[0])
    {
        err_code = INVALID_PARM;
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
    
        if (' ' == str[start])      /**< This case is when the string has whitespaces only */
        {
            /* Remove all whitespaces */
            str[0] = '\0';
        }
        else        /* When the string has at least one non-whitespace character */
        {
            for (i = 0; i <= (end - start); i++)
            {
                str[i] = str[start + i];
            }
        
            str[i] = '\0';
        }
    }

    /* Prepare the result information */
    result.func_name = (char *)__func__;
    result.errcode   = convert_errcode(err_code);

    return result;
}

st_return_info_t str_to_int(const char str[], int32_t *p_number)
{
    int32_t start;
    // int32_t end;
    int32_t i;
    int32_t number;
    int32_t gap;
    int32_t len;
    e_errcode_return_t err_code = SUCCESS;
    st_return_info_t   result;

    if (NULL == str)
    {
        err_code = ARG_NULL;
    }
    else if ('\0' == str[0])
    {
        err_code = INVALID_PARM;
    }
    else
    {
        len = (int32_t)strlen(str);

        i = ('-' == str[0]) ? 1 : 0;

        while (i < len)
        {
            if ((str[i] < '0') || ('9' < str[i]))
            {
                err_code = INVALID_PARM;
                break;
            }

            i++;
        }
    }

    if (SUCCESS == err_code)
    {
        /* Inititalize variables */
        start = ('-' == str[0]) ? 1 : 0;
        number = 0;

        // for (; start < len; start++)
        while (start < len)
        {
            gap = len - start;
            number += (integerise_character((const char)str[start]) * power(10, (gap - 1)));
            start++;
        }

        /* Negative number */
        if ('-' == str[0])
        {
            number *= (-1);
        }

        *p_number = number;
    }

    /* Prepare the result information */
    result.func_name = (char *)__func__;
    result.errcode   = convert_errcode(err_code);

    return result;
}
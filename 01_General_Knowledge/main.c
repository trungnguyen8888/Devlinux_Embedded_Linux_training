#include "strutils.h"
#include <stdio.h>

int32_t main()
{
    st_return_info_t result;

    char str_1[] = "Evol & Love";
    char str_2[] = "   Freedom is not free   ";
    char str_3[] = "8386";
    int32_t number;

    result = str_reverse(str_1);
    if (0 == strcmp("SUCCESS", result.errcode))
    {
        printf("%s\n", str_1);
    }
    else
    {
        printf("%s err: %s\n", result.func_name, result.errcode);
    }

    result = str_trim(str_2);
    if (0 == strcmp("SUCCESS", result.errcode))
    {
        printf("%s\n", ('\0' == str_2[0]) ? "\\0" : str_2);
    }
    else
    {
        printf("%s err: %s\n", result.func_name, result.errcode);
    }

    number = 0;
    result = str_to_int(str_3, &number);
    if (0 == strcmp("SUCCESS", result.errcode))
    {
        printf("%d\n", number);
    }
    else
    {
        printf("%s err: %s\n", result.func_name, result.errcode);
    }

    return 0;
}
#include <stdint.h>
#include <string.h>

struct st_return_info {
    char *func_name;
    char *errcode;
};

typedef struct st_return_info   st_return_info_t;

st_return_info_t str_reverse(char str[]);

st_return_info_t str_trim(char str[]);

st_return_info_t str_to_int(const char str[], int32_t *p_number);
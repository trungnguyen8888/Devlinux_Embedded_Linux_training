/*********************************************************************************************
 Start of file
 ********************************************************************************************/
/*********************************************************************************************
 Includes
 ********************************************************************************************/
#include <stdlib.h>
#include "dl_filestat.h"

/*********************************************************************************************
 Main
 ********************************************************************************************/
int32_t main(int32_t argc, char *argv[])
{
	/* Declare and initialise variables */
	int32_t ret = EXIT_SUCCESS;

    if (argc > 1)
    {
		/* Get information about the file */
		e_dl_errorcode_t api_ret = dl_get_file_info((const char *)argv[1]);
		if (DL_ERROR_OK != api_ret)
		{
			printf("Failed! Error <%d>\n", api_ret);
			ret = EXIT_FAILURE;
		}
		else
		{
			/* Do nothing */
		}
    }
    else
    {
		/* Invalid command */
        printf("Usage: ./filestat <file_path>\n");
		ret = EXIT_FAILURE;
    }

	/* Return the program result */
    return ret;
}
/*********************************************************************************************
 End of file
 ********************************************************************************************/
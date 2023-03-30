#include <stdio.h>
#include "err.h"

int print_status(io_status sts, const char* info)
{
	if (info == nullptr)
		info = "";
    switch(sts)
    {
    	case io_status::success:
    		break;
    	case io_status::open:
            printf("Error: Open problem in file %s\n", info);
    		break;
    	case io_status::eof:
            printf("Error: End of file %s\n", info);
    		break;
    	case io_status::format:
            printf("Error: Format problem in file %s\n", info);
    		break;
    	case io_status::memory:
            printf("Error: Memory problem %s\n", info);
    		break;
        case io_status::slash_end:
            printf("Error: Slash at the end %s\n", info);
            break;
        case io_status::wrong_code:
            printf("Error: Invalid code %s\n", info);
            break;
        default:
            printf("Unknown error %d. %s\n", (int)sts, info);
            break;
    }
    return (int)sts;
}

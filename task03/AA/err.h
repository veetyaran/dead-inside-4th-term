#ifndef _ERR_H_
#define _ERR_H_

enum class io_status
{
	success,
	eof,
	format,
	memory,
	open,
    slash_end,
    wrong_code,
    write,
    read,
};

int print_status(io_status sts, const char* info = nullptr);

#endif //_ERR_H_

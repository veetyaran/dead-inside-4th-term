#include <stdlib.h>
#include <time.h>
#include <stdio.h>


#include "coder.h"
#include "parse.h"
#include "list.h"
#include "err.h"



bool good_string(char* str, parse prs, list<coder>& list)
{
	char* next = str;
    list_node<coder>* curr = list.begin();

    for (std::unique_ptr<char[]> word = prs.get_word(next); word && curr; word = prs.get_word(next), curr = curr->next)
	{
//        printf("%s\n", word.get());
        if (curr->apply(word.get()) != GOOD)
            return false;
	}
    return true;
}


io_status parse_string(char* str, parse prs, list<coder>& list)
{
    char* next = str;

    for (std::unique_ptr<char[]> word = prs.get_word(next); word; word = prs.get_word(next))
    {
        io_status sts;
        coder codeword;

        sts = codeword.parse(word.get());
        if (sts != io_status::success)
            return sts;

        sts = list.add_value(codeword);
        if(sts != io_status::success)
            return sts;
    }

    list.reverse();

    return io_status::success;
}


#define BUFLEN 1234
io_status process_file(FILE* in, FILE* out, parse prs, list<coder>& list, int& result)
{
	char buffer[BUFLEN];
	while (fgets(buffer, BUFLEN, in))
	{
        if (good_string(buffer, prs, list))
		{
			if (fputs(buffer, out) == EOF)
				return io_status::write;
			result++;
		}
	}
    return ferror(in) ? io_status::read : io_status::success;
}

io_status solve(FILE* in, FILE* out, char* s, char* t, int& result)
{
	io_status sts = io_status::success;

	parse prs(t);
    list<coder> list;
    sts = parse_string(s, prs, list);
	if (sts != io_status::success) return sts;

    sts = process_file(in, out, prs, list, result);
	return sts;
}

int main(int argc, char *argv[])
{
    int task = 2;
	int result = 0;

	char* s = nullptr;
	char* t = nullptr;
	char *in_name = nullptr;
	char *out_name = nullptr;
	FILE* in_file = nullptr;
	FILE* out_file = nullptr;

	int iArg = 1;

	if (!(1
		&& argc>iArg && (in_name = argv[iArg++])
		&& argc>iArg && (out_name = argv[iArg++])
		&& argc>iArg && (s = argv[iArg++])
		&& argc>iArg && (t = argv[iArg++])
		&& argc == iArg))
	{
        printf("Usage: %s fin fout s t\n", argv[0]);
		return -1;
	}

	if (!(in_file = fopen(in_name, "r"))) {
		return print_status(io_status::open, in_name);
	}
	if (!(out_file = fopen(out_name, "w"))) {
		fclose(in_file);
		return print_status(io_status::open, out_name);
	}

	double time = clock();
    io_status status = solve(in_file, out_file, s, t, result);
	time = (clock() - time) / CLOCKS_PER_SEC;

	if (status == io_status::success)
        printf("%s : Task = %d Result = %d Elapsed = %.2f\n",
			argv[0], task, result, time);
	else
		print_status(status);

	fclose(in_file);
	fclose(out_file);
	return (int)status;
}

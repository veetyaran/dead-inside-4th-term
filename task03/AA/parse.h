#ifndef _PARSE_H_
#define _PARSE_H_

#include <memory>
#include <string.h>
#include <stdio.h>


#define ABC_BITS sizeof(int)
#define ABC_LEN (256/ABC_BITS)

std::unique_ptr<char[]> make_string(const char * buff, size_t len);
std::unique_ptr<char[]> make_string(const char * str);

class parse
{
private:
	unsigned int token[ABC_LEN];
	unsigned int delim[ABC_LEN];
public:
	parse(const char* s_delim)
	{
		set_abc(delim, s_delim);
		add_abc(delim, "\n\r");
		set_abc(token, s_delim);
		add_abc(token, "\n\r");
		invert_abc(token);
	}
	~parse() = default;
	std::unique_ptr<char[]> get_fragment(char*& curr, bool& word);
	std::unique_ptr<char[]> get_word(char*& curr);
private:
	void to_abc(unsigned int abc[ABC_LEN], unsigned char ch);
	int from_abc(const unsigned int abc[ABC_LEN], unsigned char ch);
	void set_abc(unsigned int abc[ABC_LEN], const char* str);
	void add_abc(unsigned int abc[ABC_LEN], const char* str);
	void invert_abc(unsigned int abc[ABC_LEN]);
	size_t find_abc(const unsigned int abc[ABC_LEN], const char* str);
};

#endif //_PARSE_H_

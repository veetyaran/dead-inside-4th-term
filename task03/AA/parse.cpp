#include <stdlib.h>
#include "parse.h"

#define ABC_BITS sizeof(int)
#define ABC_LEN (256/ABC_BITS)

void parse::to_abc(unsigned int abc[ABC_LEN], unsigned char ch)
{
    int i;
    for (i = 0; ; i++, ch -= ABC_BITS)
    {
        if (ch < ABC_BITS)
        {
            abc[i] |= 1 << ch;
            break;
        }
    }
}

int parse::from_abc(const unsigned int abc[ABC_LEN], unsigned char ch)
{
    int i;
    for (i = 0; ; i++, ch -= ABC_BITS)
    {
        if (ch < ABC_BITS)
            return abc[i] & (1 << ch);
    }
    return 0;
}

void parse::set_abc(unsigned int abc[ABC_LEN], const char* str)
{
    size_t i;
	for (i = 0; i < ABC_LEN; i++) abc[i] = 0;
	for (; *str; str++) to_abc(abc, (unsigned char)(*str));
}

void parse::add_abc(unsigned int abc[ABC_LEN], const char* str)
{
	for (; *str; str++) to_abc(abc, (unsigned char)(*str));
}

void parse::invert_abc(unsigned int abc[ABC_LEN])
{
    size_t i;
    for (i=0; i < ABC_LEN; i++)
        abc[i] = ~abc[i];
}

size_t parse::find_abc(const unsigned int abc[ABC_LEN], const char* str)
{
    size_t i;
    for (i = 0; str[i]; i++) 
    {
        if (from_abc(abc, (unsigned char)(str[i]))) break;
    }
    return i;
}

std::unique_ptr<char[]> parse::get_word(char*& next)
{
	if (next == nullptr)
		return nullptr;
	size_t index;
	char* tok = 0;
	char* curr = next;
	next = nullptr;

	index = find_abc(token, curr);
	if (curr[index])
	{
		tok = curr + index;
        curr = tok + 1;
		index = find_abc(delim, curr);
		if (curr[index])
			next = curr + index + 1;
		return make_string(tok, index + 1);
	}
	return nullptr;
}

std::unique_ptr<char[]> parse::get_fragment(char*& next, bool& word)
{
	if (next == nullptr)
		return nullptr;
	if (next[0] == 0)
	{
		next = nullptr;
		return nullptr;
	}
	size_t index;
	char* curr = next;
	next = nullptr;

	word = (bool)from_abc(token, curr[0]);
	if (word)
		index = find_abc(delim, curr + 1) + 1;
	else
		index = find_abc(token, curr + 1) + 1;
	if (curr[index])
		next = curr + index + 1;
	return make_string(curr, index + 1);
}

std::unique_ptr<char[]> make_string(const char * buff, size_t len)
{
    if (buff == nullptr) return nullptr;
    std::unique_ptr<char[]> str = std::make_unique<char[]>(len + 1);
    if (str == nullptr) return nullptr;
    char* s = str.get();
    size_t i;
    for (i = 0; i < len; i++)
        s[i] = buff[i];
    s[i] = 0;
    return str;
}

std::unique_ptr<char[]> make_string(const char * str)
{
    if (str == nullptr) return nullptr;
    size_t len = strlen(str);
    return make_string(str, len);
}


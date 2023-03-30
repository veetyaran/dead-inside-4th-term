#ifndef _CODE_H_
#define _CODE_H_

#include <memory>
#include <string.h>
#include <stdio.h>

#include "err.h"

enum {
    GOOD = 0,
    BAD = 1,
    UNKNOWN = -100,
};

class coder
{
private:
    std::unique_ptr<char[]> scode;
    std::unique_ptr<char[]> spec;
    std::unique_ptr<unsigned char[]> arg1;
    std::unique_ptr<unsigned char[]> arg2;
public:
    coder() = default;
    coder(const coder&) = delete;
    coder(coder&& x) = default;
    ~coder() = default;

    io_status parse(char* str);
    int apply(char* word);

    io_status parse1(char* str);
    int apply1(char* word);


    io_status parse2(char* str);
    io_status parse2_(char* str);
    int apply2(char* word);
private:



    enum {
        CODE_NONE = 1,
        CODE_ONE = '_',
        CODE_MUL = '%',
        CODE_RANGE = '[',
        CODE_URANGE = '^',
    };
};

#endif // _LIST_H_

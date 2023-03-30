#include "coder.h"

io_status coder::parse(char* _str)
{
    size_t len = strlen(_str);

    scode = std::make_unique<char[]>(len+1);
    spec = std::make_unique<char[]>(len+1);

    char* str = _str;

    for(size_t i = 0; *str; str++, i++)
    {
        switch(*str)
        {
        case '\\':
            if (*(++str) == '\0')
                return io_status::slash_end;
            scode[i] = *str;
            spec[i] = CODE_NONE;
            break;
        case '_':
            scode[i] = '0';
            spec[i] = CODE_ONE;
            break;
        default:
            scode[i] = *str;
            spec[i] = CODE_NONE;
            break;
        }

    }

//    printf("%s\n", scode.get());
//    printf("%s\n", spec.get());
//    printf("\n");


    return io_status::success;
}
int coder::apply(char* pword)
{
    size_t i = 0;
    char* word = pword;
    for(; *word && spec[i]; word++, i++)
    {
        switch (spec[i])
        {
        case CODE_NONE:
            if (scode[i] != *word)
                return BAD;
            break;
        case CODE_ONE:
            break;
        default:
            return UNKNOWN;
        }
    }
    if (*word != '\0' || spec[i] != '\0')
        return BAD;
    return GOOD;
}

//io_status coder::parse1(char* _str)
//{

//    size_t len = strlen(_str);

//    scode = std::make_unique<char[]>(len+1);
//    spec = std::make_unique<char[]>(len+1);

//    char* str = _str;

//    size_t i = 0;
//    for(; *str; str++, i++)
//    {
//        switch(*str)
//        {
//        case '\\':
//            if (*(++str) == '\0')
//                return io_status::slash_end;
//            scode[i] = *str;
//            spec[i] = CODE_NONE;

//            break;
//        case '%':
//            if (*(str+1) == '%') {
//                i--;
//                break;
//            }
//            scode[i] = '0';
//            spec[i] = CODE_MUL;
//            break;
//        default:
//            scode[i] = *str;
//            spec[i] = CODE_NONE;
//            break;
//        }

//    }

//    scode[i] = '\0';
//    spec[i] = '\0';

//    printf("%s\n", scode.get());
//    printf("%s\n", spec.get());
//    printf("\n");


//    return io_status::success;
//}

//int coder::apply1(char *pword)
//{
//    char* word = pword;
//    size_t i = 0;

//    for(; *word; word++, i++)
//    {
//        switch(spec[i])
//        {
//        case CODE_NONE:
//            if (scode[i] != *word)
//                return BAD;
//            break;
//        case CODE_MUL:
//            if (scode[i+1] == '\0')
//                return GOOD;
//            char* _word = nullptr;
//            if ((_word = strstr(scode+i+1, word)) != nullptr)
//            {
//                word = _word;
//                break;
//            }
//            else
//            {
//                return BAD;
//            }

//        }
//    }
//}

io_status coder::parse2(char* _str)
{
    size_t len = strlen(_str);

    scode = std::make_unique<char[]>(len+1);
    spec = std::make_unique<char[]>(len+1);
    arg1 = std::make_unique<unsigned char[]>(len+1);
    arg2 = std::make_unique<unsigned char[]>(len+1);

    char* str = _str;
    for(size_t i = 0; *str; str++, i++)
    {
        switch(*str)
        {
        case '\\':
            if (*(++str) == '\0')
                return io_status::slash_end;
            scode[i] = *str;
            spec[i] = arg1[i] = arg2[i] = CODE_NONE;
            break;
        case '[':
            scode[i] = '0';
            spec[i] = CODE_RANGE;

            if (*(++str) == '\0')
                return io_status::wrong_code;

            arg1[i] = *str;

            if (*(++str) != '-')
                return io_status::wrong_code;
            if (*(++str) == '\0')
                return io_status::wrong_code;

            arg2[i] = *str;

            if (*(++str) != ']')
                return io_status::wrong_code;
            if (arg1[i] > arg2[i])
                return io_status::wrong_code;
            break;
        case ']':
            return io_status::wrong_code;
        default:
            scode[i] = *str;
            spec[i] = arg1[i] = arg2[i] = CODE_NONE;
            break;
        }
    }

//    printf("%s\n", scode.get());
//    printf("%s\n", spec.get());
//    printf("%s\n", arg1.get());
//    printf("%s\n", arg2.get());
//    printf("\n");


    return io_status::success;

}

io_status coder::parse2_(char* _str)
{
    size_t len = strlen(_str);

    scode = std::make_unique<char[]>(len+1);
    spec = std::make_unique<char[]>(len+1);
    arg1 = std::make_unique<unsigned char[]>(len+1);
    arg2 = std::make_unique<unsigned char[]>(len+1);

    char* str = _str;
    for(size_t i = 0; *str; str++, i++)
    {
        switch(*str)
        {
        case '\\':
            if (*(++str) == '\0')
                return io_status::slash_end;
            scode[i] = *str;
            spec[i] = arg1[i] = arg2[i] = CODE_NONE;
            break;
        case '[':
            if (*(++str) != '^')
                return io_status::wrong_code;
            scode[i] = '0';
            spec[i] = CODE_URANGE;

            if (*(++str) == '\0')
                return io_status::wrong_code;

            arg1[i] = *str;

            if (*(++str) != '-')
                return io_status::wrong_code;
            if (*(++str) == '\0')
                return io_status::wrong_code;

            arg2[i] = *str;

            if (*(++str) != ']')
                return io_status::wrong_code;
            if (arg1[i] > arg2[i])
                return io_status::wrong_code;
            break;
        case ']':
            return io_status::wrong_code;
        case '^':
            return io_status::wrong_code;

        default:
            scode[i] = *str;
            spec[i] = arg1[i] = arg2[i] = CODE_NONE;
            break;
        }
    }

//    printf("%s\n", scode.get());
//    printf("%s\n", spec.get());
//    printf("%s\n", arg1.get());
//    printf("%s\n", arg2.get());
//    printf("\n");

    return io_status::success;

}

int coder::apply2(char* pword)
{
    char* word = pword;
    size_t i = 0;

    for(; *word && spec[i]; word++, i++)
    {
        switch(spec[i])
        {
        case CODE_NONE:
            if (scode[i] != *word)
                return BAD;
            break;
        case CODE_RANGE:
            if (*word < arg1[i] || arg2[i] < *word)
                return BAD;
            break;
        case CODE_URANGE:
            if (arg1[i] <= *word && *word <= arg2[i])
                return BAD;
            break;
        default:
            return UNKNOWN;
        }

    }
    if (*word != '\0' || spec[i] != '\0')
        return BAD;

    return GOOD;
}


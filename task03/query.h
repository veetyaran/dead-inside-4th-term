#ifndef QUERY_H
#define QUERY_H
#define LEN 1024
#include <memory>
#include <string>

using std::string;
using std::unique_ptr;

enum class specSym
{
    regular = 0,
    uscore = 1, // '_'
    perc = 2, // '%'
    brac = 3, //[ ]
    revbrac = 4, //[^ ]
};
class words;

class query
{
public:
    string str;
    int * spec = nullptr;
    int speclen12 = 0;
public:
    query() = default;
    ~query()
    {
        if(spec)
            delete[]spec;
    }
    query(const query& x) = delete;
    query(query&& x)
    {
        std::swap(str, x.str);
        std::swap(spec, x.spec);
    }
    void setstr(string s)
    {
        str = s;
        getSpecLen12();
    }
    query& operator=(const query& x) = delete;
    query& operator=(query&& x)
    {
        if (this == &x)
            {return *this;}
        std::swap(str, x.str);
        std::swap(spec, x.spec);
        return *this;
    }
    int getSpecLen12()
    {
        int len = str.length();
        for(int i = 0; i < len; ++i)
        {
            if(str[i] == '\\')
            {
                if(i == len - 1 && str[i + 1] != '_' && str[i + 1] != '\\')
                    return -1; //incorrect word
                else
                    {speclen12++; i++;}
                
            }
            else   
                speclen12++;
            
        }
        return 0;
    }
    void printspec12(FILE * f = stdout)
    {
        for(int i = 0; i < speclen12; ++i)
        {
            fprintf(f, "%d ", static_cast<int>(spec[i]));
        }
        fprintf(f, "\n");
    }
    int parse12() //построить spec по слову
    {
        int len = str.length(), j = 0;
        spec = new int[speclen12]();
        for(int i = 0; i < len; ++i)
        {
            if(str[i] == '\\')
            {
                if(i == len - 1 && str[i + 1] != '_' && str[i + 1] != '\\')
                    return -1; //incorrect word
                else
                    {spec[j] = 0; ++i; ++j;}
                
            }
            else if(str[i] == '_')
            {
                spec[j] = 1;
                ++j;
            }
            else{spec[j] = 0; ++j;}
        }
        return 0;
    }
};

/*class tabs
{
private:
    int tab[256] = {};
public:
    tabs(string t)
    {
        int len = t.length();
        for(int i = 0; i < len; ++i)
        {
            tab[static_cast<int>(t[i])] = 1;
        }
    }
    char * getWord(char * , )

};*/

class words
{
public:
    string s;
    string tabs;
    int * pos = nullptr;
    int * postail = nullptr;
public:
    words() = default;
    ~words()
    {
        if(pos)
            delete[]pos;
        if(postail)    
            delete[]postail;
    }
    words(string h, string t)
    {
        s = h;
        tabs = t;
        parse();
    }
    words(words&& x)
    {
        std::swap(s, x.s);
        std::swap(tabs, x.tabs);
    }
    words& operator=(const words& x) = delete;
    words& operator=(words&& x)
    {
        if (this == &x)
            {return *this;}
        std::swap(s, x.s);
        std::swap(tabs, x.tabs);
        return *this;
    }
    void print(FILE * f = stdout)
    {
        int q = get_count();
        for(int i = 0; i < q; i++)
        {
            int p = pos[i];
            char c = s[p];
            while(!isTab(c) && c != '\0')
            {
                printf("%c", c);
                p++;
                c = s[p];
            }
            fprintf(f, " ");
        }
        fprintf(f, "\n");
    }
    bool isTab(char c)
    {
        if(tabs.find(c) == string::npos)
            return false;
        return true;
    }
    int get_count()
    {
        int counter = 1, i = 0;
        char c = s[i];
        while(s[i] != '\0')
        {
            if(isTab(c))
            {
                ++counter;
                while(isTab(c))
                {
                    ++i;
                    c = s[i];
                }
            }
            else {++i;
            c = s[i];}
        }
        return counter;
    }
    int parse()
    {
        int q = get_count();
        pos = new int[q];
        postail = new int[q];
        pos[0] = 0;
        int j = 1, k = 0, len = s.length();
        for(int i = 0; i < static_cast<int>(len);)
        {
                if(isTab(s[i]))
                {
                    postail[k] = i - 1;
                    k++;
                    while(isTab(s[i]))
                    {
                        i++;
                        if(s[i] == '\0')
                            return 0;
                    }
                    pos[j] = i;
                    j++;
                }
                else {i++;}
        }
        postail[q - 1] = s.length() - 1;
        return 0;
    }
};
#endif
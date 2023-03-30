#include <stdio.h>
#include "query.h"
int main(int argc, char ** argv)
{
    query A;
    (void)argc;
    string a = argv[1];
    string tab = argv[2];
    words b = words(a, tab);
    b.print(); 
    A.setstr(b.s.substr(b.pos[0], b.postail[0] + 1));
    A.parse12();
    A.printspec12();
    return 0;
}
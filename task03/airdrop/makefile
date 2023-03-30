#makefile

GCFLAGS=-O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format

all: a01.out a02.out a03.out a04.out a05.out a06.out

%.o: %.cpp
	g++ -c $(GCFLAGS) $<

%.out: %.o
	g++ $^ -o $@

clean:
	rm *.o*

a01.o: a01.cpp zapr.h  

a02.o: a02.cpp zapr.h  

a03.o: a03.cpp zapr.h  

a04.o: a04.cpp zapr.h  

a05.o: a05.cpp zapr.h  

a06.o: a05.cpp zapr.h 
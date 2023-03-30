CPPFLAGS = -O3 -mfpmath=sse -fstack-protector-all -g -W -Wall -Wextra -Wunused -Wcast-align -Werror -pedantic -pedantic-errors -Wfloat-equal -Wpointer-arith -Wformat-security -Wmissing-format-attribute -Wformat=1 -Wwrite-strings -Wcast-align -Wno-long-long -Woverloaded-virtual -Wnon-virtual-dtor -Wcast-qual -Wno-suggest-attribute=format
all: a01.out a02.out a05.out a06.out
err.o: err.cpp err.h
	g++ -c $(CPPFLAGS) err.cpp

parse.o: parse.cpp parse.h
	g++ -c $(CPPFLAGS) parse.cpp

coder.o: coder.cpp coder.h
	g++ -c $(CPPFLAGS) coder.cpp

task01.o: task01.cpp coder.h parse.h err.h
	g++ -c $< $(CPPFLAGS)

a01.out: err.o coder.o parse.o task01.o
	g++ $^ $(CPPFLAGS) -o $@

task02.o: task02.cpp coder.h parse.h err.h list.h
	g++ -c $< $(CPPFLAGS)

a02.out: err.o coder.o parse.o task02.o
	g++ $^ $(CPPFLAGS) -o $@

task05.o: task05.cpp coder.h parse.h err.h
	g++ -c $< $(CPPFLAGS)

a05.out: err.o coder.o parse.o task05.o
	g++ $^ $(CPPFLAGS) -o $@

task06.o: task06.cpp coder.h parse.h err.h
	g++ -c $< $(CPPFLAGS)

a06.out: err.o coder.o parse.o task06.o
	g++ $^ $(CPPFLAGS) -o $@

include Makefile.preamble
COMMON= ACJ.o Box.o Params.o SL2ACJ.o Complex.o roundoff.o
CPLUSPLUS= g++
CC=gcc

.SUFFIXES: .o .cpp .C

.cpp.o:
	$(CPLUSPLUS) $(COPTS) $(CCFLAGS) -c ${@:o=cpp}

verify_cusp: verify_cusp.o $(COMMON)
	$(CPLUSPLUS) $(COPTS) verify_cusp.o $(COMMON) $(LIBS) -o ../bin/verify_cusp

simple_tree_cat: simple_tree_cat.o
	$(CPLUSPLUS) $(COPTS) simple_tree_cat.o -o ../bin/simple_tree_cat

rootcat: rootcat.o
	$(CC) $(COPTS) rootcat.o -o ../bin/rootcat

depend:
	makedepend -I/usr/local/lib/g++-include -f Makefile.depend *.cpp
include Makefile.depend

# never optimize here, since the timing of arithmetic is important
test_float.o: test_float.cpp roundoff.h
	$(CPLUSPLUS) -g -c test_float.cpp

test_float: test_float.o roundoff.o roundoff.h
	$(CC) $(COPTS) test_float.o roundoff.o -o test_float -lm

# DO NOT DELETE THIS LINE -- make depend depends on it.

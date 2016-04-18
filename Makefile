INCLUDE_DIR=$(shell echo ~)/local/include
LIBRARY_DIR=$(shell echo ~)/local/lib
DESDTIR=/
PREFIX=/usr

CXX=g++
CXXFLAGS=-L${LIBRARY_DIR} -I${INCLUDE_DIR} -march=native -O2 -g -std=c++11 -fPIC -Wall -Wextra

all: spacerocks

install:

spacerocks: spacerocks.o
	${CXX} ${CXXFLAGS} -o spacerocks spacerocks.o -lboost_program_options -lSDL2

spacerocks.o: src/spacerocks.cc
	${CXX} ${CXXFLAGS} -c src/spacerocks.cc -o spacerocks.o

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.so
	rm -f spacerocks

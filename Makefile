INCLUDE_DIR=$(shell echo ~)/local/include
LIBRARY_DIR=$(shell echo ~)/local/lib
DESDTIR=/
PREFIX=/usr

CXX=g++
CXXFLAGS=-L${LIBRARY_DIR} -I${INCLUDE_DIR} -march=native -O2 -g -std=c++11 -fPIC -Wall -Wextra

all: spacerocks

install:

spacerocks: spacerocks.o space.o object.o physics.o
	${CXX} ${CXXFLAGS} -o spacerocks spacerocks.o space.o object.o physics.o -lboost_program_options -lSDL2

spacerocks.o: src/spacerocks.cc
	${CXX} ${CXXFLAGS} -c src/spacerocks.cc -o spacerocks.o

space.o: src/space.cc
	${CXX} ${CXXFLAGS} -c src/space.cc -o space.o

object.o: src/object.cc
	${CXX} ${CXXFLAGS} -c src/object.cc -o object.o

physics.o: src/physics.cc
	${CXX} ${CXXFLAGS} -c src/physics.cc -o physics.o

clean:
	rm -rf *.o
	rm -rf *.a
	rm -rf *.so
	rm -f spacerocks

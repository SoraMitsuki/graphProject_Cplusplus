# A simple makefile for CSE 100 PA4

CC=g++
CXXFLAGS=-std=c++11
LDFLAGS=

# if passed "type=opt" at command-line, compile with "-O3" flag (otherwise use "-g" for debugging)

ifeq ($(type),opt)
    CPPFLAGS += -O3
    LDFLAGS += -O3
else
    CPPFLAGS += -g
    LDFLAGS += -g
endif

all: pathfinder actorconnections extension



# include what ever source code *.h files pathfinder relies on (these are merely the ones that were used in the solution)

pathfinder: ActorGraph.o Vertex.o Edge.o

actorconnections: DisJointGraph.o Vertex.o Edge.o

extension: extension.o

# include what ever source code *.h files ActorGraph relies on (these are merely the ones that were used in the solution)

# Note: you do not have to include a *.cpp file if it aleady has a paired *.h file that is already included with class/method headers

ActorGraph.o: Vertex.h Edge.h ActorGraph.h

DisJointGraph.o: Vertex.h Edge.h DisJointGraph.h

Vertex.o: Edge.h Vertex.h

Edge.o: Edge.h

extension.o: extension.cpp

clean:
	rm -f pathfinder *.o core*
	rm -f actorconnections
	rm -f extension


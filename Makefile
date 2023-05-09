CXX=g++
CXXFLAGS=-std=c++20 -Wall -MMD -O2 -mtune=native
EXEC=bin/potechi
OBJECTS=src/potechi.o src/system.o src/framebuffer.o
INCLUDEFLAGS=-lncurses
DEPENDS=${OBJECTS:.o=.d}
PREFIX=/usr/local

${EXEC}: ${OBJECTS}
	mkdir -p bin
	${CXX} ${CXXFLAGS} ${OBJECTS} ${INCLUDEFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

install: remove ${EXEC}
	sudo cp bin/potechi ${PREFIX}/bin/potechi

remove:
	sudo rm -rf ${PREFIX}/bin/potechi

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
	rm -rf bin

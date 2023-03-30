CXX=g++
CXXFLAGS=-std=c++23 -Wall -MMD -O2 -mtune=znver3
EXEC=bin/potechi
OBJECTS=src/potechi.o src/system.o src/framebuffer.o
INCLUDEFLAGS=-lncurses
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	mkdir -p bin
	${CXX} ${CXXFLAGS} ${OBJECTS} ${INCLUDEFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
	rm -rf bin
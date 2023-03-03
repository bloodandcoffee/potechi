CXX=g++
CXXFLAGS=-std=c++20 -Wall -MMD -O2 -mtune=znver3
EXEC=bin/potechi
OBJECTS=
DEPENDS=${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	mkdir -p bin
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
	rm -rf bin
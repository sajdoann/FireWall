CXX=g++
CXXFLAGS = -Wall -pedantic -g -Og -std=c++17 -fsanitize=address
LD=g++
LDFLAGS =-fsanitize=address
${EXECUTABLE}: main.o
	${LD} ${LDFLAGS} $^ -o ${EXECUTABLE}


%.o:

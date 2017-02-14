#
# Makefile for HW6
#
CXX      = clang++
CXXFLAGS = -g -Wall -Wextra
LDFLAGS  = -g

hw6degrees: main.cpp hashfunc.cpp hashfunc.h Class.h Class.cpp \
	    Student.h Student.cpp Graph.h Graph.cpp
	${CXX} ${CXXFLAGS} -o hw6degrees main.cpp hashfunc.cpp \
		Class.cpp Student.cpp Graph.cpp

clean:
	rm -f hw6degrees

provide:
	provide comp15 hw6 main.cpp Makefile ReadMe.md hashfunc.cpp hashfunc.h \
	Class.h Class.cpp Student.h Student.cpp Graph.h Graph.cpp

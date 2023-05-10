CPP=g++ -std=c++11

CFLAGS= -c -Wall
all: main_program

main_program: Classroom.o Student.o main.o
	$(CPP) -o main_program Classroom.o Student.o main.o
# Clasroom: Classroom.cpp
# 	$(CPP) $(CFLAGS) Classroom.cpp
Student.o: Student.cpp
	$(CPP) $(CFLAGS) Student.cpp
main.o: main.cpp
	$(CPP) $(CFLAGS) main.cpp
valgrind: main_program
	valgrind --leak-check=full $(CFLAGS) Classroom.cpp
clean:
	rm -rf *o main_program
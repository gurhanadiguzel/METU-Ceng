CPP=g++ -g -std=c++98

CFLAGS= -c -Wall
all: call_by_value a.out

call_by_value:
	$(CPP) -o call_by_value call_by_value.cpp

a.out:
	$(CPP) call_by_reference.cpp

clean:
	rm -rf call_by_value call_by_reference
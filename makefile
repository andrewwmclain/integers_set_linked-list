CFLAGS = -std=c++14 -Wall

set:    integerset.o main.o 
	g++ integerset.o main.o -o set $(CFLAGS)

test:	unit-test.o integerset.o test.o
	g++ unit-test.o integerset.o test.o -o test $(CFLAGS)

main.o:	main.cpp integerset.h 
	g++ -c main.cpp $(CFLAGS)

integerset.o:	integerset.cpp integerset.h
	g++ -c integerset.cpp $(CFLAGS)

unit-test.o:	unit-test.cpp integerset.h 
	g++ -c unit-test.cpp $(CFLAGS)

test.o:	test.cpp test.h
	g++ -c test.cpp $(CFLAGS)

clean:
	rm -f test set *.o


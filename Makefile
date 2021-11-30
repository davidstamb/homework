
all: main

main: main.o calc.o printer.o
	g++ main.o calc.o printer.o -o main

main.o: main.cpp calc.cpp printer.cpp
	g++ -C main.cpp -o main.o

calc.o: calc.cpp calc.hpp
	g++ -C calc.cpp -o calculator.o

printer.o: printer.cpp printer.hpp
	g++ -C printer.cpp -o printer.o

clean:
	rm *.o && em main

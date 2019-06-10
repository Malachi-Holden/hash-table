main: main.o hashSet.o
	g++ -o main main.o hashSet.o

main.o: main.cpp hashSet.cpp
	g++ -c main.cpp

hashSet.o: hashSet.cpp
	g++ -c hashSet.cpp

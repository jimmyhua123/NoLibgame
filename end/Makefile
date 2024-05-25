
CXX = g++
CXXFLAGS = -std=c++11

all: main

main: main.o player.o game.o
	$(CXX) $(CXXFLAGS) -o main main.o player.o game.o

main.o: main.cpp player.h game.h
	$(CXX) $(CXXFLAGS) -c main.cpp

player.o: player.cpp player.h
	$(CXX) $(CXXFLAGS) -c player.cpp

game.o: game.cpp game.h
	$(CXX) $(CXXFLAGS) -c game.cpp

clean:
	rm -f *.o main

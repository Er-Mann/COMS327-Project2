CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

OBJS = BoardSquare.o InternalBoardSquare.o ExternalBoardSquare.o Config.o

all: testconfig

testconfig: ConfigTest.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o testconfig ConfigTest.o $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o testconfig
	

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

OBJS = BoardSquare.o InternalBoardSquare.o ExternalBoardSquare.o Config.o SquareInfo.o RobotInfo.o ConfigTest.o

all: testconfig

testconfig: $(OBJS)
	$(CXX) $(CXXFLAGS) -o testconfig $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o testconfig

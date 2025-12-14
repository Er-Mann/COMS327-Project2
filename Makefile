CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -g

PARTA_OBJS = BoardSquare.o InternalBoardSquare.o ExternalBoardSquare.o SquareInfo.o RobotInfo.o Config.o
PARTB_OBJS = Config.o Util.o Content.o Square.o GameBoard.o

all: testconfig testgameboard

testconfig: ConfigTest.o $(PARTA_OBJS)
	$(CXX) $(CXXFLAGS) -o testconfig ConfigTest.o $(PARTA_OBJS)

testgameboard: TestGameBoard.o $(PARTB_OBJS)
	$(CXX) $(CXXFLAGS) -o testgameboard TestGameBoard.o $(PARTB_OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o testconfig testgameboard

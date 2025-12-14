#include "GameBoard.h"
#include <iostream>

int main(int argc, char** argv)
{
    if (argc < 2)
    {
        std::cout << "Usage: " << argv[0] << " <configfile>\n";
        return 1;
    }

    Config c(argv[1]);
    GameBoard& gb = GameBoard::getInstance("xyzzy");
    gb.resetBoard(c);
    gb.testPrintBoard();
    return 0;
}

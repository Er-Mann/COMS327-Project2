#pragma once
#include <string>
#include <stdexcept>
#include "Config.h"
#include "Util.h"
#include "Square.h"
#include "Content.h"
#include "RobotMoveRequest.h"

class GameBoard
{
private:
    GameBoard(const GameBoard&) = delete;
    GameBoard& operator=(const GameBoard&) = delete;
    GameBoard();

    static constexpr int N = 15;

    InternalSquare board[N][N];

    Location redLoc;
    Location blueLoc;
    bool redPlaced;
    bool bluePlaced;

    Color activeRobot;

    int turn;
    int longRangeRemaining;

    bool inBounds(const Location& loc) const;
    InternalSquare& at(const Location& loc);
    const InternalSquare& at(const Location& loc) const;

    Location forwardLocation(Color robotColor) const;
    Direction& directionRef(Color robotColor);
    const Direction& directionRef(Color robotColor) const;

    Location& locationRef(Color robotColor);
    const Location& locationRef(Color robotColor) const;

    void placeRandomObstacles(int count, bool rocks);
    Location randomEmptyLocation() const;

public:
    static GameBoard& getInstance(std::string password);

    void resetBoard();
    void resetBoard(Config c);

    Square& getSquareContent(const Location& loc);

    bool moveRobot(RobotMoveRequest moveRequest);
    bool paintBlobHit(RobotMoveRequest moveRequest);

    void setSquareColor(const Location& loc, Color color);

    const RobotContent& getRobotContent(Color robotColor);

    int blueScore() const;
    int redScore() const;
    int turnNumber() const;

    AgentSquare** getLongRangeScan(Color robotColor) const;
    AgentSquare** getShortRangeScan(Color robotColor) const;

    void testPrintBoard();
    void testPrintSquare(Location loc);
};

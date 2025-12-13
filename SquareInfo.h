#ifndef SQUAREINFO_H
#define SQUAREINFO_H

#include "RobotInfo.h"

enum PBSquareContent
{
    EMPTY,
    ROCK,
    FOG,
    ROCKFOG,
    WALL
};

enum PBColor : int
{
    RED,
    BLUE,
    WHITE
};

class SquareInfo
{
public:
    PBSquareContent content;
    PBColor color;
    RobotInfo robot;

    SquareInfo();
    SquareInfo(PBSquareContent c, PBColor squareColor, const RobotInfo &robotInfo);
};

#endif

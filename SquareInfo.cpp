#include "SquareInfo.h"

SquareInfo::SquareInfo()
    : content(EMPTY), color(WHITE), robot()
{
}

SquareInfo::SquareInfo(PBSquareContent c, PBColor squareColor, const RobotInfo &robotInfo)
    : content(c), color(squareColor), robot(robotInfo)
{
}

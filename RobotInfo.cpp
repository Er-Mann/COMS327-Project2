#include "SquareInfo.h"
#include "RobotInfo.h"

RobotInfo::RobotInfo()
    : robotPresent(false), color(WHITE)
{
}

RobotInfo::RobotInfo(bool present, PBColor c)
    : robotPresent(present), color(c)
{
}

#ifndef ROBOTINFO_H
#define ROBOTINFO_H

enum PBColor : int;

enum PBDirection
{
    NORTH,
    EAST,
    SOUTH,
    WEST
};

class RobotInfo
{
public:
    bool robotPresent;
    PBColor color;

    RobotInfo();
    RobotInfo(bool present, PBColor c);
};

#endif

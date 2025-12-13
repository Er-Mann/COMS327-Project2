#ifndef BOARDSQUARE_H
#define BOARDSQUARE_H

#include "SquareInfo.h"

class BoardSquare
{
public:
    virtual ~BoardSquare() = default;
    virtual SquareInfo getSquareInfo() const = 0;
    virtual RobotInfo getRobotInfo() const = 0;
};

#endif

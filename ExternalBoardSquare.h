#ifndef EXTERNALBOARDSQUARE_H
#define EXTERNALBOARDSQUARE_H

#include "BoardSquare.h"

class InternalBoardSquare;

class ExternalBoardSquare : public BoardSquare
{
public:
    ExternalBoardSquare();
    explicit ExternalBoardSquare(const InternalBoardSquare &internalSquare);

    SquareInfo getSquareInfo() const override;
    RobotInfo getRobotInfo() const override;

private:
    SquareInfo m_squareInfo;
};

#endif

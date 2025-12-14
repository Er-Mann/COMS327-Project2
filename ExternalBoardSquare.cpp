#include "ExternalBoardSquare.h"
#include "InternalBoardSquare.h"

ExternalBoardSquare::ExternalBoardSquare()
    : m_squareInfo()
{
}

ExternalBoardSquare::ExternalBoardSquare(const InternalBoardSquare &internalSquare)
    : m_squareInfo(internalSquare.getSquareInfo())
{
}

SquareInfo ExternalBoardSquare::getSquareInfo() const
{
    return m_squareInfo;
}

RobotInfo ExternalBoardSquare::getRobotInfo() const
{
    return m_squareInfo.robot;
}


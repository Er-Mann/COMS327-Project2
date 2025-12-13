#include "InternalBoardSquare.h"

InternalBoardSquare::InternalBoardSquare()
    : m_content(EMPTY),
      m_color(WHITE),
      m_robot()
{
}

InternalBoardSquare::InternalBoardSquare(PBSquareContent content,
                                         PBColor squareColor,
                                         const RobotInfo &robotInfo)
    : m_content(content),
      m_color(squareColor),
      m_robot(robotInfo)
{
}

void InternalBoardSquare::setContent(PBSquareContent content)
{
    m_content = content;
}

void InternalBoardSquare::setColor(PBColor color)
{
    m_color = color;
}

void InternalBoardSquare::setRobotInfo(const RobotInfo &robotInfo)
{
    m_robot = robotInfo;
}

SquareInfo InternalBoardSquare::getSquareInfo() const
{
    return SquareInfo(m_content, m_color, m_robot);
}

RobotInfo InternalBoardSquare::getRobotInfo() const
{
    return m_robot;
}

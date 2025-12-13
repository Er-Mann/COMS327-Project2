#ifndef INTERNALBOARDSQUARE_H
#define INTERNALBOARDSQUARE_H

#include "BoardSquare.h"

class InternalBoardSquare : public BoardSquare
{
public:
    InternalBoardSquare();
    InternalBoardSquare(PBSquareContent content,
                        PBColor squareColor,
                        const RobotInfo &robotInfo = RobotInfo());

    void setContent(PBSquareContent content);
    void setColor(PBColor color);
    void setRobotInfo(const RobotInfo &robotInfo);

    SquareInfo getSquareInfo() const override;
    RobotInfo getRobotInfo() const override;

private:
    PBSquareContent m_content;
    PBColor m_color;
    RobotInfo m_robot;
};

#endif

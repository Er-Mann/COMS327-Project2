#include "Square.h"

NotPresent Square::NotPresentInstance;
RockContent Square::RockInstance;
FogContent Square::FogInstance;
WallContent Square::WallInstance;

Square::Square() {}

ObscuredSquare::ObscuredSquare()
{
    Rock = &NotPresentInstance;
    Fog = &NotPresentInstance;
    SquareColor = &NotPresentInstance;
    Robot = &NotPresentInstance;
    Wall = &NotPresentInstance;
}

AgentSquare::AgentSquare(Color squareColor, bool rockPresent, bool fogPresent, bool robotPresent, Color robotColor)
    : agentSquareColor(squareColor),
      agentRobotContent(robotPresent ? robotColor : Color::None, Direction::North, Color::None)
{
    Rock = rockPresent ? static_cast<Content*>(&RockInstance) : static_cast<Content*>(&NotPresentInstance);
    Fog = fogPresent ? static_cast<Content*>(&FogInstance) : static_cast<Content*>(&NotPresentInstance);
    SquareColor = (squareColor == Color::None) ? static_cast<Content*>(&NotPresentInstance) : static_cast<Content*>(&agentSquareColor);
    Robot = robotPresent ? static_cast<Content*>(&agentRobotContent) : static_cast<Content*>(&NotPresentInstance);
    Wall = &NotPresentInstance;
}

AgentSquare::AgentSquare(const InternalSquare& s)
    : AgentSquare(s.getSquareColor(), s.hasRock(), s.hasFog(), s.hasRobot(),
                  s.hasRobot() ? s.robotContent().getColor() : Color::None)
{
}

AgentSquare::AgentSquare()
    : agentSquareColor(Color::None),
      agentRobotContent(Color::None, Direction::North, Color::None)
{
    Rock = &NotPresentInstance;
    Fog = &NotPresentInstance;
    SquareColor = &NotPresentInstance;
    Robot = &NotPresentInstance;
    Wall = &NotPresentInstance;
}


InternalSquare::InternalSquare()
    : internalSquareColor(Color::White),
      internalRobotContent(Color::None, Direction::North, Color::None)
{
    SquareColor = static_cast<Content*>(&internalSquareColor);
    Robot = &NotPresentInstance;
    Rock = &NotPresentInstance;
    Fog = &NotPresentInstance;
    Wall = &NotPresentInstance;
}

void InternalSquare::setSquareColor(Color c)
{
    internalSquareColor.setColor(c);
    SquareColor = (c == Color::None) ? static_cast<Content*>(&NotPresentInstance) : static_cast<Content*>(&internalSquareColor);
}

Color InternalSquare::getSquareColor() const
{
    return internalSquareColor.getColor();
}

void InternalSquare::setRobot(Color robotColor, Direction d, Color paintColor)
{
    internalRobotContent.setColor(robotColor);
    internalRobotContent.setDirection(d);
    internalRobotContent.setPaintColor(paintColor);
    Robot = static_cast<Content*>(&internalRobotContent);
}

void InternalSquare::clearRobot()
{
    internalRobotContent.setColor(Color::None);
    internalRobotContent.setPaintColor(Color::None);
    internalRobotContent.setDirection(Direction::North);
    Robot = &NotPresentInstance;
}

bool InternalSquare::hasRobot() const
{
    return Robot != &NotPresentInstance && Robot->isPresent();
}

RobotContent& InternalSquare::robotContent()
{
    return internalRobotContent;
}

const RobotContent& InternalSquare::robotContent() const
{
    return internalRobotContent;
}

void InternalSquare::setRock(bool present)
{
    Rock = present ? static_cast<Content*>(&RockInstance) : static_cast<Content*>(&NotPresentInstance);
}

void InternalSquare::setFog(bool present)
{
    Fog = present ? static_cast<Content*>(&FogInstance) : static_cast<Content*>(&NotPresentInstance);
}

bool InternalSquare::hasRock() const
{
    return Rock != &NotPresentInstance && Rock->isPresent();
}

bool InternalSquare::hasFog() const
{
    return Fog != &NotPresentInstance && Fog->isPresent();
}

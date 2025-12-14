#pragma once
#include "Util.h"
#include "Content.h"

class InternalSquare;

class Square
{
public:
    Content* Rock = &NotPresentInstance;
    Content* Fog = &NotPresentInstance;
    Content* SquareColor = &NotPresentInstance;
    Content* Robot = &NotPresentInstance;
    Content* Wall = &NotPresentInstance;

    static NotPresent NotPresentInstance;
    static RockContent RockInstance;
    static FogContent FogInstance;
    static WallContent WallInstance;

    Square();
    virtual ~Square() = default;
};

class ObscuredSquare : public Square
{
public:
    ObscuredSquare();
};

class AgentSquare : public Square
{
private:
    SquareColorContent agentSquareColor;
    RobotContent agentRobotContent;

public:
    AgentSquare();
    AgentSquare(Color squareColor, bool rockPresent, bool fogPresent, bool robotPresent, Color robotColor);
    AgentSquare(const InternalSquare& s);
};

class InternalSquare : public Square
{
private:
    SquareColorContent internalSquareColor;
    RobotContent internalRobotContent;

public:
    InternalSquare();

    void setSquareColor(Color c);
    Color getSquareColor() const;

    void setRobot(Color robotColor, Direction d, Color paintColor);
    void clearRobot();
    bool hasRobot() const;
    RobotContent& robotContent();
    const RobotContent& robotContent() const;

    void setRock(bool present);
    void setFog(bool present);
    bool hasRock() const;
    bool hasFog() const;
};

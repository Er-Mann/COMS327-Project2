#pragma once
#include "Util.h"

class Content
{
public:
    virtual bool isPresent() const = 0;
    virtual ~Content() = default;
};

class NotPresent : public Content
{
public:
    bool isPresent() const;
};

class RockContent : public Content
{
public:
    bool isPresent() const;
};

class FogContent : public Content
{
public:
    bool isPresent() const;
};

class WallContent : public Content
{
public:
    bool isPresent() const;
};

class SquareColorContent : public Content
{
private:
    Color color;

public:
    SquareColorContent(Color c);
    bool isPresent() const;
    Color getColor() const;
    void setColor(Color c);
};

class RobotContent : public Content
{
private:
    Color color;
    Direction direction;
    Color paintColor;

public:
    RobotContent(Color c, Direction d, Color p);
    bool isPresent() const;
    Color getColor() const;
    const Direction& getDirection() const;
    Direction& getDirection();
    Color getPaintColor() const;

    void setDirection(Direction d);
    void setPaintColor(Color p);
    void setColor(Color c);
};

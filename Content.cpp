#include "Content.h"

bool NotPresent::isPresent() const { return false; }
bool RockContent::isPresent() const { return true; }
bool FogContent::isPresent() const { return true; }
bool WallContent::isPresent() const { return true; }

SquareColorContent::SquareColorContent(Color c) : color(c) {}
bool SquareColorContent::isPresent() const { return color != Color::None; }
Color SquareColorContent::getColor() const { return color; }
void SquareColorContent::setColor(Color c) { color = c; }

RobotContent::RobotContent(Color c, Direction d, Color p)
    : color(c), direction(d), paintColor(p) {}

bool RobotContent::isPresent() const { return color != Color::None; }
Color RobotContent::getColor() const { return color; }
const Direction& RobotContent::getDirection() const { return direction; }
Direction& RobotContent::getDirection() { return direction; }
Color RobotContent::getPaintColor() const { return paintColor; }

void RobotContent::setDirection(Direction d) { direction = d; }
void RobotContent::setPaintColor(Color p) { paintColor = p; }
void RobotContent::setColor(Color c) { color = c; }

#pragma once

enum RobotMove { TurnLeft, TurnRight, MoveForward, NoMove };

struct RobotMoveRequest
{
    RobotMove move;
    bool fire;
};

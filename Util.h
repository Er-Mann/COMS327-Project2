#pragma once
#include <string>

enum class Color { Red, Blue, White, None };

struct Location
{
    int row;
    int col;

    Location();
    Location(int r, int c);

    Location& operator+(const Location& other);
    Location& operator-(const Location& other);

    bool operator==(const Location& other) const;
    bool operator!=(const Location& other) const;
};

struct Direction
{
    int dRow;
    int dCol;

    static const Direction North;
    static const Direction East;
    static const Direction South;
    static const Direction West;

    Direction();
    Direction(int dr, int dc);

    Direction RotateLeft90() const;
    Direction RotateRight90() const;
    Direction Rotate180() const;
};

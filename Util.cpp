#include "Util.h"

Location::Location() : row(0), col(0) {}
Location::Location(int r, int c) : row(r), col(c) {}

Location& Location::operator+(const Location& other)
{
    row += other.row;
    col += other.col;
    return *this;
}

Location& Location::operator-(const Location& other)
{
    row -= other.row;
    col -= other.col;
    return *this;
}

bool Location::operator==(const Location& other) const
{
    return row == other.row && col == other.col;
}

bool Location::operator!=(const Location& other) const
{
    return !(*this == other);
}

Direction::Direction() : dRow(-1), dCol(0) {}
Direction::Direction(int dr, int dc) : dRow(dr), dCol(dc) {}

const Direction Direction::North = Direction(-1, 0);
const Direction Direction::East  = Direction(0, 1);
const Direction Direction::South = Direction(1, 0);
const Direction Direction::West  = Direction(0, -1);

Direction Direction::RotateLeft90() const
{
    return Direction(-dCol, dRow);
}

Direction Direction::RotateRight90() const
{
    return Direction(dCol, -dRow);
}

Direction Direction::Rotate180() const
{
    return Direction(-dRow, -dCol);
}

#include "GameBoard.h"
#include <random>
#include <iostream>

static char colorChar(Color c)
{
    if (c == Color::White) return 'W';
    if (c == Color::Red) return 'R';
    if (c == Color::Blue) return 'B';
    return '-';
}

static char robotChar(Color c)
{
    if (c == Color::Red) return 'R';
    if (c == Color::Blue) return 'B';
    return '-';
}

static char obstructionChar(bool rock, bool fog)
{
    if (rock && fog) return 'X';
    if (rock) return 'R';
    if (fog) return 'F';
    return '-';
}

GameBoard::GameBoard()
    : redLoc(0, 0),
      blueLoc(0, 0),
      redPlaced(false),
      bluePlaced(false),
      activeRobot(Color::Red),
      turn(0),
      longRangeRemaining(0)
{
    resetBoard();
}

GameBoard& GameBoard::getInstance(std::string password)
{
    if (password != "xyzzy")
    {
        throw std::invalid_argument("Invalid password");
    }
    static GameBoard instance;
    return instance;
}

bool GameBoard::inBounds(const Location& loc) const
{
    return loc.row >= 0 && loc.row < N && loc.col >= 0 && loc.col < N;
}

InternalSquare& GameBoard::at(const Location& loc)
{
    return board[loc.row][loc.col];
}

const InternalSquare& GameBoard::at(const Location& loc) const
{
    return board[loc.row][loc.col];
}

Location& GameBoard::locationRef(Color robotColor)
{
    return (robotColor == Color::Red) ? redLoc : blueLoc;
}

const Location& GameBoard::locationRef(Color robotColor) const
{
    return (robotColor == Color::Red) ? redLoc : blueLoc;
}

Direction& GameBoard::directionRef(Color robotColor)
{
    if (robotColor == Color::Red) return at(redLoc).robotContent().getDirection();
    return at(blueLoc).robotContent().getDirection();
}

const Direction& GameBoard::directionRef(Color robotColor) const
{
    if (robotColor == Color::Red) return at(redLoc).robotContent().getDirection();
    return at(blueLoc).robotContent().getDirection();
}

Location GameBoard::forwardLocation(Color robotColor) const
{
    const Location& cur = locationRef(robotColor);
    const Direction d = at(cur).robotContent().getDirection();
    return Location(cur.row + d.dRow, cur.col + d.dCol);
}

void GameBoard::placeRandomObstacles(int count, bool rocks)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, N - 1);

    int placed = 0;
    while (placed < count)
    {
        Location loc(dist(gen), dist(gen));
        if (!inBounds(loc)) continue;
        InternalSquare& s = at(loc);

        if (s.hasRock()) continue;
        if (s.hasRobot()) continue;

        if (rocks)
        {
            s.setRock(true);
        }
        else
        {
            s.setFog(true);
        }
        placed++;
    }
}

Location GameBoard::randomEmptyLocation() const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, N - 1);

    while (true)
    {
        Location loc(dist(gen), dist(gen));
        if (!inBounds(loc)) continue;
        const InternalSquare& s = at(loc);
        if (s.hasRock()) continue;
        if (s.hasFog()) continue;
        if (s.hasRobot()) continue;
        return loc;
    }
}

void GameBoard::resetBoard()
{
    Config c;
    resetBoard(c);
}

void GameBoard::resetBoard(Config c)
{
    turn = 0;
    longRangeRemaining = c.getLongRangeLimit();
    redPlaced = false;
    bluePlaced = false;
    activeRobot = Color::Red;

    for (int r = 0; r < N; ++r)
    {
        for (int col = 0; col < N; ++col)
        {
            board[r][col] = InternalSquare();
            board[r][col].setSquareColor(Color::White);
            board[r][col].setRock(false);
            board[r][col].setFog(false);
            board[r][col].clearRobot();
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> rockDist(c.getRockLowerBound(), c.getRockUpperBound());
    std::uniform_int_distribution<int> fogDist(c.getFogLowerBound(), c.getFogUpperBound());

    placeRandomObstacles(rockDist(gen), true);
    placeRandomObstacles(fogDist(gen), false);

    redLoc = randomEmptyLocation();
    at(redLoc).setRobot(Color::Red, Direction::North, Color::Red);
    redPlaced = true;

    blueLoc = randomEmptyLocation();
    at(blueLoc).setRobot(Color::Blue, Direction::North, Color::Blue);
    bluePlaced = true;
}

Square& GameBoard::getSquareContent(const Location& loc)
{
    if (!inBounds(loc))
    {
        throw std::out_of_range("Location out of range");
    }
    return at(loc);
}

void GameBoard::setSquareColor(const Location& loc, Color color)
{
    if (!inBounds(loc))
    {
        throw std::out_of_range("Location out of range");
    }
    at(loc).setSquareColor(color);
}

const RobotContent& GameBoard::getRobotContent(Color robotColor)
{
    if (robotColor == Color::Red)
    {
        return at(redLoc).robotContent();
    }
    return at(blueLoc).robotContent();
}

int GameBoard::redScore() const
{
    int count = 0;
    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            if (board[r][c].getSquareColor() == Color::Red) count++;
        }
    }
    return count;
}

int GameBoard::blueScore() const
{
    int count = 0;
    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            if (board[r][c].getSquareColor() == Color::Blue) count++;
        }
    }
    return count;
}

int GameBoard::turnNumber() const
{
    return turn;
}

bool GameBoard::moveRobot(RobotMoveRequest moveRequest)
{
    Color robotColor = activeRobot;
    Location cur = locationRef(robotColor);
    InternalSquare& curSq = at(cur);

    if (!curSq.hasRobot()) return false;

    Direction d = curSq.robotContent().getDirection();

    if (moveRequest.move == TurnLeft)
    {
        curSq.robotContent().setDirection(d.RotateLeft90());
        return true;
    }
    if (moveRequest.move == TurnRight)
    {
        curSq.robotContent().setDirection(d.RotateRight90());
        return true;
    }
    if (moveRequest.move == NoMove)
    {
        return true;
    }

    if (moveRequest.move == MoveForward)
    {
        Location next(cur.row + d.dRow, cur.col + d.dCol);
        if (!inBounds(next)) return false;

        InternalSquare& nextSq = at(next);
        if (nextSq.hasRock()) return false;
        if (nextSq.hasRobot()) return false;

        curSq.setSquareColor(robotColor);
        RobotContent rc = curSq.robotContent();
        curSq.clearRobot();

        nextSq.setRobot(robotColor, rc.getDirection(), rc.getPaintColor());
        locationRef(robotColor) = next;

        activeRobot = (activeRobot == Color::Red) ? Color::Blue : Color::Red;
        turn++;

        return true;
    }

    return false;
}

bool GameBoard::paintBlobHit(RobotMoveRequest moveRequest)
{
    Color robotColor = activeRobot;
    if (!moveRequest.fire) return false;

    Color other = (robotColor == Color::Red) ? Color::Blue : Color::Red;

    const Location& cur = locationRef(robotColor);
    const Direction d = at(cur).robotContent().getDirection();

    Location probe(cur.row + d.dRow, cur.col + d.dCol);

    while (inBounds(probe))
    {
        const InternalSquare& s = at(probe);
        if (s.hasRock()) return false;
        if (s.hasRobot() && s.robotContent().getColor() == other) return true;
        probe.row += d.dRow;
        probe.col += d.dCol;
    }
    return false;
}

AgentSquare** GameBoard::getLongRangeScan(Color robotColor) const
{
    AgentSquare** scan = new AgentSquare*[N];
    for (int r = 0; r < N; ++r)
    {
        scan[r] = new AgentSquare[N];
        for (int c = 0; c < N; ++c)
        {
            scan[r][c] = AgentSquare(board[r][c]);
        }
    }
    return scan;
}

AgentSquare** GameBoard::getShortRangeScan(Color robotColor) const
{
    const int S = 5;
    AgentSquare** scan = new AgentSquare*[S];
    for (int r = 0; r < S; ++r)
    {
        scan[r] = new AgentSquare[S];
    }

    Location center = locationRef(robotColor);
    Direction fwd = at(center).robotContent().getDirection();
    Direction left = fwd.RotateLeft90();
    Direction up = fwd;

    for (int dr = -2; dr <= 2; ++dr)
    {
        for (int dc = -2; dc <= 2; ++dc)
        {
            Location loc(center.row + up.dRow * dr + left.dRow * dc,
                         center.col + up.dCol * dr + left.dCol * dc);

            int rr = dr + 2;
            int cc = dc + 2;

            if (!inBounds(loc))
            {
                scan[rr][cc] = AgentSquare(Color::None, false, false, false, Color::None);
                continue;
            }

            const InternalSquare& s = at(loc);
            scan[rr][cc] = AgentSquare(s);
        }
    }

    return scan;
}

void GameBoard::testPrintSquare(Location loc)
{
    if (!inBounds(loc))
    {
        std::cout << "---";
        return;
    }

    const InternalSquare& s = at(loc);

    char c = colorChar(s.getSquareColor());
    char o = obstructionChar(s.hasRock(), s.hasFog());

    char r = '-';
    if (s.hasRobot())
    {
        r = robotChar(s.robotContent().getColor());
    }

    std::cout << c << o << r;
}

void GameBoard::testPrintBoard()
{
    for (int r = 0; r < N; ++r)
    {
        for (int c = 0; c < N; ++c)
        {
            testPrintSquare(Location(r, c));
            if (c != N - 1) std::cout << " ";
        }
        std::cout << "\n";
    }
}

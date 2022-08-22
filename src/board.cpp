#include "../include/board.h"
#include "../include/robot.h"
#include "../include/command.h"

Board::Board() : Board(std::make_pair(-1, -1)) {}

Board::Board(pair<int, int> XYDimension) : boardXYDimensions(XYDimension) {}

bool Board::isValidMovement(pair<int, int> newPosition) const
{
    if (newPosition.first < 0 || newPosition.first >= boardXYDimensions.first)
    {
        return false;
    }
    if (newPosition.second < 0 || newPosition.second >= boardXYDimensions.second)
    {
        return false;
    }
    return true;
}

bool Board::move(const Robot &robot, const Command &command)
{
    pair<int, int> newPosition = robot.checkNewStateIsValid(command);
    auto orientation_command = command.orientationMap.find(robot.getRobotOrientationAsStr());
    if (isValidMovement(newPosition))
    {

        auto [x, y] = orientation_command->second;
        robotPositionXY.first += x;
        robotPositionXY.second += y;
        return true;
    }
    return false;
}

pair<int, int> Board::getRobotPosition()
{
    return robotPositionXY;
}

pair<int, int> Board::getBoardSize()
{
    return boardXYDimensions;
}

ostream &operator<<(ostream &os, Board &b)
{
    auto [xDimension, yDimension] = b.getBoardSize();
    auto [robotXposition, robotYposition] = b.getRobotPosition();
    for (int col = 0; col < yDimension; ++col)
    {
        for (int row = 0; row < xDimension; ++row)
        {
            if (robotXposition == row && robotYposition == col)
            {
                os << "R";
            }
            else
            {
                os << ".";
            }
        }
        os << endl;
    }
    return os;
}

void Board::syncWithRobot(const Robot &robot)
{
    Robot newRobot = robot;
    robotPositionXY = newRobot.getRobotPosition();
}
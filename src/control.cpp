#include "../include/control.h"
#include "../include/robot.h"
#include "../include/board.h"
#include "../include/command.h"

#include <utility>
using std::make_pair;
using std::pair;

#include <ostream>
using std::ostream;

Control::Control()
{
    Command command;
    Robot robot(command);
    Board board(command.boardXYDimension);
}

void Control::movePiece(const Command &command)
{
    this->command = command;
    if (command.givenCommand == "REPORT")
    {
        cout << *this << endl;
    }
    else if (command.givenCommand == "PLACE")
    {
        robot = Robot(command);
    }
    else if (board.move(robot, command))
    {
        robot.updateState(command);
    }
    board.syncWithRobot(robot);
}

const pair<Robot, Board> Control::getControlState() const
{
    return std::make_pair(robot, board);
}

ostream &operator<<(ostream &os, const Control &c)
{
    if (!c.command.canIStart)
    {
        os << "Na Na You did not say the magic word" << endl;
        return os;
    }
    auto [robot, board] = c.getControlState();
    // os << robot << " " << board;
    auto [xDimension, yDimension] = board.getBoardSize();
    auto [robotXposition, robotYposition] = robot.getRobotPosition();
    for (int row = xDimension - 1; row >= 0; --row)
    {
        for (int col = 0; col < yDimension; col++)
        {
            if (robotXposition == row && robotYposition == col)
            {
                os << " " << robot;
            }
            else
            {
                os << " "
                   << ".";
            }
        }
        os << endl;
    }
    cout << "\nOutput: " << robotXposition << "," << robotYposition << "," << robot.getRbotSOrientation() << endl;
    return os;
}

Control::Control(const Command &command)
{
    this->command = command;
    board = Board(command.boardXYDimension);
    robot = Robot(command);
}
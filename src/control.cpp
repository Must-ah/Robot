#include "../include/control.h"

Control::Control()
{
    Command command;
    Robot robot;
    Board board;
}

void Control::movePiece(const Command &command)
{

    if (command.givenCommand == "REPORT")
    {
        cout << *this << endl;
    }
    else if (command.givenCommand == "PLACE")
    {
        *this = Control(command);
    }
    else if (board.move(robot, command))
    {
        this->command = command;
        this->command.startOrientation = robot.getRobotOrientationAsStr();
        robot.updateState(this->command);
    }
    board.syncWithRobot(robot);
}

const pair<Robot, Board> Control::getControlState() const
{
    return std::make_pair(robot, board);
}
const Command Control::getControlCommandState() const
{
    return command;
}

ostream &operator<<(ostream &os, const Control &c)
{
    if (!c.command.canIStart)
    {
        os << "Ah ah ah, you didn't say the magic word" << endl;
        return os;
    }
    auto [robot, board] = c.getControlState();
    auto [xDimension, yDimension] = board.getBoardSize();
    auto [robotXposition, robotYposition] = robot.getRobotPosition();
    os << " \n";
    for (int row = xDimension - 1; row >= 0; --row)
    {
        for (int col = 0; col < yDimension; ++col)
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
    os << "\nOutput: "
       << robotYposition
       << "," << robotXposition
       << "," << robot.getRobotOrientationAsStr()
       << endl;
    return os;
}

Control::Control(const Command &command)
{

    this->command = command;
    board = Board(command.boardXYDimension);
    robot = Robot(command);
}
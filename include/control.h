#include "robot.h"
#include "board.h"
#include "command.h"

#ifndef CONTROL_H
#define CONTROL_H

#include <utility>
using std::make_pair;
using std::pair;

#include <ostream>
using std::ostream;

#include <iostream>
using std::cout;
using std::endl;

/*
class Robot;
class Board;
struct Command;
*/

class Control
{
    Robot robot;
    Board board;
    Command command;    

public:
    Control();
    Control(const Command &command);
    void movePiece(const Command &command);
    void updateRobotState(Robot &robot, const Command &command);
    void updateBoard(Board &board, const Robot &robot);
    const pair<Robot, Board> getControlState() const;
    const Command getControlCommandState() const;
    friend ostream &operator<<(ostream &os, const Control &c);
  
};

#endif
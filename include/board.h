#ifndef BOARD_H
#define BOARD_H

#include <utility>
using std::pair;

#include <ostream>
using std::ostream;
class Robot;
struct Command;
class Board
{
    pair<int,int> boardXYDimensions = std::make_pair(5, 5);    
    pair<int, int> robotPositionXY = std::make_pair(0, 0);

    //  methods
    bool isValidMovement(pair<int, int> newPosition) const;

    friend ostream &operator<<(ostream &os, const Board &b);

public:
    Board();
    Board(pair<int,int>XYDimensions);
    bool move(const Robot& robot, const Command& command);
    pair<int, int> getRobotPosition();
    pair<int, int> getBoardSize();
   void syncWithRobot(const Robot& robot);
};

#endif // BOARD_H
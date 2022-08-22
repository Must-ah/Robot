#ifndef ROBOT_H
#define ROBOT_H

#include <utility>
using std::pair;
#include <string>
using std::string;

#include <unordered_map>
using std::unordered_map;

#include <ostream>
using std::ostream;

struct Command;

class Robot
{
    pair<int, int> robotXYposition = std::make_pair(-1, -1);
    string robotOrientation = "NORTH";

    unordered_map<string, char> orientationMap = {
        {"NORTH", '^'},
        {"EAST", '>'},
        {"WEST", '<'},
        {"SOUTH", 'v'}};

    unordered_map<int, string> robotPose = {
        {0, "NORTH"},
        {1, "EAST"},
        {2, "SOUTH"},
        {3, "WEST"}};
    unordered_map<string, int> inverseRobotPose = {
        {"NORTH", 0},
        {"EAST", 1},
        {"WEST", 2},
        {"SOUTH", 3}};

    int robotPoseIndex = 0;

public:
    Robot();
    Robot(const Command& command);
    pair<int, int> getRobotPosition();
    void updateState(const Command &command);
    pair<int,int> checkNewStateIsValid(const Command &command) const ;
    const char getRobotOrientation() const;
    const string getRobotOrientationAsStr() const;
    friend ostream &operator<<(ostream &os, const Robot &r);
};

#endif // ROBOT_H
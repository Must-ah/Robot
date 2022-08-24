#include "../include/robot.h"
#include "../include/command.h"

Robot::Robot() {}

Robot::Robot(const Command &command)
{
    if (command.canIStart)
    {
        robotXYposition = command.startPosition;
        robotOrientation = command.startOrientation;
        robotPoseIndex = inverseRobotPose.at(robotOrientation);
    }
}
pair<int, int> Robot::getRobotPosition()
{
    return robotXYposition;
}

void Robot::updateState(const Command &command)
{
    robotOrientation = robotPose.at(robotPoseIndex);
    auto searchIfCommandRotation = command.rotationMap.find(command.givenCommand);
    auto orientation_command = command.orientationMap.find(robotOrientation);
    if (searchIfCommandRotation != command.rotationMap.end())
    {
        robotPoseIndex += searchIfCommandRotation->second;
        robotPoseIndex = (0 > robotPoseIndex) ? 3 : robotPoseIndex % 4;
        robotOrientation = robotPose.at(robotPoseIndex);
    }
    else if (orientation_command != command.orientationMap.end())
    {
        auto [x, y] = orientation_command->second;
        robotXYposition.first += x;
        robotXYposition.second += y;
    }
}

pair<int, int> Robot::checkNewStateIsValid(const Command &command) const
{
    string newRobotOrientation = robotPose.at(robotPoseIndex);
    auto searchIfCommandRotation = command.rotationMap.find(command.givenCommand);
    auto orientation_command = command.orientationMap.find(newRobotOrientation);

    if (searchIfCommandRotation != command.rotationMap.end())
    {
        return robotXYposition;
    }
    else if (orientation_command != command.orientationMap.end())
    {
        auto [x, y] = orientation_command->second;
        int xPosition = robotXYposition.first;
        int yPosition = robotXYposition.second;
        xPosition += x;
        yPosition += y;

        return std::make_pair(xPosition, yPosition);
    }
    return std::make_pair(robotXYposition.first, robotXYposition.second);
}

const char Robot::getRobotOrientationAsChar() const
{
    auto search = orientationMap.find(robotOrientation);
    if (search != orientationMap.end())
    {
        return search->second;
    }
    return '?';
}

ostream &operator<<(ostream &os, const Robot &r)
{
    auto orientation = r.getRobotOrientationAsChar();
    os << orientation;
    return os;
}

const string Robot::getRobotOrientationAsStr() const
{
    return robotOrientation;
}
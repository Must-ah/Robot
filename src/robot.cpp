#include "../include/robot.h"
#include "../include/command.h"

Robot::Robot()
{
    robotXYposition = std::make_pair(0, 0);
    robotOrientation = "NORTH";
}

Robot::Robot(const Command &command)
{
    robotXYposition = command.startPosition;
    robotOrientation = command.startOrientation;
    robotPoseIndex = inverseRobotPose.at(robotOrientation);
}
pair<int, int> Robot::getRobotPosition()
{
    return robotXYposition;
}

void Robot::updateState(const Command &command)
{
    robotOrientation = robotPose.at(robotPoseIndex);
    // cout << "robot orientation:1 " << robotOrientation << endl;
    auto searchIfCommandRotation = command.rotationMap.find(command.givenCommand);
    auto orientation_command = command.orientationMap.find(robotOrientation);
    if (searchIfCommandRotation != command.rotationMap.end())
    {
        robotPoseIndex += searchIfCommandRotation->second;

        robotPoseIndex = (0 > robotPoseIndex) ? 3 : robotPoseIndex % 4;

        robotOrientation = robotPose.at(robotPoseIndex);
        // cout << "robot Pose Index: " << robotPoseIndex << endl;
        // cout << "robot orientation: " << robotOrientation << endl;
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
    string newrobotOrientation = robotPose.at(robotPoseIndex);
    auto searchIfCommandRotation = command.rotationMap.find(command.givenCommand);
    auto orientation_command = command.orientationMap.find(newrobotOrientation);

    if (searchIfCommandRotation != command.rotationMap.end())
    {
        return robotXYposition;
    }
    else if (orientation_command != command.orientationMap.end())
    {
        // cout<<"New STATE robot orientation: "<<newrobotOrientation<<endl;
        auto [x, y] = orientation_command->second;
        int xPosition = robotXYposition.first;
        int yPosition = robotXYposition.second;
        xPosition += x;
        yPosition += y;
        // cout<< "x: "<<xPosition<<" y: "<<yPosition<<endl;
        return std::make_pair(xPosition, yPosition);
    }
    return std::make_pair(robotXYposition.first, robotXYposition.second);
}

const char Robot::getRobotOrientation() const
{
    auto search = orientationMap.find(robotOrientation);
    if (search != orientationMap.end())
    {
        // cout << search->second;
        return search->second;
    }
    return '?';
}

ostream &operator<<(ostream &os, const Robot &r)
{
    auto orientation = r.getRobotOrientation();
    os << orientation; // << " x " << r.robotXYposition.first << " y " << r.robotXYposition.second;
    return os;
}

const string Robot::getRbotSOrientation() const
{
    return robotOrientation;
}
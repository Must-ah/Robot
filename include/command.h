#ifndef COMMAND_H
#define COMMAND_H

#include <unordered_map>
using std::unordered_map;

#include <utility>
using std::pair;

#include <string>
using std::string;

#include <iostream>
using std::endl;

#include <unordered_set>
using std::unordered_set;

struct Command
{
    bool canIStart = false;
    string givenCommand = "MOVE";
    unordered_map<string, pair<int, int>> orientationMap = {
        {"NORTH", std::make_pair(1, 0)},
        {"EAST", std::make_pair(0, 1)},
        {"WEST", std::make_pair(0, -1)},
        {"SOUTH", std::make_pair(-1, 0)},
    };
    unordered_map<string, int> rotationMap =
        {
            {"LEFT", -1},
            {"RIGHT", 1}};
    unordered_set<string> validCommands = {
        "MOVE",
        "LEFT",
        "RIGHT",
        "REPORT",
    };
    pair<int, int> startPosition = std::make_pair(0, 0);
    string startOrientation = "NORTH";
    pair<int, int> boardXYDimension = std::make_pair(5, 5);
    Command() = default;
    Command(string newCommand)
    {
        bool commandValid = validCommands.find(newCommand) != validCommands.end();
        if (!canIStart)
        {
            std::string::size_type n = newCommand.find("PLACE");
            if (n != std::string::npos)
            {
                auto startPosX = newCommand.find(" ") + 1;
                auto endPosX = newCommand.find(",", startPosX + 1);
                string xP = newCommand.substr(startPosX, endPosX - startPosX);
                startPosition.first = std::stoi(xP);

                auto startPosY = endPosX + 1;
                auto endPosY = newCommand.find(",", startPosY);
                string yP = newCommand.substr(startPosY, endPosY - startPosY);
                startPosition.second = std::stoi(yP);
                auto startOrientationIdx = newCommand.find_last_of(",");
                string orientation = newCommand.substr(startOrientationIdx + 1);

                auto searchDirection = orientationMap.find(orientation);
                if (searchDirection != orientationMap.end())
                {
                    auto [xBoardDim, yBoardDim] = boardXYDimension;
                    if (startPosition.first >= 0 && startPosition.first <= xBoardDim)
                    {
                        if (startPosition.second >= 0 && startPosition.second <= yBoardDim)
                        {
                            canIStart = true;
                            startOrientation = orientation;
                            givenCommand = "PLACE";
                        }
                    }
                }
            }
        }
    }
    bool updateCommandState(const string &inComingCommand)
    {
        bool commandValid = validCommands.find(inComingCommand) != validCommands.end();
        if (canIStart && commandValid)
        {
            // cout << "updateCommandState " << inComingCommand << endl;
            givenCommand = inComingCommand;
            return true;
        }
        else if (!commandValid)
        {
            // cout << "Invalid Command" << endl;
            Command cmd(inComingCommand);
            if (cmd.canIStart && !inComingCommand.empty())
            {
                //   cout << "INCOMING: " << inComingCommand << endl;
                *this = cmd;
                return true;
            }
        }

        return false;
    }
};

#endif
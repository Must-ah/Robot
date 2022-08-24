#ifndef COMMAND_H
#define COMMAND_H

#include <unordered_map>
using std::unordered_map;

#include <utility>
using std::pair;

#include <string>
using std::string;

#include <iostream>
using std::cout;
using std::endl;

#include <unordered_set>
using std::unordered_set;

#include <stdexcept>

struct Command
{
    bool canIStart = false;
    string givenCommand = "NaN";
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
    pair<int, int> startPosition = std::make_pair(-1, -1);
    string startOrientation = "NaNC";
    pair<int, int> boardXYDimension = std::make_pair(5, 5);
    Command() = default;
    Command(string newCommand)
    {

        if (!canIStart)
        {
            std::string::size_type n = newCommand.find("PLACE");
            if (n != std::string::npos)
            {
                auto startPosY = newCommand.find(" ") + 1;
                auto endPosY = newCommand.find(",", startPosY + 1);
                string yP = newCommand.substr(startPosY, endPosY - startPosY);

                auto startPosX = endPosY + 1;
                auto endPosX = newCommand.find(",", startPosX);
                string xP = newCommand.substr(startPosX, endPosX - startPosX);
                auto startOrientationIdx = newCommand.find_last_of(",");
                string orientation = newCommand.substr(startOrientationIdx + 1);
                int tempX = -1;
                int tempY = -1;
                try
                {
                    tempX = std::stoi(xP);
                    tempY = std::stoi(yP);
                }
                catch (std::invalid_argument const &ex)
                {
                    throw std::invalid_argument("Invalid argument");
                }
                catch (std::out_of_range const &ex)
                {

                    throw std::out_of_range("Out of range");
                }
                auto searchDirection = orientationMap.find(orientation);
                if (searchDirection != orientationMap.end())
                {
                    auto [xBoardDim, yBoardDim] = boardXYDimension;
                    if (tempX >= 0 && tempX <= xBoardDim)
                    {
                        if (tempY >= 0 && tempY <= yBoardDim)
                        {
                            startPosition.first = std::stoi(xP);
                            startPosition.second = std::stoi(yP);
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
         
            givenCommand = inComingCommand;
            return true;
        }
        else if (!commandValid)
        {
            
            Command cmd(inComingCommand);
            if (cmd.canIStart && !inComingCommand.empty())
            {
                *this = cmd;
                return true;
            }
        }

        return false;
    }
};

#endif
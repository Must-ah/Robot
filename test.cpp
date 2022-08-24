#include <gtest/gtest.h>

#include "include/board.h"
#include "include/robot.h"
#include "include/command.h"
#include "include/control.h"
#include "include/inputGeneratorFile.h"

#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

#include <utility>
using std::make_pair;
using std::pair;
#include <vector>
using std::vector;

TEST(StringGeneratorTest, NoneValidPath)
{
    vector<string> inputPath{
        "454",
        "",
        "./"
        "~/",
    };
    const string expectedResponse = "File not found";
    for (auto inputFileName : inputPath)
    {
        StringGenerator inputData = fileOpener(inputFileName);
        for (auto line : inputData)
        {
            EXPECT_TRUE(line == expectedResponse || expectedResponse == line);
        }
    }
}

TEST(CommandTest, InvalidCommands)
{
    const string filePath = "../data/invalidCommand.txt";
    StringGenerator inputData = fileOpener(filePath);
    for (auto line : inputData)
    {
        Command command(line);
        EXPECT_FALSE(command.canIStart);
    }
}

TEST(CommandTest, invalidStartPosition)
{
    const string filePath = "../data/invalidStartPosition.txt";
    StringGenerator inputData = fileOpener(filePath);
    for (auto line : inputData)
    {
        Command command(line);
        EXPECT_FALSE(command.canIStart);
    }
}

TEST(CommandTest, startPosNotINTValue)
{
    const string filePath = "../data/startPosNotINTValue.txt";
    StringGenerator inputData = fileOpener(filePath);
    for (auto line : inputData)
    {
        try
        {
            Command command(line);
            Control cmd(command);
        }
        catch (std::invalid_argument const &ex)
        {
            string expectedResponse = ex.what();
            EXPECT_EQ(expectedResponse, "Invalid argument");
        }
    }
}
TEST(CommandTest, startPosToLargeIntValue)
{
    const string filePath = "../data/startPosToLargeIntValue.txt";
    StringGenerator inputData = fileOpener(filePath);
    for (auto line : inputData)
    {
        try
        {
            Command command(line);
            Control cmd(command);
        }
        catch (std::out_of_range const &ex)
        {
            string expectedResponse = ex.what();
            EXPECT_EQ(expectedResponse, "Out of range");
        }
    }
}

TEST(ControlTest, sendValidCommands)
{
    const string filePath = "../data/input.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command command;
    for (auto line : inputData)
    {
        command.updateCommandState(line);
        Control cmd(command);
        Command cmdState = cmd.getControlCommandState();
        EXPECT_TRUE(cmdState.canIStart);
    }
}

TEST(ControlTest, sendInvalidCommands)
{
    const string filePath = "../data/invalidCommand.txt";
    StringGenerator inputData = fileOpener(filePath);
    for (auto line : inputData)
    {
        Command command(line);
        Control cmd(command);
        auto [robot, board] = cmd.getControlState();
        auto [xPosition, yPosition] = robot.getRobotPosition();
        EXPECT_EQ(xPosition, -1);
        EXPECT_EQ(yPosition, -1);
        EXPECT_FALSE(command.canIStart);
    }
}

TEST(ControlTest, sendInvalidStartPosition)
{
    const string filePath = "../data/invalidStartPosition.txt";
    StringGenerator inputData = fileOpener(filePath);
    for (auto line : inputData)
    {
        Command command(line);
        Control cmd(command);
        auto [robot, board] = cmd.getControlState();
        auto [xPosition, yPosition] = robot.getRobotPosition();
        EXPECT_EQ(xPosition, -1);
        EXPECT_EQ(yPosition, -1);
    }
}

TEST(ControlTest, sendOneValidCommandRestInvalid)
{
    const int expectedXPosition = 4;
    const int expectedYPosition = 3;
    const string robotOrientation = "EAST";
    const string filePath = "../data/oneValidCommandRestNotValid.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_EQ(xPosition, expectedXPosition);
    EXPECT_EQ(yPosition, expectedYPosition);
    EXPECT_STREQ(robotOrientation.c_str(), robotOrientationState.c_str());
}

TEST(ControlTest, oneValidCommandInStartAndAtTheEnd)
{
    const int expectedXPosition = 2;
    const int expectedYPosition = 1;
    const string robotOrientation = "WEST";
    const string filePath = "../data/oneValidCommandInStartAndAtTheEnd.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_EQ(xPosition, expectedXPosition);
    EXPECT_EQ(yPosition, expectedYPosition);
    EXPECT_STREQ(robotOrientation.c_str(), robotOrientationState.c_str());
}

TEST(RobotTEST, robotDontFallNORTH)
{
    const int expectedXPosition = 4;
    const int expectedYPosition = 4;
    const string robotOrientation = "NORTH";
    const string filePath = "../data/robotDontFallNORTH.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_EQ(xPosition, expectedXPosition);
    EXPECT_EQ(yPosition, expectedYPosition);
    EXPECT_STREQ(robotOrientation.c_str(), robotOrientationState.c_str());
}
TEST(RobotTEST, robotDontFallEAST)
{
    const int expectedXPosition = 4;
    const int expectedYPosition = 4;
    const string robotOrientation = "EAST";
    const string filePath = "../data/robotDontFallEAST.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_EQ(xPosition, expectedXPosition);
    EXPECT_EQ(yPosition, expectedYPosition);
    EXPECT_STREQ(robotOrientation.c_str(), robotOrientationState.c_str());
}

TEST(RobotTEST, robotDontFallWEST)
{
    const int expectedXPosition = 0;
    const int expectedYPosition = 0;
    const string robotOrientation = "WEST";
    const string filePath = "../data/robotDontFallWEST.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_EQ(xPosition, expectedXPosition);
    EXPECT_EQ(yPosition, expectedYPosition);
    EXPECT_STREQ(robotOrientation.c_str(), robotOrientationState.c_str());
}
TEST(RobotTEST, robotDontFallSOUTH)
{
    const int expectedXPosition = 0;
    const int expectedYPosition = 0;
    const string robotOrientation = "SOUTH";
    const string filePath = "../data/robotDontFallSOUTH.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_EQ(xPosition, expectedXPosition);
    EXPECT_EQ(yPosition, expectedYPosition);
    EXPECT_STREQ(robotOrientation.c_str(), robotOrientationState.c_str());
}

TEST(RobotTest, robotOrientationRight)
{
    const int expectedXPosition = 2;
    const int expectedYPosition = 2;
    const string validCommand = "PLACE 2,2,NORTH";
    vector<string> rightSequence = {"EAST", "SOUTH", "WEST", "NORTH"};
    Command cmd(validCommand);
    Control control(cmd);
    for (auto correctOrientation : rightSequence)
    {
        cmd.updateCommandState("RIGHT");
        control.movePiece(cmd);
        auto [robot, board] = control.getControlState();
        auto [xPosition, yPosition] = robot.getRobotPosition();
        EXPECT_EQ(xPosition, expectedXPosition);
        EXPECT_EQ(yPosition, expectedYPosition);
        const string robotOrientationState = robot.getRobotOrientationAsStr();
        EXPECT_STREQ(correctOrientation.c_str(), robotOrientationState.c_str());
    }
}

TEST(RobotTest, robotOrientationLEFT)
{
    const int expectedXPosition = 3;
    const int expectedYPosition = 3;
    const string validCommand = "PLACE 3,3,NORTH";
    vector<string> rightSequence = {"WEST", "SOUTH", "EAST", "NORTH"};
    Command cmd(validCommand);
    Control control(cmd);
    for (auto correctOrientation : rightSequence)
    {
        cmd.updateCommandState("LEFT");
        control.movePiece(cmd);
        auto [robot, board] = control.getControlState();
        auto [xPosition, yPosition] = robot.getRobotPosition();
        EXPECT_EQ(xPosition, expectedXPosition);
        EXPECT_EQ(yPosition, expectedYPosition);
        const string robotOrientationState = robot.getRobotOrientationAsStr();
        EXPECT_STREQ(correctOrientation.c_str(), robotOrientationState.c_str());
    }
}
TEST(ControlTest, InputExampleInputA)
{
    const int expectedXPosition = 0;
    const int expectedYPosition = 1;
    const string correctOrientation = "NORTH";
    const string filePath = "../data/inputA.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    EXPECT_EQ(yPosition, expectedXPosition);
    EXPECT_EQ(xPosition, expectedYPosition);
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_STREQ(correctOrientation.c_str(), robotOrientationState.c_str());
}
TEST(ControlTest, InputExampleInputB)
{
    const int expectedXPosition = 0;
    const int expectedYPosition = 0;
    const string correctOrientation = "WEST";
    const string filePath = "../data/inputB.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    EXPECT_EQ(yPosition, expectedXPosition);
    EXPECT_EQ(xPosition, expectedYPosition);
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_STREQ(correctOrientation.c_str(), robotOrientationState.c_str());
}
TEST(ControlTest, InputExampleInputC)
{
    const int expectedXPosition = 3;
    const int expectedYPosition = 3;
    const string correctOrientation = "NORTH";
    const string filePath = "../data/inputC.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    EXPECT_EQ(yPosition, expectedXPosition);
    EXPECT_EQ(xPosition, expectedYPosition);
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_STREQ(correctOrientation.c_str(), robotOrientationState.c_str());
}
TEST(ControlTest, moveOnTheWholeBoardInput)
{
    const int expectedXPosition = 3;
    const int expectedYPosition = 3;
    const string correctOrientation = "NORTH";
    const string filePath = "../data/moveOnTheWholeBoardInput.txt";
    StringGenerator inputData = fileOpener(filePath);
    Command cmd;
    Control control;
    for (auto line : inputData)
    {
        cmd.updateCommandState(line);
        control.movePiece(cmd);
    }
    auto [robot, board] = control.getControlState();
    auto [xPosition, yPosition] = robot.getRobotPosition();
    EXPECT_EQ(yPosition, expectedXPosition);
    EXPECT_EQ(xPosition, expectedYPosition);
    const string robotOrientationState = robot.getRobotOrientationAsStr();
    EXPECT_STREQ(correctOrientation.c_str(), robotOrientationState.c_str());
}
int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    /*
        string inputFileName = "../data/input.txt";
        StringGenerator inputData = fileOpener(inputFileName);
        Command command;
        Control control;
        for (auto line : inputData)
        {
            bool success =command.updateCommandState(line);

            if (command.canIStart && success)
            {
                cout << "CMD: "
                     << line
                     << endl;
                control.movePiece(command);
            }
        }
    */
    cout << "END" << endl;

    return RUN_ALL_TESTS();
}

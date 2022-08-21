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

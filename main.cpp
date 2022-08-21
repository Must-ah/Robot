
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

int main()
{

    string inputFileName = "../data/input.txt";
    StringGenerator inputData = fileOpener(inputFileName);
    Command command;
    Control control;
    for (auto line : inputData)
    {
        bool success = command.updateCommandState(line);
        if (command.canIStart && success)
        {
            cout << "CMD: "
                 << line
                 << endl;
            control.movePiece(command);
        }
    }

    cout << "END" << endl;
}
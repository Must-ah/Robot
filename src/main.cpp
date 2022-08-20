#include <iostream>
using std::cin;
using std::cout;
using std::endl;
#include <string>
using std::string;

#include <utility>
using std::make_pair;
using std::pair;

#include "board.cpp"
#include "command.cpp"
#include "robot.cpp"
#include "control.cpp"

#include "cor-input.cpp"

int main()
{

    StringGenerator inputData = fileOpener("data/input.txt");
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
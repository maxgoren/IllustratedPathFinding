#include <iostream>
#include <BearLibTerminal.h>
#include "Engine.hpp"
using namespace std;

int main()
{
    terminal_open();
    terminal_set("window: size=80x40;");
    Engine myGame(80, 40);
    myGame.mainLoop();
    terminal_close();
    return 0;
}
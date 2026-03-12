#include "RunSession.h"

int main()
{
    // RunSession encapsulates all of the interactive logic.  main
    // simply creates the object and kicks off the game loop.
    RunSession session;
    session.run();
    return 0;
}
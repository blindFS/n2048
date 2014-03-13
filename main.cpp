#include "n2048.h"

int main()
{
    n2048 n = n2048();
    n.game_run();
    endwin();
    return 0;
}

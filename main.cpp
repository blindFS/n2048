#include "n2048.h"
#include <unistd.h>

int main(int argc, char **argv)
{
    int h = 4, w = 4, c, t;
    while ((c = getopt(argc, argv, "h:w:")) != -1) {
        switch (c) {
            case 'h' : if ((t = atoi(optarg)) > 0)
                           h = t;
                       break;
            case 'w' : if ((t = atoi(optarg)) > 0)
                           w = t;
                       break;
        }
    }
    n2048 n = n2048(h, w);
    n.game_run();
    endwin();
    return 0;
}

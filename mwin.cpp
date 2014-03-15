#include "mwin.h"

mwin::mwin() {
    int x, y;
    initscr();

    if(has_colors() != TRUE)
    {
        endwin();
        printf("ERROR, your terminal can't display colors.\n");
    }
    getmaxyx(stdscr, y, x);
    if(x < WIDTH+2 || y < HEIGHT+3) {
        endwin();
        printf("ERROR, your terminal is too small. (min %ux%u)\n", WIDTH, HEIGHT);
    }
    clear();
    noecho();
    start_color();

    for (int i = 0; i < 15; i++)
        init_pair(i, COLOR_BLACK, 200+2*i);

    curs_set(0); // remove curser
    refresh();
    mainwin    = newwin(HEIGHT+1, WIDTH+2, 0, 0);
    scorewin   = newwin(3, WIDTH+2, HEIGHT+2, 0);
}

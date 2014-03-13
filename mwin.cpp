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
    if(x < WIDTH || y < HEIGHT) {
        endwin();
        printf("ERROR, your terminal is too small. (min %ux%u)\n", WIDTH, HEIGHT);
    }
    clear();
    noecho();
    start_color();

    init_pair(0, COLOR_BLACK, COLOR_WHITE);
    init_pair(1, COLOR_BLACK, COLOR_RED);
    init_pair(2, COLOR_BLACK, COLOR_YELLOW);
    init_pair(3, COLOR_BLACK, COLOR_BLUE);
    init_pair(4, COLOR_BLACK, COLOR_GREEN);
    init_pair(5, COLOR_BLACK, COLOR_CYAN);
    init_pair(6, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(7, COLOR_BLACK, COLOR_WHITE);
    init_pair(8, COLOR_BLACK, COLOR_GREEN);
    init_pair(9, COLOR_BLACK, COLOR_CYAN);
    init_pair(10, COLOR_BLACK, COLOR_MAGENTA);
    init_pair(11, COLOR_BLACK, COLOR_WHITE);

    curs_set(0); // remove curser
    refresh();
    mainwin    = newwin(HEIGHT+1, WIDTH+2, 0, 0);
    scorewin   = newwin(10, 20, HEIGHT+1, WIDTH/2-10);
    box(mainwin, 0, 0);
}

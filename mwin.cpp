#include "mwin.h"

mwin::mwin(int hgt, int wid) {
    int x, y;
    mheight     = hgt;
    mwidth      = wid;
    mmax        = std::max(hgt, wid);
    mnum        = hgt*wid;
    mbrickwidth = 4;
    height      = mbrickwidth*hgt;
    width       = 2*wid*mbrickwidth;

    initscr();

    if(has_colors() != TRUE)
    {
        endwin();
        printf("ERROR, your terminal can't display colors.\n");
    }
    getmaxyx(stdscr, y, x);
    if(x < width+2 || y < height+3) {
        endwin();
        printf("ERROR, your terminal is too small. (min %ux%u)\n", width, height);
    }
    clear();
    noecho();
    start_color();

    for (int i = 0; i < 15; i++)
        init_pair(i, COLOR_BLACK, 200+2*i);

    curs_set(0); // remove curser
    refresh();
    mainwin    = newwin(height+1, width+2, 0, 0);
    scorewin   = newwin(3, width+2, height+2, 0);
}

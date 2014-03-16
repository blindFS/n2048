#include "brick.h"
#include <ncurses.h>

#ifndef MWIN_H
#define MWIN_H

class mwin {
    public:
    int mheight, mwidth, mmax, mnum, mbrickwidth, height, width;
    WINDOW* mainwin;
    WINDOW* scorewin;
    mwin(int hgt, int wid);
    mwin() {};
};

#endif

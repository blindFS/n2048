#include "brick.h"
#include <ncurses.h>

#ifndef MWIN_H
#define MWIN_H

#define MHEIGHT 4
#define MWIDTH 4
#define MMAX max(MHEIGHT, MWIDTH)
#define MNUM MHEIGHT*MWIDTH

#define MBRICKWIDTH 5
#define HEIGHT MBRICKWIDTH*MHEIGHT
#define WIDTH 2*HEIGHT

class mwin {
    public:
    WINDOW* mainwin;
    WINDOW* scorewin;
    mwin();
};

#endif

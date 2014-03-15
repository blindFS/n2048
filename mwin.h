#include "brick.h"
#include <ncurses.h>

#ifndef MWIN_H
#define MWIN_H

#define MHEIGHT 1
#define MWIDTH 16
#define MMAX 16 
#define MNUM MHEIGHT*MWIDTH

#define MBRICKWIDTH 4
#define HEIGHT MBRICKWIDTH*MHEIGHT
#define WIDTH 2*MBRICKWIDTH*MWIDTH

class mwin {
    public:
    WINDOW* mainwin;
    WINDOW* scorewin;
    mwin();
};

#endif

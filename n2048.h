#include "mwin.h"

#ifndef NTFZE
#define NTFZE

class n2048 {
    mwin mw;
    int max, score, best, empty;
    int mheight, mwidth, mmax, mnum, mbrickwidth, height, width;
    brick **ebricks;
    brick **gbricks;
    bool need_new;
    bool running;
    int **numbers_old;
    void check_finish();
    void main_refresh();
    void show_score();
    void get_key();
    void brick_reduce(int direction);
    void new_brick();
    void mov_brick(int direction);
    bool mov_and_merge(brick **temp, int num);
    void undo();
    void paint_brick();
    void collect_empty();
    void replay();
    public:
    n2048(int hgt, int wid);
    n2048() {};
    void game_run();
};

#endif

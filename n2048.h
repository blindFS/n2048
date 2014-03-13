#include "mwin.h"

#ifndef NTFZE
#define NTFZE

class n2048 {
    mwin mw;
    int max, score, empty;
    brick *ebricks[MNUM];
    brick gbricks[MHEIGHT][MWIDTH];
    bool need_new;
    int gbricks_old[MHEIGHT][MWIDTH];
    void check_finish();
    void main_refresh();
    void show_score();
    void get_key();
    void brick_reduce(int direction);
    void new_brick();
    void mov_brick(int direction);
    bool mov_and_merge(brick *temp[MWIDTH]);
    void undo();
    void backup();
    void paint_brick();
    void collect_empty();
    public:
    n2048();
    void game_run();
};

#endif

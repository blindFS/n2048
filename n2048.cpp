#include "n2048.h"
#include <unistd.h>

n2048::n2048() {
    srand(time(NULL));
    mw = mwin();
    max = 1;
    score = 0;
    need_new = true;
    empty = MNUM;
    for (int i = 0; i < MHEIGHT; i++) {
        for (int j = 0; j < MWIDTH; j++) {
            gbricks[i][j] = brick(i, j, 0);
        }
    }
    this->backup();
    this->collect_empty();
}

void n2048::collect_empty() {
    int k = 0;
    for (int i = 0; i < MHEIGHT; i++) {
        for (int j = 0; j < MWIDTH; j++) {
            if (gbricks[i][j].number == 0) {
                ebricks[k] = &(gbricks[i][j]);
                k++;
            }
        }
    }
    empty = k;
}

void n2048::game_run() {

    this->show_score();
    this->new_brick();
    this->main_refresh();
    // nodelay(stdscr, true);
    while (true) {
        need_new = false;
        this->get_key();
    }
}

bool n2048::mov_and_merge(brick *temp[MWIDTH]) {
    bool moved = false;
    int i, j, t;
    for (i = 0; i < MWIDTH; i++) {
        for (j = 0; j < MWIDTH-i-1; j++) {
            if (temp[j]->number == 0 && temp[j+1]->number != 0) {
                t = temp[j]->number;
                temp[j]->number = temp[j+1]->number;
                temp[j+1]->number = t;
                moved = true;
                need_new = true;
            }
        }
    }
    for (i = 0; i < MWIDTH-1; i++) {
        if (temp[i]->number == temp[i+1]->number && temp[i]->number != 0) {
            score += 1 << temp[i]->number;
            temp[i]->number++;
            temp[i+1]->number = 0;
            moved = true;
            need_new = true;
        }
    }
    return moved;
}

void n2048::mov_brick(int direction) {
    int i, j;
    bool move;
    brick *temp[MWIDTH];
    switch (direction) {
        case 0:
            for (i = 0; i < MHEIGHT; i++) {
                move =true;
                for (j = 0; j < MWIDTH; j++) {
                    temp[j] = &(gbricks[i][j]);
                }
                while (move)
                    move = this->mov_and_merge(temp);
            }
            break;
        case 1:
            for (j = 0; j < MWIDTH; j++) {
                move =true;
                for (i = 0; i < MHEIGHT; i++) {
                    temp[MHEIGHT-i-1] = &(gbricks[i][j]);
                }
                while (move)
                    move = this->mov_and_merge(temp);
            }
            break;
        case 2:
            for (j = 0; j < MWIDTH; j++) {
                move =true;
                for (i = 0; i < MHEIGHT; i++) {
                    temp[i] = &(gbricks[i][j]);
                }
                while (move)
                    move = this->mov_and_merge(temp);
            }
            break;
        case 3:
            for (i = 0; i < MHEIGHT; i++) {
                move =true;
                for (j = 0; j < MWIDTH; j++) {
                    temp[MWIDTH-j-1] = &(gbricks[i][j]);
                }
                while (move)
                    move = this->mov_and_merge(temp);
            }
            break;
    }
}

void n2048::brick_reduce(int direction) {
    this->backup();
    this->mov_brick(direction);
    this->collect_empty();
    this->check_finish();
    this->new_brick();
    this->main_refresh();
}

void n2048::check_finish() {
    if (max == 11) {
        // win
    }
    if (empty == 0) {
        // lose
        // werase(mw.mainwin);
        // wattron(mw.mainwin, COLOR_PAIR(1));
        // mvwprintw(mw.mainwin, 9, 14, "You lose!");
        // wattroff(mw.mainwin, COLOR_PAIR(1));
        // wrefresh(mw.mainwin);
        // sleep(2);
        // endwin();
        // exit(0);
    }
}

void n2048::new_brick() {
    if (!need_new) {
        return;
    }
    int index = rand() % empty;
    ebricks[index]->number = 1;
    this->collect_empty();
}

void n2048::get_key() {
    switch (getch()) {
        case 'h':
            this->brick_reduce(0);
            break;
        case 'j':
            this->brick_reduce(1);
            break;
        case 'k':
            this->brick_reduce(2);
            break;
        case 'l':
            this->brick_reduce(3);
            break;
        case 'i':
            need_new = true;
            this->new_brick();
            this->main_refresh();
            break;
        case 'r':
            this->main_refresh();
            break;
        case 'u':
            this->undo();
            break;
        case 'q':
            endwin();
            exit(0);
    }
}

void n2048::backup() {
    int i, j;
    for (i = 0; i < MHEIGHT; i++) {
        for (j = 0; j < MWIDTH; j++) {
            gbricks_old[i][j] = gbricks[i][j].number;
        }
    }
}

void n2048::undo() {
    int i, j;
    for (i = 0; i < MHEIGHT; i++) {
        for (j = 0; j < MWIDTH; j++) {
            gbricks[i][j].number = gbricks_old[i][j];
        }
    }
    this->main_refresh();
}

void n2048::main_refresh() {
    mw = mwin();
    for (int i = 0; i < MHEIGHT; i++) {
        for (int j = 0; j < MWIDTH; j++) {
            wattron(mw.mainwin, COLOR_PAIR(gbricks[i][j].number));
            mvwprintw(mw.mainwin, i*5, j*10, "%d", gbricks[i][j].number);
            wattroff(mw.mainwin, COLOR_PAIR(gbricks[i][j].number));
        }
    }
    wrefresh(mw.mainwin);
    this->show_score();
}

void n2048::show_score()
{
    werase(mw.scorewin);
    mvwprintw(mw.scorewin, 2, 2, "score:%d", score);
    wrefresh(mw.scorewin);
}
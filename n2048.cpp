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
            numbers_old[i][j] = 0;
        }
    }
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
            if (max < temp[i]->number)
                max = temp[i]->number;
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
    int t[MHEIGHT][MWIDTH];
    int i, j;
    for (i = 0; i < MHEIGHT; i++) {
        for (j = 0; j < MWIDTH; j++) {
            t[i][j] = gbricks[i][j].number;
        }
    }
    need_new = false;
    this->mov_brick(direction);
    this->collect_empty();
    if (need_new) {
        for (i = 0; i < MHEIGHT; i++) {
            for (j = 0; j < MWIDTH; j++) {
                numbers_old[i][j] = t[i][j];
            }
        }
    }
    this->new_brick();
    this->main_refresh();
    this->check_finish();
}

void n2048::check_finish() {
    if (max > 14) {
        wattron(mw.mainwin, COLOR_PAIR(0));
        mvwprintw(mw.mainwin, HEIGHT/2, WIDTH/2-4, "You Win!");
        wattroff(mw.mainwin, COLOR_PAIR(0));
        wrefresh(mw.mainwin);
        sleep(5);
    }
    if (empty == 0) {
        // lose
        brick temp = *ebricks[0];
        int x = temp.x;
        int y = temp.y;
        if (x > 0 && gbricks[x-1][y].number == temp.number)
            return;
        if (x < MHEIGHT-1 && gbricks[x+1][y].number == temp.number)
            return;
        if (y > 0 && gbricks[x][y-1].number == temp.number)
            return;
        if (y < MWIDTH && gbricks[x-1][y].number == temp.number)
            return;

        wattron(mw.mainwin, COLOR_PAIR(0));
        mvwprintw(mw.mainwin, HEIGHT/2, WIDTH/2-4, "You Lose!");
        wattroff(mw.mainwin, COLOR_PAIR(0));
        wrefresh(mw.mainwin);
        sleep(2);
        endwin();
        exit(0);
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
            this->check_finish();
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

void n2048::undo() {
    int i, j;
    for (i = 0; i < MHEIGHT; i++) {
        for (j = 0; j < MWIDTH; j++) {
            gbricks[i][j].number = numbers_old[i][j];
        }
    }
    this->main_refresh();
}

void n2048::main_refresh() {
    endwin();
    for (int i = 0; i < MHEIGHT; i++) {
        for (int j = 0; j < MWIDTH; j++) {
            wattron(mw.mainwin, COLOR_PAIR(gbricks[i][j].number));
            for (int k = 1; k < MBRICKWIDTH; k++)
                for(int l = 1; l < MBRICKWIDTH*2-1; l++)
                    mvwprintw(mw.mainwin, i*MBRICKWIDTH+k, j*2*MBRICKWIDTH+l, " ");
            if (gbricks[i][j].number != 0)
                mvwprintw(mw.mainwin, i*MBRICKWIDTH+MBRICKWIDTH/2, (j*2+1)*MBRICKWIDTH-1, "%d", gbricks[i][j].number);
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

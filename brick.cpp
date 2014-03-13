#include "brick.h"

brick::brick(int col, int row, int num) {
    x = col;
    y = row;
    number = num;
}

brick::brick() {
    x = 0;
    y = 0;
    number = 0;
}

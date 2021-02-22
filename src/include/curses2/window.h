#ifndef CURSES_2_WINDOW_H
#define CURSES_2_WINDOW_H

#include <curses.h>

WINDOW * createWindow(int width, int height, int x, int y){
    WINDOW *win = newwin(height, width, y, x);
    
    box(win, 0, 0);
    wrefresh(win);

    return win;
}

void refreshWindow(WINDOW *win){
    box(win, 0, 0);
    wrefresh(win);
}

void deleteWindow(WINDOW *win){
    wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
    delwin(win);
}

#endif
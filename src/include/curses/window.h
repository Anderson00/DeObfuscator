#ifndef WINDOW_H
#define WINDOW_H

#include <curses.h>
#include <panel.h>
#include "viewgroup.h"

class Window : public ViewGroup{
public:
    Window(int width, int height, int x = 0, int y = 0) : 
        ViewGroup(width, height, x, y)
    {
        this->initialize();
    }

    ~Window(){
        wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	    wrefresh(win);
        delwin(this->win);
    }

    void move(int x, int y);
    void resize(int x, int y);  
    void background(chtype pair);
    void refresh() override {
        wrefresh(this->win);
    }


private:
    void initialize();

private:
    WINDOW *win;
    bool isInitialized = false;
};

#endif
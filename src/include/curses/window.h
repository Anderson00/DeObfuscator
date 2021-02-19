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

    void visible(bool visible){
        this->visible_val = visible;
        if(this->visible_val){
            this->refresh();
        }else{
            this->clear();
        }
    }

    void border(bool border){
        this->border_val = border;
    }

    void move(int x, int y) override;
    void resize(int x, int y);  
    void background(chtype pair);
    void refresh() override {
        if(this->visible_val){
            if(this->border_val)
                wborder(this->win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
            wrefresh(this->win);
            ViewGroup::refresh();
        }
    }

    void clear() override{
        wborder(win, ' ', ' ', ' ',' ',' ',' ',' ',' ');
	    wrefresh(win);
        //refresh();
    }

    void print(const char *str){
        wmove(this->win, this->height()/2, this->width()/2 - strlen(str)/2);
        wprintw(this->win, str);
        wrefresh(this->win);
    }

protected:
    WINDOW * winInstance(){return this->win;}

private:
    void initialize();

private:
    WINDOW *win;
    bool isInitialized = false;
    bool visible_val = false;
    bool border_val = true;
};

#endif
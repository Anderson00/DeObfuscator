
#include "window.h"
#include <iostream>

void Window::initialize(){
    if(!this->isInitialized){
        this->win = newwin(this->height(), this->width(), this->y(), this->x());
        wborder(this->win, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE, ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
	    wrefresh(this->win);
        this->isInitialized = true;
    }
}
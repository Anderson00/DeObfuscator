
#include "window.h"
#include <iostream>

void Window::initialize(){
    if(!this->isInitialized){
        this->win = newwin(this->height(), this->width(), this->y(), this->x());
        this->isInitialized = true;
    }
}

void Window::move(int x, int y){
    this->clear();
    ViewGroup::move(x, y);
    ViewGroup::refresh();
    if(this->parent() != nullptr){

        x = x + this->parent()->x();

        y = y + this->parent()->y();
        if(this->x() == x && this->y() == y)
            return;
    }
    
        this->x(x);
        this->y(y);
    
    

    std::cout << "Window::Move: " << x << " | " << y << std::endl; 
    mvwin(this->win, y, x);
    this->refresh();
}
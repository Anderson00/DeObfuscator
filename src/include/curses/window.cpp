
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
    if(this->parent() != nullptr){
        this->x(x + this->parent()->x());
        this->y(y + this->parent()->y());
    }
    else{
        this->x(x);
        this->y(y);
    }
    

    std::cout << "Window::Move: " << this->x() << " | " << this->y() << std::endl; 
    mvwin(this->win, this->y(), this->x());
    ViewGroup::refresh();
    this->refresh();    
}
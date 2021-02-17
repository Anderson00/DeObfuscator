#ifndef VIEW_H
#define VIEW_H

#include <iostream>

class View{
public:
    View(int width, int height, int x, int y) :
        width_val(width), 
        height_val(height), 
        x_val(x), 
        y_val(y){ }

    int& width(){return this->width_val;}
    int& height(){return this->height_val;}
    int& x(){return this->x_val;}
    int& y(){return this->y_val;}

    const int x() const {return x_val;}
    const int y() const {return x_val;}
    const int width() const {return this->width_val;}
    const int height() const {return this->height_val;}

    virtual void refresh() = 0;
private:
    int width_val,  height_val;
    int x_val, y_val;
};

#endif
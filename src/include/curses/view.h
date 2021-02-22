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

    virtual void move(int x, int y) = 0;

    int width(){return this->width_val;}
    int width(int width){return this->width_val;}
    int height(){return this->height_val;}
    int height(int height){return this->height_val;}
    int x(){return this->x_val;}
    int x(int x){
        //normalizeViewX(x);
        this->x_val = x;
        return this->x_val;
    }
    int y(){return this->y_val;}
    int y(int y){
        //normalizeViewY(y);
        this->y_val = y;
        return this->y_val;
    }

    View* parent(){return this->parent_val;}
    View* parent(View * parent){
        this->parent_val = parent;
        this->clear();
        this->move(this->x_val, this->y_val);
        this->parent()->refresh();
        //normalizeViewInParent();
        return this->parent_val;
    }

    const int x() const {return x_val;}
    const int y() const {return y_val;}
    const int width() const {return this->width_val;}
    const int height() const {return this->height_val;}

    virtual void refresh() = 0;
    virtual void clear() = 0;

    bool operator ==(View *view){return view == this;}


protected:
    int& maxWidth(){return this->maxWidth_val;}
    int& maxHeight(){return this->maxHeight_val;}
    int& maxX(){return this->maxX_val;}
    int& maxY(){return this->maxY_val;}

    const int maxX() const {return maxX_val;}
    const int maxY() const {return maxY_val;}
    const int maxWidth() const {return this->maxWidth_val;}
    const int maxHeight() const {return this->maxHeight_val;}

private:
    int width_val,  height_val;
    int maxWidth_val,  maxHeight_val;
    int x_val, y_val;
    int maxX_val, maxY_val;

    View * parent_val = nullptr;
};

#endif
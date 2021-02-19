#ifndef BORDER_PANE_H
#define BORDER_PANE_H

#include "window.h"
#include <curses.h>

class BorderPane : public Window{
public:
    BorderPane(int width, int height, int x, int y)
        : Window(width, height, x, y){
            this->visible(true);
            this->refresh();
            

            this->addChild(new Window(width-2, 4, 1 , 1));//Top
            this->addChild(new Window(((width-2)-width*0.2) - width*0.2, height - 6, width*0.2 + 1, 5));//Center
            this->addChild(new Window(width*0.2, height - 6, 1 , 5));//Left
            this->addChild(new Window(width*0.2, height - 6, ((width-2)-width*0.2) + 1, 5));//Right
            this->top()->visible(true);
            this->center()->visible(true);
            this->left()->visible(true);
            this->right()->visible(true);
            

            this->refresh();

            this->top()->print("Top");
            this->center()->print("Center");
            this->left()->print("Left");
            this->right()->print("Right");
        }
    
    Window* top();
    Window* top(Window * child);

    Window* center();
    Window* center(Window * child);

    Window* left();
    Window* left(Window * child);

    Window* right();
    Window* right(Window * child);

private:
};

#endif
#ifndef VIEW_GROUP_H
#define VIEW_GROUP_H

#include <vector>
#include "view.h"

class ViewGroup : public View{
public:
    ViewGroup(int width = 0, int height = 0, int x = 0, int y = 0)
        : View(width, height, x, y){}

    View* addChild(View * view);
    View* removeChild(View * view);
    View* removeChild(int index);
    int childrenCount(){return this->children.size();}

private:
    std::vector<View*> children;
};

#endif
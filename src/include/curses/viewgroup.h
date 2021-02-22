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
    std::vector<View*> children(){return this->children_val;}
    int childrenCount(){return this->children_val.size();}
    
    void refresh() override;
    virtual void move(int x, int y) override;
    void clear() override;

private:
    void normalizeChild(View* view);

private:
    std::vector<View*> children_val;
};

#endif
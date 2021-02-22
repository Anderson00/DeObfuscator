#include "viewgroup.h"

#include <math.h>

View* ViewGroup::addChild(View * view){
    this->children_val.push_back(view);
    view->parent(this);
    ViewGroup::refresh();
    return view;
}

View* ViewGroup::removeChild(View * view){
    for(auto it = this->children_val.begin(); it != this->children_val.end(); ++it){
        if(*it == view){
            this->children_val.erase(it);
            return view;
        }
    }
    return nullptr;
}

View* ViewGroup::removeChild(int index){
    return *(this->children_val.erase(this->children_val.begin() + index));
}

void ViewGroup::refresh(){
    std::cout << "Cildren count: " << this->children_val.size() << std::endl;
    for(auto it = this->children_val.begin(); it != this->children_val.end(); ++it){
        //(*it)->clear();
        //(*it)->move(abs((*it)->x() - (*it)->parent()->x()), abs((*it)->y() - (*it)->parent()->y()));
        (*it)->move((*it)->x(), (*it)->y());
        (*it)->refresh();        
        
    }
}

void ViewGroup::move(int x, int y){
    std::cout << "Cildren Move: " << this->children_val.size() << std::endl;
    for(auto it = this->children_val.begin(); it != this->children_val.end(); ++it){
        //(*it)->move(abs((*it)->x() - (*it)->parent()->x()), abs((*it)->y() - (*it)->parent()->y()));
        (*it)->move((*it)->x(), (*it)->y());     
        (*it)->refresh();  
    }
}

void ViewGroup::clear(){
    for(auto it = this->children_val.begin(); it != this->children_val.end(); ++it){
        (*it)->clear();
    }
}
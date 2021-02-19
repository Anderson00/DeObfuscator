#ifndef TEXT_H
#define TEXT_H

#include <curses.h>
#include <string>

class Text : public Window{
public:
    Text(std::string text, int x, int y) : text_val(text), Window(text.size()+4, 1, x, y){
        this->border(false);
        this->visible(true);
    }

    void refresh() override {
        std::cout << "Print" << std::endl;
        this->print(this->text_val.c_str());
        Window::refresh();
    }

    std::string value(){return this-> text_val;}
private:
    std::string text_val;
};

#endif
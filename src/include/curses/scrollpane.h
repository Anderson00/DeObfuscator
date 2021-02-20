#ifndef SCROLL_PANE_H
#define SCROLL_PANE_H

#include "window.h"
#include <vector>
#include <string.h>

class ScrollPane : public Window {
public:
    ScrollPane(int width, int height, int x, int y)
        :Window(width, height, x, y){
        this->border(true);
        

        scrollok(this->winInstance(), TRUE);
        
        this->visible(true);

    }

    void print(){
        int y = 0, x = 0;
        getyx(this->winInstance(), y, x);
        std::cout << "Scroll getyx: " << x << " | " << y << std::endl;
        for(int i = 0; i < 30; i++){
            //wmove(this->winInstance(), i + 1, 2);
            std::string str("Testando: ");
            str.append(std::to_string(i));
            str.append("\n");
            data.push_back(str);
            wprintw(this->winInstance(), str.c_str());
            //wmove(this->winInstance(), i + 1, 2);
        }
        
        
        
    }

    void scroll(int n){
        int y = 0, x = 0;
        getyx(this->winInstance(), y, x);
        std::cout << "Scroll getyx: " << x << " | " << y << std::endl;
        std::cout << "Scroll: " << getcurx(this->winInstance()) << " | " << getcury(this->winInstance()) << std::endl;
        wscrl(this->winInstance(), n);
        getyx(this->winInstance(), y, x);
        std::cout << "Scroll getyx: " << x << " | " << y << std::endl;
        std::cout << "Scroll: " << getcurx(this->winInstance()) << " | " << getcury(this->winInstance()) << std::endl;
        //for(int i = 0; i)
    }

private:
    std::vector<std::string> data;
};

#endif
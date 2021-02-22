#ifndef CURSES_SINGLETON_H
#define CURSES_SINGLETON_H

#include <curses.h>
#include <cxxopts.hpp>

class CursesSingleton{
public:
    static CursesSingleton * instance(){
        /*if(CursesSingleton::instanceCurses == nullptr){
            CursesSingleton::instanceCurses = new CursesSingleton();
        }*/
        static CursesSingleton* inst = new CursesSingleton();
        return inst;
    }


    ~CursesSingleton(){
        wclear(this->scrwin);
        endwin();
        this->scrwin = nullptr;
    }


private:
    CursesSingleton(){
        this->scrwin = initscr();        
        start_color();
        init_pair(1, COLOR_RED, COLOR_BLACK);
        has_colors();
        can_change_color();
        refresh();
        
    }

    

    WINDOW *scrwin;

    static CursesSingleton * instanceCurses;
};

#endif
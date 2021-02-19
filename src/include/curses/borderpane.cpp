#include "borderpane.h"

Window* BorderPane::top(){
    return (Window*)this->children()[0];
}

Window* BorderPane::top(Window * view){
    return (Window*)this->children()[0];
}

Window* BorderPane::center(){
    return (Window*)this->children()[1];
}

Window* BorderPane::left(){
    return (Window*)this->children()[2];
}

Window* BorderPane::right(){
    return (Window*)this->children()[3];
}
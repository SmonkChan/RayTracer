#include <math.h>
#include <stdexcept>

using namespace std;
#include "color.h"

color::color(){
    red = 0;
    green = 0;
    blue = 0;
}
//Constructor takes 3 doubles that must be between 0 and 1 inclusive
//If not it will throw an exception
color::color(double r, double g, double b){
    if((r>1)||(r<0)||(g>1)||(g<0)||(b>1)||(b<0)){
        throw invalid_argument("recieved color value greater than 1 or less than 0");
    }
    red = r;
    green = g;
    blue = b;
}
color::color(const color& color2){
    *this = color2;
}
color::~color(){}

void color::operator=(const color& color2){
    this->red = color2.red;
    this->blue = color2.blue;
    this->green = color2.green;
}

//Creates a string based on the Char data to easily print
string color::getString(){
    int r = (int)(red*255);
    int g = (int)(green*255);
    int b = (int)(blue*255);
    if(r < 0){r = 0;}
    if(g < 0){g = 0;}
    if(b < 0){b = 0;}
    return to_string(r).append(" ").append(to_string(g)).append(" ").append(to_string(b));
}
#include <math.h>
#include <stdexcept>
#include <iostream>

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
    if(r > 1){
        std::cout << "red value = " << r << std::endl;
        throw invalid_argument("recieved red color value greater than 1");
    } else if(r < 0){
        std::cout << "red value = " << r << std::endl;
        throw invalid_argument("recieved red color value less than 0");
    } else if(b > 1){
        std::cout << "blue value = " << b << std::endl;
        throw invalid_argument("recieved blue color value greater than 1");
    } else if(b < 0){
        std::cout << "blue value = " << b << std::endl;
        throw invalid_argument("recieved blue color value less than 0");
    } else if(g > 1){
        std::cout << "green value = " << g << std::endl;
        throw invalid_argument("recieved green color value greater than 1");
    } else if(g < 0){
        std::cout << "green value = " << g << std::endl;
        throw invalid_argument("recieved green color value less than 0");
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
    return to_string(r).append(" ").append(to_string(g)).append(" ").append(to_string(b));
}
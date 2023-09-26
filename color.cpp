#include <math.h>
#include <stdexcept>

using namespace std;
#include "color.h"

color::color(){
    rgbChar = make_tuple(0,0,0);
}
//Constructor takes 3 doubles that must be between 0 and 1 inclusive
//If not it will throw an exception
color::color(double r, double g, double b){
    if((r>1)||(r<0)||(g>1)||(g<0)||(b>1)||(b<0)){
        throw invalid_argument("recieved color value greater than 1 or less than 0");
    }
    rgbChar = make_tuple((unsigned char) (r*255), (unsigned char) (g*255), (unsigned char) (b*255));
}
color::color(unsigned char r, unsigned char g, unsigned char b){
    rgbChar = make_tuple(r, g, b);
}
color::color(const color& color2){
    *this = color2;
}
color::~color(){}

void color::operator=(const color& color2){
    this->rgbChar = color2.rgbChar;
}

//Creates a string based on the Char data to easily print
string color::getString(){
    string r = to_string((int) get<0>(rgbChar));
    string g = to_string((int) get<1>(rgbChar));
    string b = to_string((int) get<2>(rgbChar));
    return r.append(" ").append(g).append(" ").append(b);
}
#ifndef COLOR_H
#define COLOR_H
#include <tuple>
#include <string>
class color 
{
private:
    double red;
    double green;
    double blue;
public:
    //Constructors
    color();
    color(double r, double g, double b);
    color(unsigned char r, unsigned char g, unsigned char b);
    color(const color& color2);
    ~color();
    
    double getRed(){return red;}
    double getGreen(){return green;}
    double getBlue(){return blue;}

    void operator=(const color& color2);

    //Outputs the char data as a string to make extreamly easy to print
    std::string getString();
};
#endif
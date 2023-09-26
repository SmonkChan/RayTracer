#ifndef COLOR_H
#define COLOR_H
#include <tuple>
#include <string>
class color 
{
private:
    std::tuple<unsigned char, unsigned char, unsigned char> rgbChar;
public:
    //Constructors
    color();
    color(double r, double g, double b);
    color(unsigned char r, unsigned char g, unsigned char b);
    color(const color& color2);
    ~color();
    
    void operator=(const color& color2);

    //Outputs the char data as a string to make extreamly easy to print
    std::string getString();
};
#endif
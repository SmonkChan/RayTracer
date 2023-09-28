#include <math.h>

using namespace std;
#include "point.h"

//constructors and destructors
point3D::point3D(double Px, double Py, double Pz)
{
    p[0] = Px;
    p[1] = Py;
    p[2] = Pz;
}
point3D::point3D()
{  
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
}
point3D::point3D(const point3D& point2){
    *this = point2;
}
point3D::~point3D(){}

//getters
double point3D::getX(){return p[0];}
double point3D::getY(){return p[1];}
double point3D::getZ(){return p[2];}

//Distance between two points
double point3D::distance(point3D point2){
    return sqrt(pow(point2.getX() - p[0], 2) + pow(point2.getY() - p[1], 2) + pow(point2.getZ() - p[2], 2));
}

string point3D::printPoint(){
    string s;
    return s.append("(").append(to_string(p[0])).append(", ").append(to_string(p[1])).append(", ").append(to_string(p[2])).append(")");
}

//Method for setting one point equal to another
void point3D::operator=(const point3D& point2){
    this->p[0] = point2.p[0];
    this->p[1] = point2.p[1];
    this->p[2] = point2.p[2];
}

//Method for adding a vector to a point to get another point
point3D point3D::operator+(vector3D vector){
    double x = this->p[0] + vector.getX();
    double y = this->p[1] + vector.getY();
    double z = this->p[2] + vector.getZ();
    return point3D(x, y, z);
}

//Method for subtracting a point from a point to get a vector
vector3D point3D::operator-(point3D point2){
    double x = this->p[0]-point2.p[0];
    double y = this->p[1]-point2.p[1];
    double z = this->p[2]-point2.p[2];
    return vector3D(x, y, z);
}
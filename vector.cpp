#include <math.h>
#include <iostream>

using namespace std;
#include "vector.h"

//Constructors and destructors
vector3D::vector3D(){
    v[0] = 0;
    v[1] = 0;
    v[2] = 0;
}
vector3D::vector3D(double x, double y, double z){
    v[0] = x;
    v[1] = y;
    v[2] = z;
}
vector3D::vector3D(const vector3D& vector2){
    *this = vector2;
}
vector3D::~vector3D(){}

void vector3D::operator=(const vector3D& vector2){
    this->v[0] = vector2.v[0];
    this->v[1] = vector2.v[1];
    this->v[2] = vector2.v[2];
}

//Getters and setters
double vector3D::getX(){return v[0];}
double vector3D::getY(){return v[1];}
double vector3D::getZ(){return v[2];}

vector3D vector3D::operator+(vector3D v2){
    double x = v[0]+v2.getX();
    double y = v[1]+v2.getY();
    double z = v[2]+v2.getZ();
    vector3D newVector(x,y,z);
    return newVector;
}

//Computes the cross product of the vector cross another vector
//Ex: vector1.crossProduct(vector2) = vector1 X vector2
vector3D vector3D::crossProduct(vector3D v2){
    double x = v[0];
    double y = v[1];
    double z = v[2];
    double newX = y*v2.getZ() - z*v2.getY();
    double newY = z*v2.getX() - x*v2.getZ();
    double newZ = x*v2.getY() - y*v2.getX();
    return vector3D(newX, newY, newZ);
}

//Computes the dot product between the vector and a second vector
double vector3D::dotProduct(vector3D v2){
    return v[0]*v2.getX() + v[1]*v2.getY() + v[2]*v2.getZ();
}

//Returns the magnitude of the vector
double vector3D::magnitude(){
    return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
}

//Updates the vector by multiplying it by a scalar
vector3D vector3D::multiplyByScalar(double scalar){
    double x = v[0] * scalar;
    double y = v[1] * scalar;
    double z = v[2] * scalar;
    vector3D newVector(x, y, z);
    return newVector;
}

//Updates the vector with the normal vector
void vector3D::normalize(){
    double mag = magnitude();
    if(mag == 0){
        std::cout << "WARNING: given vector equals 0" << std::endl;
        return;
    }
    v[0] /= mag;
    v[1] /= mag;
    v[2] /= mag;
}

//Outputs a vector that is the normal vector of the input vector
vector3D vector3D::getNormalVector(){
    double mag = magnitude();
    if(mag == 0){return vector3D(v[0], v[1], v[2]);}
    return vector3D(v[0]/mag, v[1]/mag, v[2]/mag);
}

//Checks if the vector is a null vector
bool vector3D::isNullVector(){
    return ((v[0] == 0) && (v[1] == 0) && (v[2] == 0));
}

//Checks if two vectors are colinear;
bool vector3D::isColinear(vector3D v2){
    return crossProduct(v2).isNullVector();
}

//Returns a string of the vector
//used for debugging
string vector3D::printVector(){
    string s;
    return s.append("<").append(to_string(v[0])).append(", ").append(to_string(v[1])).append(", ").append(to_string(v[2])).append(">");
}
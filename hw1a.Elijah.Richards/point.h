#ifndef POINT_H
#define POINT_H
#include<tuple>
#include<string>
#include"vector.h"
//Class used to define a point in 3D space
//Takes 3 doubles and stores them for future use
//Stores the values in an array for ease of use
class point3D
{
private:
    double p[3];
public:
    point3D(double Px, double Py, double Pz);
    point3D();
    point3D(const point3D& point2);
    ~point3D();

    double getX();
    double getY();
    double getZ();

    double distance(point3D point2);
    std::string printPoint();

    void operator=(const point3D& point2);
    point3D operator+(vector3D vector);
    vector3D operator-(point3D point2);
};
#endif 
#ifndef SHAPE_H
#define SHAPE_H
#include "point.h"
#include "color.h"
#include "vector.h"

//This is used to define what type of shape the shape class is created from
//The other shape objects are all inherited off of this class

class shape
{
    protected:
    color material; //All shapes should have a material color

    public:
    shape();
    shape(const shape& shape2);
    color getColor();
    virtual double intersects(point3D rayOrigin, vector3D ray) = 0;
    virtual std::string printShape();

};

//The sphere class
class sphere : public shape
{
    private:
    point3D center;
    double radius;

    public:
    sphere();
    sphere(point3D c, double r, color m);
    void operator=(const sphere &sphere2);
    double intersects(point3D rayOrigin, vector3D ray);
    std::string printShape();
};

//The cylinder class
class cylinder : public shape
{
    private:
    point3D center;
    vector3D upVector;
    double radius;
    double length;

    public:
    cylinder();
    cylinder(point3D c, vector3D v, double r, double l, color m);
    void operator=(const cylinder &shape2);
    double intersects(point3D rayOrigin, vector3D ray);
    std::string printShape();
};
#endif
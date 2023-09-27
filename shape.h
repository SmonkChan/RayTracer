#ifndef SHAPE_H
#define SHAPE_H
#include "point.h"
#include "color.h"
#include "vector.h"
#include "material.h"
#include "lightsource.h"

//This is used to define what type of shape the shape class is created from
//The other shape objects are all inherited off of this class

class shape
{
    protected:
    material* texture; //All shapes should have a material color

    public:
    shape();
    shape(const shape& shape2);
    material* getColor();
    virtual double intersects(point3D rayOrigin, vector3D ray) = 0;
    virtual std::string printShape();
    virtual vector3D findNormal(point3D p) = 0;
};

//The sphere class
class sphere : public shape
{
    private:
    point3D center;
    double radius;

    public:
    sphere();
    sphere(point3D c, double r, material* m);
    void operator=(const sphere &sphere2);
    double intersects(point3D rayOrigin, vector3D ray);
    std::string printShape();
    virtual vector3D findNormal(point3D p);
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
    cylinder(point3D c, vector3D v, double r, double l, material* m);
    void operator=(const cylinder &shape2);
    double intersects(point3D rayOrigin, vector3D ray);
    std::string printShape();
    virtual vector3D findNormal(point3D p);
};
#endif
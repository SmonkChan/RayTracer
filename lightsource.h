#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include <math.h>
#include "vector.h"
#include "point.h"
#include "color.h"
class lightsource
{
    public:
    virtual vector3D getLightDirection(point3D) = 0;
    virtual double distanceFromLight(point3D) = 0;
    virtual color getLightColor(double distance) = 0;
};

class directional_light : public lightsource
{
    private:
    vector3D lightDirection;
    color lightColor;
    public:
    directional_light(vector3D v, color c);
    vector3D getLightDirection(point3D p);
    double distanceFromLight(point3D p);
    color getLightColor(double distance){return lightColor;}
};

class point_light : public lightsource
{
    private:
    point3D lightOrigin;
    color lightColor;
    public:
    point_light(){}
    point_light(point3D p, color c);
    vector3D getLightDirection(point3D p);
    double distanceFromLight(point3D p);
    virtual color getLightColor(double distance){return lightColor;}
};

class attenuated_light : public point_light
{
    private:
    point3D lightOrigin;
    color lightColor;
    double c1;
    double c2;
    double c3;
    public:
    attenuated_light(point3D p, color c, double c1=1, double c2=1, double c3=1);
    color getLightColor(double distance);
};

#endif
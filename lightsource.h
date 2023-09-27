#ifndef LIGHTSOURCE_H
#define LIGHTSOURCE_H

#include "vector.h"
#include "point.h"
#include "color.h"
class lightsource
{
    public:
    virtual vector3D getLightDirection(point3D) = 0;
};

class directional_light : public lightsource
{
    private:
    vector3D lightDirection;
    color lightColor;
    public:
    directional_light(vector3D v, color c);
    vector3D getLightDirection(point3D p);
};

class point_light : public lightsource
{
    private:
    point3D lightOrigin;
    color lightColor;
    public:
    point_light(point3D p, color c);
    vector3D getLightDirection(point3D p);
};

class spot_light : public lightsource
{

};

#endif
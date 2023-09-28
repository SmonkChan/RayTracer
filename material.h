#ifndef MATERIAL_H
#define MATERIAL_H

#include <math.h>
#include <string.h>
#include "color.h"
#include "point.h"
#include "lightsource.h"

class material
{
    private:
    protected:
    color baseColor;
    public:
    material(color base = color());
    virtual color calculateColor();
    virtual color calculateColor(point3D rayOrigin, point3D intersection, lightsource** allLights, color* lightShadow, vector3D* lightDirection, int numLights, vector3D normal);
    virtual int materialType(){return 0;}
};

class Phong_material : public material 
{
    private:
    color specularHighlight;
    double specularA;
    double specularD;
    double specularS;
    double specularExponent;

    public:
    Phong_material(color baseColor, color highlight, double ka, double kd, double ks, double n);
    color calculateColor(point3D rayOrigin, point3D intersection, lightsource** allLights, color* lightShadow, vector3D* lightDirection, int numLights, vector3D normal);
    int materialType(){return 1;}
};

#endif
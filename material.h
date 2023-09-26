#ifndef MATERIAL_H
#define MATERIAL_H

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
    color calculateColor(point3D intersection, lightsource light);
};

#endif
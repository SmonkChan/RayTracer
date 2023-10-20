#ifndef MATERIAL_H
#define MATERIAL_H

#include <math.h>
#include <string.h>
#include "color.h"
#include "point.h"
#include "lightsource.h"
#include "raycaster.h"
#include "scene.h"

class material
{
    private:
    protected:
    color baseColor;
    public:
    material(color base = color());
    virtual color calculateColor(point3D rayOrigin, point3D intersection, vector3D normal, scene environment);
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
    color calculateColor(point3D rayOrigin, point3D intersection, vector3D normal, scene environment);
};

#endif
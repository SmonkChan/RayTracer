#ifndef MATERIAL_H
#define MATERIAL_H

#include <math.h>
#include <string.h>
#include <iostream>
#include "color.h"
#include "point.h"
#include "lightsource.h"
#include "scene.h"
#include "raycaster.h"

class material
{
    public:
    virtual color calculateColor(point3D rayOrigin, point3D intersection, shape* intersectedShape, scene* environment) = 0;
    virtual void printInfo() = 0;
    virtual ~material(){}
    virtual double getIndexOfRefraction() = 0;
    virtual double getFresnel() = 0;
    virtual double getSpecular() = 0;
    virtual double getOpacity() = 0;
};

class flat_material : public material 
{
    private:
    color baseColor;
    public:
    flat_material(color base){baseColor = base;}
    virtual color calculateColor(point3D rayOrigin, point3D intersection, shape* intersectedShape, scene* environment){return baseColor;}
    void printInfo();
    virtual ~flat_material(){}
    double getIndexOfRefraction(){return 1;}
    double getFresnel(){return 0;}
    double getSpecular(){return 0;}
    double getOpacity(){return 1;}
};

class Phong_material : public material 
{
    private:
    color baseColor;
    protected:
    color phong_illumination(color colorAtPoint, point3D rayOrigin, point3D intersection, shape* intersectedShape, scene* environment);

    public:
    color specularHighlight;
    double specularA;
    double specularD;
    double specularS;
    double specularExponent;
    double opacity;
    double indexOfRefraction;
    Phong_material();
    Phong_material(color baseColor, color highlight, double ka, double kd, double ks, double n);
    Phong_material(color baseColor, color highlight, double ka, double kd, double ks, double n, double alpha, double eta);
    virtual color calculateColor(point3D rayOrigin, point3D intersection, shape* intersectedShape, scene* environment);
    virtual void printInfo();
    virtual ~Phong_material(){}
    virtual double getIndexOfRefraction();
    virtual double getFresnel();
    double getSpecular(){return specularS;}
    double getOpacity(){return opacity;}
};

class texture_material : public Phong_material
{
    private:
    int imWidth;
    int imHeight;

    public:
    color* textureData;
    texture_material(int width, int height, Phong_material* material_properties);
    ~texture_material();
    color calculateColor(point3D rayOrigin, point3D intersection, shape* intersectedShape, scene* environment);
    void printInfo();
};

#endif
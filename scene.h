#ifndef SCENE_H
#define SCENE_H

#include "shape.h"
#include "color.h"
#include "material.h"
#include "lightsource.h"

class scene {
    private:
    int shapeListSize;
    int matListSize;
    int lightListSize;

    public:
    color bkgcolor;
    shape** allShapesList;
    int numShapes;
    material** allMaterialsList;
    int numMats;
    lightsource** allLights;
    int numLights;

    scene();
    ~scene();
    scene(const scene& copyScene);
    void operator=(const scene& copyScene);
    void addShape(shape*);
    void addLight(lightsource*);
    void addMaterial(material*);
    void setBackgroundColor(color b){bkgcolor = b;}
};
#endif
#ifndef SCENE_H
#define SCENE_H

#include "color.h"
class shape;
class material;
class lightsource;

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
    void addShape(shape* newShape);
    void addLight(lightsource* newLight);
    void addMaterial(material* newMaterial);
    void setBackgroundColor(color b){bkgcolor = b;}
};
#endif
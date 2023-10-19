#ifndef SCENE_H
#define SCENE_H

#include "shape.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "material.h"
#include "lightsource.h"

class scene {
    color bkgcolor;
    shape** allShapesList;
    int shapeListSize;
    int numShapes;
    material** allMaterialsList;
    int matListSize;
    int numMats;
    material* currMaterial;
    lightsource** allLights;
    int lightListSize;
    int numLights;


    public:
    scene();
    scene(const scene& copyScene);
    ~scene();
    void operator=(const scene& copyScene);
    void addShape(shape*);
    void addLight(lightsource*);
    void addMaterial(material*);

    void setBackgroundColor(color b){bkgcolor = b;}

    material* getCurrMaterial(){return currMaterial;}
};

class camera{
    point3D eye;
    vector3D viewdir;
    vector3D updir;
    double fov;
    int imsizeWidth;
    int imsizeHeight;
    //These vectors are colinear as the orthogonal viewplane basis, but with length of one pixel
    vector3D vertPixelChange;
    vector3D horiPixelChange;
    //This vector points at the center of the bottom left pixel
    vector3D bottomVector;
    color* colorOut;
    void getViewplane();

    public:
    camera(point3D e, vector3D v, vector3D u, double f, int w, int h);
    camera(const camera& copyCamera);
    ~camera();
    void operator=(const camera& copyCamera);
    int getSceneWidth(){return imsizeWidth;}
    int getSceneHeight(){return imsizeHeight;}
    bool isInvalid();

};
#endif
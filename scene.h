#ifndef SCENE_H
#define SCENE_H

#include "color.h"
#include "triangle.h"
class shape;
class material;
class lightsource;

class scene {
    private:
    int shapeListSize;
    int matListSize;
    int lightListSize;
    int vertexListSize;
    int normalListSize;

    public:
    color bkgcolor;
    shape** allShapesList;
    int numShapes;
    material** allMaterialsList;
    int numMats;
    lightsource** allLights;
    int numLights;
    point3D** allVertexes;
    int numVerts;
    vector3D** allNorms;
    int numNorms;

    scene();
    ~scene();
    void addShape(shape* newShape);
    void addLight(lightsource* newLight);
    void addMaterial(material* newMaterial);
    void addVertex(point3D* newVertex);
    void addFace(int vert1, int vert2, int vert3);
    void addNormal(vector3D* newNormal);
    void addFace(int vert1, int norm1, int vert2, int norm2, int vert3, int norm3);
    void setBackgroundColor(color b){bkgcolor = b;}
};
#endif
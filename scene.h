#ifndef SCENE_H
#define SCENE_H

#include "color.h"
#include "point.h"
#include "vector.h"
class shape;
class material;
class lightsource;
struct uvCord;

class scene {
    private:
    int shapeListSize;
    int matListSize;
    int lightListSize;
    int vertexListSize;
    int normalListSize;
    int textureCordListSize;

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
    uvCord** allTextureCords;
    int numCords;

    scene();
    ~scene();
    void addShape(shape* newShape);
    void addLight(lightsource* newLight);
    void addMaterial(material* newMaterial);
    void addVertex(point3D* newVertex);
    void addNormal(vector3D* newNormal);
    void addTextureCord(uvCord* newCord);
    void addFlatFace(int* indecies, material* mat);
    void addTexturedFlatFace(int* indecies, material* mat);
    void addSmoothFace(int* indecies, material* mat);
    void addTexturedSmoothFace(int* indecies, material* mat);
    void setBackgroundColor(color b){bkgcolor = b;}
};
#endif
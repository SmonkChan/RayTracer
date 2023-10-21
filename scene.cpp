#include "scene.h"
#include "shape.h"
#include "material.h"
#include "lightsource.h"

scene::scene(){
    shapeListSize = 4;
    numShapes = 0;
    allShapesList = new shape*[shapeListSize];

    matListSize = 4;
    numMats = 0;
    allMaterialsList = new material*[matListSize];

    lightListSize = 4;
    numLights = 0;
    allLights = new lightsource*[lightListSize];

    vertexListSize = 4;
    numVerts = 0;
    allVertexes = new point3D*[vertexListSize];

    normalListSize = 4;
    numNorms = 0;
    allNorms = new vector3D*[normalListSize];

    bkgcolor = color(0,0,0);
}

scene::~scene(){
    for(int i = 0; i > numShapes; i++){
        delete allShapesList[i];
    } 
    delete[] allShapesList;
    for(int i = 0; i < numMats; i++){
        delete allMaterialsList[i];
    }
    delete[] allMaterialsList;
    for(int i = 0; i < numLights; i++){
        delete allLights[i];
    }
    delete[] allLights;
    for(int i = 0; i < numVerts; i++){
        delete allVertexes[i];
    }
    delete[] allVertexes;
    for(int i = 0; i < numNorms; i++){
        delete allNorms[i];
    }
    delete[] allNorms;
}

void scene::addShape(shape* newShape){
    if(numShapes >= shapeListSize){
        shapeListSize *= 2;
        shape** tempList = new shape*[shapeListSize];
        for(int i = 0; i < numShapes; i++){
            tempList[i] = allShapesList[i];
        }
        delete[] allShapesList;
        allShapesList = tempList;
    }
    allShapesList[numShapes] = newShape;
    numShapes++;
}

void scene::addLight(lightsource* newLight){
    if(numLights == lightListSize){
        lightListSize *= 2;
        lightsource** tempList = new lightsource*[lightListSize];
        for(int i = 0; i < numLights; i++){
            tempList[i] = allLights[i];
        }
        delete[] allLights;
        allLights = tempList;
    }
    allLights[numLights] = newLight;
    numLights++;
}

void scene::addMaterial(material* newMaterial){
    if(numMats == matListSize){
        matListSize *= 2;
        material** tempList = new material*[matListSize];
        for(int i = 0; i < numMats; i++){
            tempList[i] = allMaterialsList[i];
        }
        delete[] allMaterialsList;
        allMaterialsList = tempList;
    }
    allMaterialsList[numMats] = newMaterial;
    numMats++;
}

void scene::addVertex(point3D* newVertex){
    if(numVerts == matListSize){
        vertexListSize *= 2;
        point3D** tempList = new point3D*[vertexListSize];
        for(int i = 0; i < numVerts; i++){
            tempList[i] = allVertexes[i];
        }
        delete[] allVertexes;
        allVertexes = tempList;
    }
    allVertexes[numVerts] = newVertex;
    numVerts++;
}

void scene::addNormal(vector3D* newNorm){
    if(numNorms == normalListSize){
        normalListSize *= 2;
        vector3D** tempList = new vector3D*[normalListSize];
        for(int i =0; i < numNorms; i++){
            tempList[i] = allNorms[i];
        }
        delete[] allNorms;
        allNorms = tempList;
    }
    allNorms[numNorms] = newNorm;
    numNorms++;
}

void scene::addFace(int vertex1, int vertex2, int vertex3){
    point3D* p1 = allVertexes[vertex1-1];
    point3D* p2 = allVertexes[vertex2-1];
    point3D* p3 = allVertexes[vertex3-1];
    addShape(new flatTriangle(p1, p2, p3));
}

void scene::addFace(int vert1, int norm1, int vert2, int norm2, int vert3, int norm3){
    point3D* p1 = allVertexes[vert1-1];
    point3D* p2 = allVertexes[vert2-1];
    point3D* p3 = allVertexes[vert3-1];
    vector3D* n1 = allNorms[norm1-1];
    vector3D* n2 = allNorms[norm2-1];
    vector3D* n3 = allNorms[norm3-1];
    addShape(new smoothTriangle(p1, n1, p2, n2, p3, n3));
}
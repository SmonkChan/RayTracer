#include <iostream>

#include "scene.h"
#include "shape.h"
#include "material.h"
#include "lightsource.h"
#include "triangle.h"

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

    textureCordListSize = 4;
    numCords = 0;
    allTextureCords = new uvCord*[textureCordListSize];

    bkgcolor = color(0,0,0);
}

scene::~scene(){
    for(int i = 0; i < numShapes; i++){
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
    for(int i = 0; i < numCords; i ++){
        delete allTextureCords[i];
    }
    delete[] allTextureCords;
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
    if(numVerts == vertexListSize){
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
    allNorms[numNorms]->normalize();
    numNorms++;
}

void scene::addTextureCord(uvCord* newCord){
    if(numCords == textureCordListSize){
        textureCordListSize *= 2;
        uvCord** tempList = new uvCord*[textureCordListSize];
        for(int i = 0; i < numCords; i++){
            tempList[i] = allTextureCords[i];
        }
        delete[] allTextureCords;
        allTextureCords = tempList;
    }
    allTextureCords[numCords] = newCord;
    numCords++;
}

void scene::addFlatFace(int* indecies, material* mat){
    point3D* p1 = allVertexes[indecies[0]-1];
    point3D* p2 = allVertexes[indecies[1]-1];
    point3D* p3 = allVertexes[indecies[2]-1];
    std::cout << "adding face. p1 = " << p1 << " p2 = " << p2 << " p3 = " << p3 << std::endl;
    shape* newTriangle = new flatTriangle(p1, p2, p3, mat);
    addShape(newTriangle);
}

void scene::addSmoothFace(int* indecies, material* mat){
    point3D* p1 = allVertexes[indecies[0]-1];
    point3D* p2 = allVertexes[indecies[3]-1];
    point3D* p3 = allVertexes[indecies[6]-1];
    vector3D* n1 = allNorms[indecies[2]-1];
    vector3D* n2 = allNorms[indecies[5]-1];
    vector3D* n3 = allNorms[indecies[8]-1];
    shape* newTriangle = new smoothTriangle(p1, n1, p2, n2, p3, n3, mat);
    addShape(newTriangle);
}

void scene::addTexturedFlatFace(int* indecies, material* mat){
    point3D* p1 = allVertexes[indecies[0]-1];
    point3D* p2 = allVertexes[indecies[2]-1];
    point3D* p3 = allVertexes[indecies[4]-1];
    uvCord* tp1 = allTextureCords[indecies[1]-1];
    uvCord* tp2 = allTextureCords[indecies[3]-1];
    uvCord* tp3 = allTextureCords[indecies[5]-1];
    shape* newTriangle = new flatTriangleTextured(p1, tp1, p2, tp2, p3, tp3, mat);
    addShape(newTriangle);
}

void scene::addTexturedSmoothFace(int* indecies, material* mat){
    point3D* p1 = allVertexes[indecies[0]-1];
    point3D* p2 = allVertexes[indecies[3]-1];
    point3D* p3 = allVertexes[indecies[6]-1];
    vector3D* n1 = allNorms[indecies[1]-1];
    vector3D* n2 = allNorms[indecies[4]-1];
    vector3D* n3 = allNorms[indecies[7]-1];
    uvCord* tp1 = allTextureCords[indecies[2]-1];
    uvCord* tp2 = allTextureCords[indecies[5]-1];
    uvCord* tp3 = allTextureCords[indecies[8]-1];
    shape* newTriangle = new smoothTriangleTextured(p1, tp1, n1, p2, tp2, n2, p3, tp3, n3, mat);
    addShape(newTriangle);
}

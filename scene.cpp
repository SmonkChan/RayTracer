#include "scene.h"
#include "shape.h"
#include "material.h"
#include "lightsource.h"

scene::scene(){
    shapeListSize = 4;
    numShapes = 0;
    allShapesList = new shape*[4];

    matListSize = 4;
    numMats = 0;
    allMaterialsList = new material*[4];

    lightListSize = 4;
    numLights = 0;
    allLights = new lightsource*[4];

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
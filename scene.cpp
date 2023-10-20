#include "scene.h"

scene::scene(){
    shapeListSize = 4;
    numShapes = 0;
    shape** allShapeList = new shape*[shapeListSize];

    int matlistSize = 4;
    int numMats = 0;
    allMaterialsList = new material*[matlistSize];

    int lightlistSize = 4;
    int numLights = 0;
    allLights = new lightsource*[lightListSize];

    bkgcolor = color(0,0,0);
}

scene::scene(const scene& copyScene){
    this->~scene();
    bkgcolor = copyScene.bkgcolor;
    shapeListSize = copyScene.shapeListSize;
    allShapesList = new shape*[shapeListSize];
    numShapes = copyScene.numShapes;
    for(int i =0; i < numShapes; i++){
        allShapesList[i] = copyScene.allShapesList[i];
    }
    matListSize = copyScene.matListSize;
    allMaterialsList = new material*[matListSize];
    numMats = copyScene.numMats;
    for(int i =0; i < numMats; i++){
        allMaterialsList[i] = copyScene.allMaterialsList[i];
    }
    lightListSize = copyScene.lightListSize;
    allLights = new lightsource*[shapeListSize];
    numLights = copyScene.numLights;
    for(int i =0; i < numLights; i++){
        allLights[i] = copyScene.allLights[i];
    }
}

void scene::operator=(const scene& copyScene){
    this->~scene();
    bkgcolor = copyScene.bkgcolor;
    shapeListSize = copyScene.shapeListSize;
    allShapesList = new shape*[shapeListSize];
    numShapes = copyScene.numShapes;
    for(int i =0; i < numShapes; i++){
        allShapesList[i] = copyScene.allShapesList[i];
    }
    matListSize = copyScene.matListSize;
    allMaterialsList = new material*[matListSize];
    numMats = copyScene.numMats;
    for(int i =0; i < numMats; i++){
        allMaterialsList[i] = copyScene.allMaterialsList[i];
    }
    lightListSize = copyScene.lightListSize;
    allLights = new lightsource*[shapeListSize];
    numLights = copyScene.numLights;
    for(int i =0; i < numLights; i++){
        allLights[i] = copyScene.allLights[i];
    }
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
    if(numShapes == shapeListSize){
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
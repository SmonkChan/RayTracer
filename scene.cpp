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
    currMaterial = newMaterial;
}



camera::camera(point3D e, vector3D v, vector3D u, double f, int w, int h){
    eye = e;
    viewdir = v;
    updir = u;
    fov = f;
    imsizeWidth = w;
    imsizeHeight = h;
    getViewplane();
}

camera::camera(const camera& copyCamera){
    eye = copyCamera.eye;
    viewdir = copyCamera.viewdir;
    updir = copyCamera.updir;
    fov = copyCamera.fov;
    imsizeWidth = copyCamera.imsizeWidth;
    vertPixelChange = copyCamera.vertPixelChange;
    horiPixelChange = copyCamera.horiPixelChange;
    bottomVector = copyCamera.bottomVector;
    colorOut = copyCamera.colorOut;
}

camera::~camera(){
    delete[] colorOut;
}

void camera::operator=(const camera& copyCamera){
    eye = copyCamera.eye;
    viewdir = copyCamera.viewdir;
    updir = copyCamera.updir;
    fov = copyCamera.fov;
    imsizeWidth = copyCamera.imsizeWidth;
    vertPixelChange = copyCamera.vertPixelChange;
    horiPixelChange = copyCamera.horiPixelChange;
    bottomVector = copyCamera.bottomVector;
    colorOut = copyCamera.colorOut;
}

bool camera::isInvalid(){
    return (viewdir.isNullVector() || updir.isNullVector() || viewdir.isColinear(updir));
}

void camera::getViewplane(){
    //First we normalize the view direction vector;
    viewdir.normalize();
    vector3D orthoXBasis = viewdir.crossProduct(updir);
    orthoXBasis.normalize();
    vector3D orthoYBasis = orthoXBasis.crossProduct(viewdir);
    double viewPlaneHeight = 2*tan((fov*M_PI/180)/2);
    double pixelLength = viewPlaneHeight/(imsizeHeight-1);
    double viewPlaneWidth = pixelLength*(imsizeWidth-1);
    horiPixelChange = orthoXBasis.multiplyByScalar(pixelLength);
    vertPixelChange = orthoYBasis.multiplyByScalar(pixelLength);
    bottomVector = viewdir+(orthoXBasis.multiplyByScalar(-viewPlaneWidth/2));
    bottomVector = bottomVector+(orthoYBasis.multiplyByScalar(-viewPlaneHeight/2));
}
#include "camera.h"

camera::camera(point3D e, vector3D v, vector3D u, double f, int w, int h, scene envi){
    eye = e;
    viewdir = v;
    updir = u;
    fov = f;
    imsizeWidth = w;
    imsizeHeight = h;
    environment = envi;
    if(!isInvalid()){
        getViewplane();
    }
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

void camera::castAllRays(){
    raycaster raycaster;
    for(int j =0; j < imsizeHeight; j++){
        for(int i =0; i < imsizeWidth; i++){
            vector3D ray = bottomVector+(horiPixelChange.multiplyByScalar(i))+(vertPixelChange.multiplyByScalar(j));
            ray.normalize();
            colorOut[(j*imsizeWidth)+i] = raycaster.calculateRayEffect(eye, ray, environment);
        }
    }
}
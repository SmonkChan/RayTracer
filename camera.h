#ifndef CAMERA_H
#define CAMERA_H

#include "shape.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "material.h"
#include "lightsource.h"
#include "raycaster.h"
#include "scene.h"


class camera{
    scene environment;
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
    camera(point3D eye, vector3D viewdir, vector3D updir, double fov, int width, int height, scene environment);
    ~camera();
    camera(const camera& copyCamera);
    void operator=(const camera& copyCamera);
    int getSceneWidth(){return imsizeWidth;}
    int getSceneHeight(){return imsizeHeight;}
    bool isInvalid();
    color* getColors(){return colorOut;}
    void castAllRays();
};
#endif
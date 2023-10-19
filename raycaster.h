#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "shape.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "material.h"
#include "lightsource.h"
#include "scene.h"

class raycaster{
    private:
    scene enviroment;

    public:
    //Constructors and destructors
    raycaster(scene s);
    raycaster(const raycaster& copyray);
    ~raycaster();
    void operator=(const raycaster& copyray);

    //Methods that do the core functions of the raycaster
    shape* shootRay(point3D origin, vector3D ray, double& intersectionDistance);
    void castAll();
    color calculateRayEffect(vector3D ray);
    color* getColors();

    //Function to help debug
    void printRaycaster();
};
#endif
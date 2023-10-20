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
    public:
    raycaster(){}
    //Methods that do the core functions of the raycaster
    shape* shootRay(point3D origin, vector3D ray, double& intersectionDistance, scene environment);
    color calculateRayEffect(point3D origin, vector3D ray, scene environment);
};
#endif
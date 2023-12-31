#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "vector.h"
#include "point.h"
#include "color.h"
#include "material.h"
#include "lightsource.h"
#include "scene.h"
#include "shape.h"

class raycaster{
    public:
    raycaster(){}
    //Methods that do the core functions of the raycaster
    shape* shootRay(point3D origin, vector3D ray, double& intersectionDistance, scene* environment);
    color calculateRayEffect(int recursions, double currIoF, point3D origin, vector3D ray, scene* environment);
    double lightPercentage(point3D, vector3D ray, double distanceToLight, scene* environment);
};
#endif
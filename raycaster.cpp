#include<math.h>
#include<iostream>
#include "raycaster.h"

/*
PARAMETERS:
point3D origin: The point where the ray originates from
vector3D ray: The direction of the ray
OUTPUT:
shape*: Pointer to the shape that the ray intersected with 

This function takes a ray and then tests to see if it intersects with any shape
If it does, it keeps track of the distance and the shape that it intersected
It then returns the shape that the ray intersected at the closes point
*/
shape* raycaster::shootRay(point3D origin, vector3D ray, double& minDistance, scene environment){
    shape* closestShape = NULL;
    point3D intsecPoint;
    for(int i = 0; i < environment.numShapes; i++){
        double tempdist = environment.allShapesList[i]->intersects(origin, ray);
        if((tempdist > 0.00000001) && (tempdist < minDistance)){
            minDistance = tempdist;
            closestShape = environment.allShapesList[i];
        }
    }
    return closestShape;
}

color raycaster::calculateRayEffect(point3D origin, vector3D rayDirection, scene environment){
    double intersectionDistance = INFINITY;
    shape* shapeIntersection = shootRay(origin, rayDirection, intersectionDistance, environment);
    if(intersectionDistance == INFINITY){
        return environment.bkgcolor;   
    } 
    else{
        material* shapeMaterial = shapeIntersection->getColor();
        point3D intersectionPoint = origin + rayDirection.multiplyByScalar(intersectionDistance);
        vector3D normal = shapeIntersection->findNormal(intersectionPoint, origin);
        return shapeMaterial->calculateColor(origin, intersectionPoint, normal, environment); 
    }
}
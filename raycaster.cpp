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
shape* raycaster::shootRay(point3D origin, vector3D ray, double& minDistance, scene* environment){
    shape* closestShape = NULL;
    for(int i = 0; i < environment->numShapes; i++){
        double tempdist = environment->allShapesList[i]->intersects(origin, ray);
        if((tempdist > 0.00000001) && (tempdist < minDistance)){
            minDistance = tempdist;
            closestShape = environment->allShapesList[i];
        }
    }
    return closestShape;
}

color raycaster::calculateRayEffect(point3D origin, vector3D rayDirection, scene* environment){
    double intersectionDistance = INFINITY;
    shape* shapeIntersection = shootRay(origin, rayDirection, intersectionDistance, environment);
    if(intersectionDistance < INFINITY){
        material* shapeMaterial = shapeIntersection->getColor();
        point3D intersectionPoint = origin + rayDirection.multiplyByScalar(intersectionDistance);
        return shapeMaterial->calculateColor(origin, intersectionPoint, shapeIntersection, environment); 
    } 
    else{
        return environment->bkgcolor;   
    }
}

color raycaster::calculateRayEffect(double fresnel, point3D origin, vector3D rayDirection, scene* environment){
    double intersectionDistance = INFINITY;
    shape* shapeIntersection = shootRay(origin, rayDirection, intersectionDistance, environment);
    if(intersectionDistance < INFINITY){
        material* shapeMaterial = shapeIntersection->getColor();
        point3D intersectionPoint = origin + rayDirection.multiplyByScalar(intersectionDistance);
        color materialColor = shapeMaterial->calculateColor(origin, intersectionPoint, shapeIntersection, environment); 
        materialColor = materialColor * fresnel;
        if(materialColor.getRed() < 0.001 && materialColor.getGreen() < 0.001 && materialColor.getBlue() < 0.001){
            return color(0,0,0);
        }
        else {
            vector3D N = shapeIntersection->findNormal(intersectionPoint, origin);
            vector3D I = rayDirection.multiplyByScalar(-1);
            vector3D R = N.multiplyByScalar(2 * (N.dotProduct(I))) + rayDirection;
            double cosTheta = I.dotProduct(N);
            double F0 = shapeMaterial->getFresnel();
            double Fr = F0 + (1 - F0)*pow((1-cosTheta), 5);
            return materialColor + calculateRayEffect(Fr, intersectionPoint, R, environment);
        }
    } 
    else{
        return environment->bkgcolor;   
    }
}
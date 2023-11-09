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

color raycaster::calculateRayEffect(int recursions, double currIoR, point3D origin, vector3D rayDirection, scene* environment){
    const int maxRecursions = 10;
    double intersectionDistance = INFINITY;
    shape* shapeIntersection = shootRay(origin, rayDirection, intersectionDistance, environment);
    if(intersectionDistance < INFINITY){
        material* shapeMaterial = shapeIntersection->getColor();
        point3D intersectionPoint = origin + rayDirection.multiplyByScalar(intersectionDistance);
        color materialColor = shapeMaterial->calculateColor(origin, intersectionPoint, shapeIntersection, environment); 
        color refractedColor = color(0,0,0);
        color transmittedColor = color(0,0,0);

        vector3D N = shapeIntersection->findNormal(intersectionPoint, origin).getNormalVector();
        vector3D I = rayDirection.multiplyByScalar(-1).getNormalVector();
        double cosTheta = I.dotProduct(N);
        double F0 = shapeMaterial->getFresnel();
        double Fr = F0 + (1 - F0)*pow((1-cosTheta), 5);
        
        if(recursions >= maxRecursions || shapeMaterial->getSpecular() == 0){
            refractedColor = color(0,0,0);
        }
        else {
            if(Fr > 1) {
                std::cout << "=======ERROR=======" << std::endl;
                std::cout << "Fr = " << Fr << " F0 = " << F0 << std::endl;
                std::cout << "Normal Vector: " << N.printVector() << std::endl;
                std::cout << "I Vector: " << I.printVector() << std::endl;
                std::cout << "cosTheta between vectors " << cosTheta << std::endl << std::endl;
            }
            vector3D R = N.multiplyByScalar(2 * (N.dotProduct(I))) + rayDirection;
            refractedColor = calculateRayEffect(recursions+1, currIoR, intersectionPoint, R, environment) * Fr;
        }
        
        if(shapeMaterial->getOpacity() < 1){
            double sinTheta = std::sqrt(1 - pow(cosTheta, 2));
            double transmittedIoF = shapeMaterial->getIndexOfRefraction();
            if(sinTheta <= transmittedIoF / currIoR){
                double transCoef = (1-Fr)*(1-shapeMaterial->getOpacity());
                vector3D transmittedRay;
                double sqrtCoef = std::sqrt(1 - (pow(currIoR / transmittedIoF, 2) * (1 - pow(cosTheta, 2))));
                transmittedRay = N.multiplyByScalar(-sqrtCoef) + (N.multiplyByScalar(cosTheta) - I).multiplyByScalar(currIoR / transmittedIoF);
                transmittedColor = calculateRayEffect(recursions, transmittedIoF, intersectionPoint, transmittedRay, environment) * transCoef;
            }
        }
        
        return materialColor + refractedColor + transmittedColor;
    } 
    else{
        return environment->bkgcolor;   
    }
}
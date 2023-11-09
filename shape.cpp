#include <math.h>
#include <iostream>

using namespace std;
#include "shape.h"

shape::shape(){}

material* shape::getColor(){return texture;}

//Constructors for a sphere
sphere::sphere(){}
//sphere is defined with a center point, radius and material color
sphere::sphere(point3D c, double r, material* m){
    center = c;
    radius = r;
    texture = m;
}
void sphere::operator=(const sphere& sphere2){
    this->center = sphere2.center;
    this->radius = sphere2.radius;
    this->texture = sphere2.texture;
}

//Methods for a sphere
/*
PARAMETERS:
voint3D origin: The point in space that the ray originates from
vector3D ray: Normalized vector that is the direction of the ray
OUTPUT:
Double that is the distance away from the origin point to the closest point of intersection
Returns -1 if no intersection is found

Used for calculating the intesection with a ray and a sphere
*/
double sphere::intersects(point3D origin, vector3D ray){
    double xc = center.getX();
    double yc = center.getY();
    double zc = center.getZ();
    double xo = origin.getX();
    double yo = origin.getY();
    double zo = origin.getZ();
    double xd = ray.getX();
    double yd = ray.getY();
    double zd = ray.getZ();
    double r = radius;

    //This is a much simplified version of the equation, and much more likely to be correct
    double B = 2*(xd*(xo-xc)+yd*(yo-yc)+zd*(zo-zc));
    double C = pow(xo-xc,2)+pow(yo-yc,2)+pow(zo-zc,2)-pow(r,2);
    double discriminant = pow(B,2)-4*C;
    if(discriminant < 0) {return -1;}
    if ((-B-sqrt(discriminant))/2 < (-B+sqrt(discriminant))/2 && (-B-sqrt(discriminant))/2 > 0.00001){
        return (-B-sqrt(discriminant))/2;
    } else {
        return (-B+sqrt(discriminant))/2;
    }
}
vector3D sphere::findNormal(point3D intersection, point3D rayOrigin){
    vector3D normal = (intersection-center).getNormalVector();
    point3D furtherPoint = intersection + normal;
    point3D nearerPoint = intersection + normal.multiplyByScalar(-1);
    if(rayOrigin.distance(nearerPoint) < rayOrigin.distance(furtherPoint)){
        return normal.multiplyByScalar(-1);
    } else {
        return normal;
    }
}

//Constructors for a cylinder
cylinder::cylinder(){}
//cylinder is defined with a center point, up vector, radius, length and material color
cylinder::cylinder(point3D c, vector3D v, double r, double l, material* m){
    upVector = v.getNormalVector();
    center = c;
    radius = r;
    length = l;
    texture = m;
}
void cylinder::operator=(const cylinder& shape2){
    this->center = shape2.center;
    this->radius = shape2.radius;
    this->length = shape2.length;
    this->upVector = shape2.upVector;
    this->texture = shape2.texture;
}

/*
PARAMETERS:
voint3D origin: The point in space that the ray originates from
vector3D ray: Normalized vector that is the direction of the ray
OUTPUT:
Double that is the distance away from the origin point to the closest point of intersection
Returns -1 if no intersection is found

Massive amount of code in order to get the intersection calculation for a cylinder
There is probably a better way of doing it but this is what I figured out
*/
double cylinder::intersects(point3D origin, vector3D ray){
    vector3D X = origin-center;
    vector3D V = upVector;
    double A = ray.dotProduct(ray) - pow(ray.dotProduct(V),2);
    double B = 2*(ray.dotProduct(X) - (ray.dotProduct(V))*(X.dotProduct(V)));
    double C = X.dotProduct(X) - pow(X.dotProduct(V),2) - pow(radius,2);
    double discriminant = pow(B,2)-4*A*C;
    if(discriminant < 0){return -1;}
    double option1 = (-B - sqrt(discriminant))/(2*A);
    double option2 = (-B + sqrt(discriminant))/(2*A);
    //This is used to bound the length of the sphere
    double maxDistance = sqrt(pow(radius,2) + pow(length/2,2));
    double option1Distance = ((origin+ray.multiplyByScalar(option1))-center).magnitude();
    double option2Distance = ((origin+ray.multiplyByScalar(option2))-center).magnitude();
    if((option1Distance > maxDistance) && (option2Distance > maxDistance)){
        return -1;
    }else if(option1Distance > maxDistance){
        return option2;
    }else if(option2Distance > maxDistance){
        return option1;
    }else if(option1<option2 && option1>0.00000001){
        return option1;
    } else{return option2;}
}
vector3D cylinder::findNormal(point3D intersection, point3D rayOrigin){
    vector3D sliceBasis = (intersection-center).crossProduct(upVector);
    vector3D flattenedVector = upVector.crossProduct(sliceBasis).getNormalVector();
    //std::cout << "flattenedVector " << flattenedVector.printVector() << std::endl;
    //We need to calculate if this is hitting the inside or the outside of the cylinder
    //This is done by calculating if the intersection point + the normal vector is closer or farther than the intersection point
    //This is because if the normal vector is pointing away, it will make it farther than the intersection point so the vector should be inverted
    if(((intersection+flattenedVector)-rayOrigin).magnitude() < ((intersection+(flattenedVector.multiplyByScalar(-1.0)))-rayOrigin).magnitude()){return flattenedVector;} 
    else {return flattenedVector.multiplyByScalar(-1.0);}
}

void sphere::getTextureCords(point3D intersection, double& width, double& height) {
    vector3D N = (intersection - center).getNormalVector();
    double phi = acos(N.getZ());
    double theta = atan2(N.getY(), N.getX());
    height = phi/M_PI;
    width = theta/(2*M_PI)+0.5;
}

void cylinder::getTextureCords(point3D intersection, double& width, double& height) {
    std::cout << "Impliment texture cords for cylinder" << std::endl;
}
#include <math.h>
#include <iostream>

using namespace std;
#include "shape.h"

shape::shape(){}

shape::shape(const shape& shape2){
    *this = shape2;
}

material* shape::getColor(){return texture;}

//Print all the data about a shape as a string;
string shape::printShape(){
    string out;
    out.append("Default Shape Object\n");
    out.append("material: ").append(texture->calculateColor().getString()).append("\n");
    return out;
}

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

    //This is all for calculating the distance, I just split it up onto multiple lines
    /*
    double difference = pow(r,2)-pow(xc,2)-pow(xo,2)-pow(yc,2)-pow(yo,2)-pow(zc,2)-pow(zo,2)+2*xo*xc+2*yo*yc+2*zo*zc;
    //Sum of the vector components squared
    double sumSquares = pow(xd,2)+pow(yd,2)+pow(zd,2);
    double otherComp = xd*xo+yd*yo+zd*zo-xd*xc-yd*yc-zd*zc;
    double insideRoot = difference/sumSquares+pow(otherComp/sumSquares,2);
    //This checks if the root is imaginary
    //If it is, there is no intersection and so return -1 to indicate that
    if(insideRoot<0){return -1;}
    if(sqrt(insideRoot)-otherComp/sumSquares < -sqrt(insideRoot)-otherComp/sumSquares){
        return sqrt(insideRoot)-otherComp/sumSquares;
    }
    else{return -sqrt(insideRoot)-otherComp/sumSquares;}
    */
    
    //This is a much simplified version of the equation, and much more likely to be correct
    double B = 2*(xd*(xo-xc)+yd*(yo-yc)+zd*(zo-zc));
    double C = pow(xo-xc,2)+pow(yo-yc,2)+pow(zo-zc,2)-pow(r,2);
    double discriminant = pow(B,2)-4*C;
    if(discriminant < 0) {return -1;}
    if ((-B-sqrt(discriminant))/2 < (-B+sqrt(discriminant))/2){
        return (-B-sqrt(discriminant))/2;
    } else {return (-B+sqrt(discriminant))/2;}
}
string sphere::printShape(){
    string out;
    out.append("Sphere\n");
    out.append("center: ").append(center.printPoint()).append("\n");
    out.append("raidus: ").append(to_string(radius)).append("\n");
    out.append("material: ").append(texture->calculateColor().getString()).append("\n");
    return out;
}
vector3D sphere::findNormal(point3D intersection, point3D rayOrigin){
    return (intersection-center).getNormalVector();
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
    }else if(option1<option2 && option1>=0){
        return option1;
    } else{return option2;}
}
string cylinder::printShape(){
    string out;
    out.append("Cylinder\n");
    out.append("center: ").append(center.printPoint()).append("\n");
    out.append("upVector: ").append(upVector.printVector()).append("\n");
    out.append("raidus: ").append(to_string(radius)).append("\n");
    out.append("length: ").append(to_string(length)).append("\n");
    out.append("material: ").append(texture->calculateColor().getString()).append("\n");
    return out;
}
vector3D cylinder::findNormal(point3D intersection, point3D rayOrigin){
    vector3D sliceBasis = (intersection-center).crossProduct(upVector);
    if(fabs((center-rayOrigin).magnitude()) > fabs((intersection-rayOrigin).magnitude())){
        return upVector.crossProduct(sliceBasis).getNormalVector();
    } else {return upVector.crossProduct(sliceBasis).getNormalVector().multiplyByScalar(-1);}
}
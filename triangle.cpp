#include "triangle.h"
#include <math.h>
#include <iostream>

flatTriangle::flatTriangle(point3D* vertex1, point3D* vertex2, point3D* vertex3, material* mat){
    p1 = vertex1;
    p2 = vertex2;
    p3 = vertex3;
    e1 = (*p2-*p1);
    e2 = (*p3-*p1);
    planarNormal = e1.crossProduct(e2);
    std::cout << "Point 0: " << p1->printPoint() << std::endl;
    std::cout << "Point 1: " << p2->printPoint() << std::endl;
    std::cout << "Point 2: " << p3->printPoint() << std::endl;
    std::cout << "Triangle vector 1: " << e1.printVector() << std::endl;
    std::cout << "Triangle vector 2: " << e2.printVector() << std::endl;
    std::cout << "Plane normal: " << planarNormal.printVector() << std::endl;
    texture = mat;
}

smoothTriangle::smoothTriangle(point3D* vertex1, vector3D* normal1, point3D* vertex2, vector3D* normal2, point3D* vertex3, vector3D* normal3, material* mat){
    p1 = vertex1;
    p2 = vertex2;
    p3 = vertex3;
    n1 = normal1;
    n2 = normal2;
    n3 = normal3;
    e1 = (*p2-*p1);
    e2 = (*p3-*p1);
    planarNormal = e1.crossProduct(e2);
    texture = mat;
}

double triangle::intersects(point3D origin, vector3D ray){
    double A = planarNormal.getX();
    double B = planarNormal.getY();
    double C = planarNormal.getZ();
    double D = -(A*p1->getX() + B*p1->getY() + C*p1->getZ());
    double denominator = A*(ray.getX()) + B*(ray.getY()) + C*(ray.getZ());
    if(fabs(denominator) < 0.0000000001){return -1;}
    double t = -(A*origin.getX() + B*origin.getY() + C*origin.getZ()+D)/denominator;
    if(t < 0){return -1;}
    point3D intersection = origin+ray.multiplyByScalar(t);
    double d11 = e1.dotProduct(e1);
    double d12 = e1.dotProduct(e2);
    double d22 = e2.dotProduct(e2);
    double det = d11*d22-d12*d12;
    if(fabs(det) < 0.0000000001){return -1;}
    vector3D ep = intersection-(*p1);
    double d1p = e1.dotProduct(ep);
    double d2p = e2.dotProduct(ep);
    beta = (d22*d1p - d12*d2p)/det;
    gamma = (d11*d2p - d12*d1p)/det;
    if(beta < 0 || beta > 1){
        return -1;
    }
    else if(gamma < 0 || gamma > 1){
        return -1;
    }
    else if((1 - beta - gamma) < 0 || (1 - beta - gamma) > 1){
        return -1;
    }
    else {
        return (intersection - origin).magnitude();
    }
}

vector3D smoothTriangle::findNormal(point3D p, point3D originPoint){
    return (n1->multiplyByScalar(1-beta-gamma) + n2->multiplyByScalar(beta) + n3->multiplyByScalar(gamma)).getNormalVector();
}

void flatTriangleTextured::getTextureCords(point3D intersection, double& width, double& height) {

}

void smoothTriangleTextured::getTextureCords(point3D intersection, double& width, double& height) {

}

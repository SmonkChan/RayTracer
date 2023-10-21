#include "triangle.h"
#include <math.h>

flatTriangle::flatTriangle(point3D* vertex1, point3D* vertex2, point3D* vertex3){
    p1 = vertex1;
    p2 = vertex2;
    p3 = vertex3;
    vector3D e1 = (*p2-*p1);
    vector3D e2 = (*p3-*p1);
    planarNormal = e1.crossProduct(e2);
}

smoothTriangle::smoothTriangle(point3D* vertex1, vector3D* normal1, point3D* vertex2, vector3D* normal2, point3D* vertex3, vector3D* normal3){
    p1 = vertex1;
    p2 = vertex2;
    p3 = vertex3;
    n1 = normal1;
    n2 = normal2;
    n3 = normal3;
    vector3D e1 = (*p2-*p1);
    vector3D e2 = (*p3-*p1);
    planarNormal = e1.crossProduct(e2);
}

double triangle::intersects(point3D origin, vector3D ray){
    double A = planarNormal.getX();
    double B = planarNormal.getY();
    double C = planarNormal.getZ();
    double D = -(A*p1->getX() + B*p1->getY() + C*p3->getZ());
    double denominator = A*ray.getX() + B*ray.getY() + C*ray.getZ();
    if(fabs(denominator) < 0.0000000001){return -1;}
    double t = -(A*origin.getX() + B*origin.getY() + C*origin.getZ())/denominator;
    point3D intersection = point3D((origin.getX() + t*ray.getX()), (origin.getY() + t*ray.getY()), (origin.getZ() + t*ray.getZ()));
    double d11 = e1.dotProduct(e1);
    double d12 = e1.dotProduct(e2);
    double d22 = e2.dotProduct(e2);
    double det = d11*d12-d12*d22;
    if(fabs(det) < 0.0000000001){return -1;}
    vector3D ep = intersection-*p1;
    double d1p = e1.dotProduct(ep);
    double d2p = e2.dotProduct(ep);
    beta = (d22*d1p - d12*d2p)/det;
    gamma = (d11*d2p - d12*d1p)/det;
    if((fabs(beta-0.5) > 0.5) || (fabs(gamma-0.5) > 0.5) || (fabs(1-beta-gamma-0.5) > 0.5)){
        return -1;
    }
    return origin.distance(intersection);
}

vector3D smoothTriangle::findNormal(point3D p, point3D originPoint){
    return (n1->multiplyByScalar(1-beta-gamma) + n2->multiplyByScalar(beta) + n3->multiplyByScalar(gamma)).getNormalVector();
}
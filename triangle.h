#ifndef TRIANGLE_H
#define TRIANLGE_H

#include "shape.h"
#include "point.h"
#include "vector.h"

class triangle : public shape
{
    protected:
    point3D* p1;
    point3D* p2;
    point3D* p3;
    vector3D e1;
    vector3D e2;
    vector3D planarNormal;
    double beta;
    double gamma;
    public:
    double intersects(point3D rayOrigin, vector3D ray);
    virtual vector3D findNormal(point3D p, point3D originPoint) = 0;
    virtual void getTextureCords(point3D intersection, double& width, double& height) = 0;
};

class flatTriangle : public triangle
{
    public:
    flatTriangle(point3D* vertex1, point3D* vertex2, point3D* vertex3, material* mat);
    vector3D findNormal(point3D p, point3D originPoint){return planarNormal.getNormalVector();}
    virtual void getTextureCords(point3D intersection, double& width, double& height){}
};

class smoothTriangle : public triangle
{
    private:
    vector3D* n1;
    vector3D* n2;
    vector3D* n3;
    public:
    smoothTriangle(point3D* vertex1, vector3D* normal1, point3D* vertex2, vector3D* normal2, point3D* vertex3, vector3D* normal3, material* mat);
    vector3D findNormal(point3D p, point3D originPoint);
    virtual void getTextureCords(point3D intersection, double& width, double& height){}
};

class flatTriangleTextured : public flatTriangle
{
    void getTextureCords(point3D intersection, double& width, double& height);
};

class smoothTriangleTextured: public smoothTriangle
{
    void getTextureCords(point3D intersection, double& width, double& height);
};

#endif
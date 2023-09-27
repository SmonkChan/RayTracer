#ifndef RAYCASTER_H
#define RAYCASTER_H

#include "shape.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "material.h"
#include "lightsource.h"

class raycaster{
    private:
    point3D eye;
    vector3D viewdir;
    vector3D updir;
    double fov;
    int imsizeWidth;
    int imsizeHeight;
    color bkgcolor;
    int numShapes;
    shape** allShapesList;
    color* colorOut;
    lightsource* light;

    //These vectors forms the orthonormal basis for the viewplane
    vector3D orthoXBasis;
    vector3D orthoYBasis;

    //These lengths are assuming the viewplane is 1 unit away from the eye
    double viewPlaneWidth;
    double viewPlaneHeight;
    double pixelLength;

    //These vectors are colinear as the orthogonal viewplane basis, but with length of one pixel
    vector3D vertPixelChange;
    vector3D horiPixelChange;
    
    //This vector points at the center of the bottom left pixel
    vector3D bottomVector;

    //This gets the vectors that form the pixel changes
    //When the viewdir is normal, the pixel changes length are equal to 1 pixel
    //They then form orthoganal basis for the viewplane
    //returns nothing as it just updates the vectors that are privatly stored as vertPixelChange and horiPixelChange
    void getViewplaneBasis();
    //This gets the vector the intersects the bottom left pixel
    //This is used along with the pixel change to iterate through and get all of the rays that intersect the viewplane
    //returns nothing as it just updates the private vector bottomVector
    void findBottomLeftPixel();

    public:
    //Constructors and destructors
    raycaster(point3D e, vector3D v, vector3D u, double f, double w, double h, color b, shape** a, int n, lightsource* l = nullptr);
    raycaster(const raycaster& copyray);
    ~raycaster();
    void operator=(const raycaster& copyray);

    //Methods that do the core functions of the raycaster
    shape* shootRay(point3D origin, vector3D ray, double& intersectionDistance);
    void castAll();
    color* getColors();

    //Function to help debug
    void printRaycaster();
};
#endif
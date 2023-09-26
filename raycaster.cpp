#include<math.h>
#include<iostream>
#include "raycaster.h"

raycaster::raycaster(point3D e, vector3D v, vector3D u, double f, double w, double h, color b, shape** a, int n){
    eye = e;
    viewdir = v;
    updir = u;
    fov = f;
    imsizeWidth = w;
    imsizeHeight = h;
    bkgcolor = b;
    allShapesList = a;
    numShapes = n;

    //Defines an array to store the colors for the out file
    colorOut = new color[imsizeWidth * imsizeHeight];

    //Uses two functions to find other internal variables
    getViewplaneBasis();
    findBottomLeftPixel();
    //printRaycaster();
}

raycaster::raycaster(const raycaster& copyray){
    colorOut = NULL;
    *this = copyray;
}

raycaster::~raycaster(){
    delete[] colorOut;
}

void raycaster::operator=(const raycaster& copyray){
    this->eye = copyray.eye;
    this->viewdir = copyray.viewdir;
    this->updir = copyray.updir;
    this->fov = copyray.fov;
    this->imsizeWidth = copyray.imsizeWidth;
    this->imsizeHeight = copyray.imsizeHeight;
    this->bkgcolor = copyray.bkgcolor;
    this->allShapesList = copyray.allShapesList;
    this->numShapes = copyray.numShapes;

    delete[] colorOut;
    this->colorOut = new color[imsizeWidth * imsizeHeight];
    for (int i = 0; i < imsizeHeight*imsizeWidth; i++){
        this->colorOut[i] = copyray.colorOut[i];
    }
}
/*
This function is a helper function that uses the input values in order to calculate an orthogonal basis for the viewplane
The two vectors that result are also length one pixel given that the eye direction vector is normalized
*/
void raycaster::getViewplaneBasis(){
    //First we normalize the view direction vector;
    viewdir.normalize();
    orthoXBasis = viewdir.crossProduct(updir);
    orthoXBasis.normalize();
    orthoYBasis = orthoXBasis.crossProduct(viewdir);

    viewPlaneHeight = 2*tan((fov*M_PI/180)/2);
    pixelLength = viewPlaneHeight/(imsizeHeight-1);
    viewPlaneWidth = pixelLength*(imsizeWidth-1);
    horiPixelChange = orthoXBasis.multiplyByScalar(pixelLength);
    vertPixelChange = orthoYBasis.multiplyByScalar(pixelLength);
    //By this point we should have two vectors that have the length of a pixel in our view plane
    //Given that the viewplane is 1 unit away from the eye
    //These two vectors form an orthagonal basis for the viewplane
}
/*
Because we already found the basis for the viewplane, we use that to find the vector that is pointing at the bottom left corner
This is used to easily cast all of the rays
*/
void raycaster::findBottomLeftPixel(){
    //finds the vector that points to the bottom left corner
    bottomVector = viewdir+(orthoXBasis.multiplyByScalar(-viewPlaneWidth/2));
    bottomVector = bottomVector+(orthoYBasis.multiplyByScalar(-viewPlaneHeight/2));
}

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
shape* raycaster::shootRay(point3D origin, vector3D ray){
    double minDistance = INFINITY;
    shape* closestShape = NULL;
    point3D intsecPoint;
    for(int i = 0; i < numShapes; i++){
        double tempdist = allShapesList[i]->intersects(origin, ray);
        if((tempdist >= 0) && (tempdist < minDistance)){
            minDistance = tempdist;
            closestShape = (allShapesList[i]);
        }
    }
    return closestShape;
}

/*
This function works in order to cast every ray through every pixel in the view plane
It does this starting at the bottom left going to the top right and then adds the vectors that are one pixel long that form the orthogonal viewplane
then for each pixel it shoots a ray, and then gets the color of the object that it intersected with closest
*/
void raycaster::castAll(){
    for(int j =0; j < imsizeHeight; j++){
        for(int i =0; i < imsizeWidth; i++){
            vector3D ray = bottomVector+(horiPixelChange.multiplyByScalar(i))+(vertPixelChange.multiplyByScalar(j));
            ray.normalize();
            shape* shapeIntersection = shootRay(eye, ray);
            if(shapeIntersection != NULL){
                colorOut[(j*imsizeWidth)+i] = shootRay(eye, ray)->getColor();
            } else{colorOut[(j*imsizeWidth)+i] = bkgcolor;}
        }
    }
}

color* raycaster::getColors(){return colorOut;}


//Used for debugging, this void function prints out all the information about the raycaster
void raycaster::printRaycaster(){
    std::cout << std::endl << "RAYCASTER INFO:" << std::endl;
    std::cout << "eye: " << eye.printPoint() << std::endl;
    std::cout << "viewdir: " << viewdir.printVector() << std::endl;
    std::cout << "updir: " << updir.printVector() << std::endl;
    std::cout << "fov: " << fov << std::endl;
    std::cout << "imsizeWidth: " << imsizeWidth << std::endl;
    std::cout << "imsizeHeight: " << imsizeHeight << std::endl;
    std::cout << "bkgcolor: " << bkgcolor.getString() << std::endl;
    std::cout << "First Shape: " << std::endl << allShapesList[0]->printShape();
    std::cout << "othoXBasis: " << orthoXBasis.printVector() << std::endl;
    std::cout << "orthoYBasis: " << orthoYBasis.printVector() << std::endl;
    std::cout << "viewPlaneWidth: " << viewPlaneWidth << std::endl;
    std::cout << "viewPlaneHeight: " << viewPlaneHeight << std::endl;
    std::cout << "pixelLength: " << pixelLength << std::endl;
    std::cout << "horiPixelChange" << horiPixelChange.printVector() << std::endl;
    std::cout << "vertPixelChange: " << vertPixelChange.printVector() << std::endl;
    std::cout << "bottomVector: " << bottomVector.printVector() << std::endl;
}
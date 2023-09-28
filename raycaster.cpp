#include<math.h>
#include<iostream>
#include "raycaster.h"

raycaster::raycaster(point3D e, vector3D v, vector3D u, double f, double w, double h, color b, shape** a, int ns, lightsource** l, int nl){
    eye = e;
    viewdir = v;
    updir = u;
    fov = f;
    imsizeWidth = w;
    imsizeHeight = h;
    bkgcolor = b;
    allShapesList = a;
    numShapes = ns;
    allLights = l;
    numLights = nl;


    lightShadow = new color[numLights];
    lightDirection = new vector3D[numLights];

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
    delete[] lightShadow;
    delete[] lightDirection;
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
shape* raycaster::shootRay(point3D origin, vector3D ray, double& minDistance){
    shape* closestShape = NULL;
    point3D intsecPoint;
    for(int i = 0; i < numShapes; i++){
        double tempdist = allShapesList[i]->intersects(origin, ray);
        if((tempdist > 0.00000001) && (tempdist < minDistance)){
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
            colorOut[(j*imsizeWidth)+i] = calculateRayEffect(ray);
        }
    }
}

color raycaster::calculateRayEffect(vector3D ray){
    double intersectionDistance = INFINITY;
    shape* shapeIntersection = shootRay(eye, ray, intersectionDistance);
    //std::cout << "intersectionDistance " << intersectionDistance << std::endl;
    if(intersectionDistance < INFINITY){
        //check what type of material it is
        //If it is a default material, we just want it to return the color
        //As such we dont have to worry about all the cacluations for fancier images
        material* shapeMaterial = shapeIntersection->getColor();
        if(shapeMaterial->materialType() == 1){
            //std::cout << "Identified Phong Material" << std::endl;
            point3D intersectionPoint = eye + ray.multiplyByScalar(intersectionDistance);
            vector3D normal = shapeIntersection->findNormal(intersectionPoint, eye);
            for(int i = 0; i < numLights; i++){
                double distance = allLights[i]->distanceFromLight(intersectionPoint);
                double newDistance = distance;
                lightDirection[i] = allLights[i]->getLightDirection(intersectionPoint);
                shootRay(intersectionPoint, lightDirection[i], newDistance);
                //The light color is baked into the shadow checker
                //If there is a shadow the light color is treated as if the light has a black color
                //Light attenuation is also baked into the getLightColor function
                if (newDistance < distance){lightShadow[i] = color(0.0,0.0,0.0);}
                else{; lightShadow[i] = allLights[i]->getLightColor(distance);}
            }
            return shapeMaterial->calculateColor(eye, intersectionPoint, allLights, lightShadow, lightDirection, numLights, normal);
        } else{return shapeMaterial->calculateColor();}

        
    } else{return bkgcolor;}
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
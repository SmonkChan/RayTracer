#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>

#include "raycaster.h"
#include "shape.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "material.h"
#include "lightsource.h"

using namespace std;

int main(int argc, char *argv[])
{
    //First checks to make sure that an argument of the input file is given
    //An output file is created from the name of the input file
    if(argc < 2)
    {
        cout << "Must give a file for input" << endl;
        return -1;
    }

    //All of the stuff below is just for parsing through the input file
    //Setting up variables that will hold data that is read in from the file
    point3D eye;
    vector3D viewdir(0,0,0);
    vector3D updir(0,0,0);
    double fov;
    int width;
    int height;
    color bkgcolor;

    //Was using to test some things
    //cout << "Size of shape class: " << sizeof(shape) << endl;
    //cout << "Size of sphere class: " << sizeof(sphere) << endl;
    //cout << "Size of cylinder class: " << sizeof(cylinder) << endl;

    //This is data for an array that stores the shapes
    //It is an array of pointers
    //The array starts out at size 4 but then it will double every time it fills up
    int listSize = 4;
    int numShapes = 0;
    shape** allShapeList = new shape*[listSize];

    int matlistSize = 4;
    int numMats = 0;
    material** allMaterials = new material*[matlistSize];

    int lightlistSize = 4;
    int numLights = 0;
    lightsource** allLights = new lightsource*[numLights];

    //A bunch of temp variables to help parse the file
    string strIn;
    material* currMaterial;
    double temp1;
    double temp2;
    double temp3;
    vector3D tempVector;
    point3D tempPoint;
    shape** tempList = nullptr;
    material** tempMats = nullptr;
    color tempColor1;
    color tempColor2;

    //Open and parse the input file
    ifstream infile;
    infile.open (argv[1]);
    if (infile.is_open())
    {
        //This while loop is just for parsing the file
        //It matches whatever keyword with it's whatever data it contains
        while(infile >> strIn){
            if(strIn == "eye"){
                cout << "reading eye" << endl;
                infile >> temp1 >> temp2 >> temp3;
                eye = point3D(temp1, temp2, temp3);
            }
            else if(strIn == "viewdir"){
                cout << "reading viewdir" << endl;
                infile >> temp1 >> temp2 >> temp3;
                viewdir = vector3D(temp1, temp2, temp3);
            }
            else if(strIn == "updir"){
                cout << "reading updir" << endl;
                infile >> temp1 >> temp2 >> temp3;
                updir = vector3D(temp1, temp2, temp3);
            }
            else if(strIn == "fov"){
                cout << "reading fov" << endl;
                infile >> fov;
            }
            else if(strIn == "imsize"){
                cout << "reading imsize" << endl;
                infile >> width >> height;
            }
            else if(strIn == "bkgcolor"){
                cout << "reading bkgcolor" << endl;
                infile >> temp1 >> temp2 >> temp3;
                if((temp1 > 1) || (temp1 < 0) || (temp2 > 1) || (temp2 < 0) || (temp3 > 1) || (temp3 < 0)){
                    cout << "Color values must be between 0 and 1 inclusive" << endl;
                }
                else {
                    bkgcolor = color(temp1, temp2, temp3);
                }
            }
            else if(strIn == "mtlcolor"){
                cout << "Reading Phong Material" << endl;
                if(numMats == matlistSize){
                    matlistSize *= 2;
                    tempMats = new material*[listSize];
                    for(int i = 0; i < numMats; i++){
                        tempMats[i] = allMaterials[i];                        }
                    delete[] allMaterials;
                    allMaterials = tempMats;
                    tempMats = nullptr;
                }
                double tempDoubles[10];
                for(int i = 0; i < 10; i++){
                    cout << "reading double number " << i << endl;
                    infile >> tempDoubles[i];
                }
                color baseColor = color(tempDoubles[0], tempDoubles[1], tempDoubles[2]);
                color spotColor = color(tempDoubles[3], tempDoubles[4], tempDoubles[5]);
                currMaterial = new Phong_material(baseColor, spotColor, tempDoubles[6], tempDoubles[7], tempDoubles[8], tempDoubles[9]);
                allMaterials[numMats] = currMaterial;
                numMats++;
            }
            else if(strIn == "sphere"){
                cout << "Reading Sphere" << endl;
                //The only thing really weird is these lines of code
                //If the array that was alocated is full, it allocats a new array with double the size
                if(numShapes == listSize){
                    listSize *= 2;
                    tempList = new shape*[listSize];
                    for(int i = 0; i < numShapes; i++){
                        tempList[i] = allShapeList[i];
                    }
                    delete[] allShapeList;
                    allShapeList = tempList;
                    tempList = nullptr;
                }
                infile >> temp1 >> temp2 >> temp3;
                tempPoint = point3D(temp1, temp2, temp3);
                infile >> temp1; 
                allShapeList[numShapes] = new sphere(tempPoint, temp1, currMaterial);
                numShapes++;
            }
            else if(strIn == "cylinder"){
                cout << "Reading Cylinder" << endl;
                if(numShapes == listSize){
                    listSize *= 2;
                    tempList = new shape*[listSize];
                    for(int i = 0; i < numShapes; i++){
                        tempList[i] = allShapeList[i];
                    }
                    delete[] allShapeList;
                    allShapeList = tempList;
                    tempList = nullptr;
                }
                infile >> temp1 >> temp2 >> temp3;
                tempPoint = point3D(temp1, temp2, temp3);
                infile >> temp1 >> temp2 >> temp3;
                tempVector = vector3D(temp1, temp2, temp3);
                infile >> temp1 >> temp2; 
                //Casts the void pointer as a cylinder in order to add it to the array
                //I am using the chunk of memory as an array, and manually adding to the pointer to access the array indicies
                allShapeList[numShapes] = new cylinder(tempPoint, tempVector, temp1, temp2, currMaterial);
                numShapes++;
            }
            else if(strIn == "parallel"){
                cout << "Impliment parallel keyword" << endl;
            }
            else if(strIn == "light"){
                cout << "Reading Light" << endl;
                if(numLights == lightlistSize){
                    listSize *= 2;
                    lightsource** tempList = new lightsource*[lightlistSize];
                    for(int i = 0; i < numLights; i++){
                        tempList[i] = allLights[i];
                    }
                    delete[] allLights;
                    allLights = tempList;
                }
                int lightType;
                double r;
                double g;
                double b;
                infile >> temp1 >> temp2 >> temp3 >> lightType >> r >> g >> b;
                color lightColor = color(r,g,b);
                switch (lightType){
                case 0:
                    cout << "Read Directional Light" << endl;
                    allLights[numLights] = new directional_light(vector3D(temp1, temp2, temp3), lightColor);
                    numLights++;
                    break;
                case 1:
                    cout << "read point light" << endl;
                    allLights[numLights] = new point_light(point3D(temp1, temp2, temp3), lightColor);
                    numLights++;
                    break;
                default:
                    cout << "Invalid light type" << endl;
                    break;
                }
            }
        }
        infile.close();

        //Test cases to make sure that it is reading the file in correctly
        /*
        cout << "Memory Size: " << listSize << endl;
        cout << (*(shape*)(allShapeList)).printShape();
        cout << "eye: " << eye.printPoint() << endl;
        cout << "viewdir: " << viewdir.printVector() << endl;
        cout << "updir: " << updir.printVector() << endl;
        cout << "fov: " << fov << endl;
        cout << "imsize width: " << width << " imsize height: " << height << endl;
        cout << "bkgcolor: " << bkgcolor.getString() << endl;
        cout << "mtlcolor: " << tempMaterial.getString() << endl;
        */
        
    }
    //Reports an error if the file fails to open
    else 
    {
        cout << "Unable to open file " << argv[1] << endl;
        for(int i = 0; i > numShapes; i++){
            delete allShapeList[i];
        } 
        delete[] allShapeList;
        for(int i = 0; i < numMats; i++){
            delete allMaterials[i];
        }
        delete[] allMaterials;
        return -1;
    }
    //If either given vector is a null vector or they are colinear, stop the program
    if(viewdir.isNullVector() || updir.isNullVector() || viewdir.isColinear(updir)){
        cout << "Vectors given are invalid" << endl;
        for(int i = 0; i > numShapes; i++){
            delete allShapeList[i];
        } 
        delete[] allShapeList;
        for(int i = 0; i < numMats; i++){
            delete allMaterials[i];
        }
        delete[] allMaterials;
        return -1;
    }

    //raycaster is a class that contains all of the logic to cast the rays
    raycaster rays(eye, viewdir, updir, fov, width, height, bkgcolor, allShapeList, numShapes, allLights, numLights);
    rays.castAll();

    //Creates an output file based on the name of the input file
    string out;
    out = argv[1];
    out.append(".ppm");

    //Opens the outfile in order to create the image
    ofstream outfile;
    outfile.open (out);
    if (outfile.is_open())
    {
        //Prepares the header for the ppm file
        outfile << "P3 " << width << " " << height << " " << 255 << endl;
        
        //this is where the printing out the image
        //This has to be build from bottom to top because the rays start at the bottom left corner
        color* image = rays.getColors();
        for(int j = height-1; j >= 0; j--){
            for(int i = 0; i < width; i++){
                outfile << image[j*width+i].getString() << endl;
            }
        }

        outfile.close();
    }
    else
    {
        cout << "Unable to open file" << '\n';
        return -1;
    }

    //Dealocates the shape array to prevent a memory leak
    for(int i = 0; i < numShapes; i++){
        delete allShapeList[i];
    }
    delete[] allShapeList;

    for(int i = 0; i < numMats; i++){
        delete allMaterials[i];
    }
    delete[] allMaterials;

    for(int i = 0; i < numLights; i++){
        delete allLights[i];
    }
    delete[] allLights;

    return 0;
}
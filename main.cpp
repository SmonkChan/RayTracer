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
                infile >> temp1 >> temp2 >> temp3;
                eye = point3D(temp1, temp2, temp3);
            }
            else if(strIn == "viewdir"){
                infile >> temp1 >> temp2 >> temp3;
                viewdir = vector3D(temp1, temp2, temp3);
            }
            else if(strIn == "updir"){
                infile >> temp1 >> temp2 >> temp3;
                updir = vector3D(temp1, temp2, temp3);
            }
            else if(strIn == "fov"){
                infile >> fov;
            }
            else if(strIn == "imsize"){
                infile >> width >> height;
            }
            else if(strIn == "bkgcolor"){
                infile >> temp1 >> temp2 >> temp3;
                if((temp1 > 1) || (temp1 < 0) || (temp2 > 1) || (temp2 < 0) || (temp3 > 1) || (temp3 < 0)){
                    cout << "Color values must be between 0 and 1 inclusive" << endl;
                }
                else {
                    bkgcolor = color(temp1, temp2, temp3);
                }
            }
            else if(strIn == "mtlcolor"){
                if(numMats == matlistSize){
                    matlistSize *= 2;
                    tempMats = new material*[listSize];
                    for(int i = 0; i < numMats; i++){
                        tempMats[i] = allMaterials[i];                        }
                    delete[] allMaterials;
                    allMaterials = tempMats;
                    tempMats = nullptr;
                }
                infile >> temp1 >> temp2 >> temp3;
                if((temp1 > 1) || (temp1 < 0) || (temp2 > 1) || (temp2 < 0) || (temp3 > 1) || (temp3 < 0)){
                    cout << "Color values must be between 0 and 1 inclusive" << endl;
                }
                else {
                    tempColor1 = color(temp1, temp2, temp3);
                    currMaterial = new material(color(temp1, temp2, temp3));
                    allMaterials[numMats] = currMaterial;
                    numMats++;
                }                
            }
            else if(strIn == "sphere"){
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
    raycaster rays(eye, viewdir, updir, fov, width, height, bkgcolor, allShapeList, numShapes);
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
    return 0;
}
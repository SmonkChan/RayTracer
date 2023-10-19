#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <sstream>

#include "raycaster.h"
#include "shape.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "material.h"
#include "lightsource.h"
#include "scene.h"

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

    //An enviroment to store the scene in
    scene enviroment = scene();

    //A bunch of temp variables to help parse the file
    string strIn;

    //Open and parse the input file
    ifstream infile;
    infile.open (argv[1]);
    if (infile.is_open())
    {
        //This while loop is just for parsing the file
        //It matches whatever keyword with it's whatever data it contains
        while(infile >> strIn){
            if(strIn == "eye"){
                double x;
                double y;
                double z;
                infile >> x >> y >> z;
                enviroment.setEye(point3D(x, y, z));
            }
            else if(strIn == "viewdir"){
                double x;
                double y;
                double z;
                infile >> x >> y >> z;
                enviroment.setViewDirection(vector3D(x, y, z));
            }
            else if(strIn == "updir"){
                double x;
                double y;
                double z;
                infile >> x >> y >> z;
                enviroment.setUpDirection(vector3D(x, y, z));
            }
            else if(strIn == "fov"){
                double fov;
                infile >> fov;
                enviroment.setFOV(fov);
            }
            else if(strIn == "imsize"){
                int width;
                int height;
                infile >> width >> height;
                enviroment.setImageWidth(width);
                enviroment.setImageHeight(height);
            }
            else if(strIn == "bkgcolor"){
                double r;
                double g;
                double b;
                infile >> r >> g >> b;
                if((r > 1) || (r < 0) || (g > 1) || (g < 0) || (b > 1) || (b < 0)){
                    cout << "Color values must be between 0 and 1 inclusive" << endl;
                }
                else {
                    enviroment.setBackgroundColor(color(r, g, b));
                }
            }
            else if(strIn == "mtlcolor"){
                material* currMaterial;
                double tempDoubles[10];
                string materialLine;
                std::getline(infile, materialLine);
                std::stringstream s(materialLine);
                double readIn;
                int numDoubles = 0;
                while (s >> readIn){
                    tempDoubles[numDoubles] = readIn;
                    numDoubles++;
                }
                if(numDoubles == 3){
                    currMaterial = new material(color(tempDoubles[0], tempDoubles[1], tempDoubles[2]));
                }
                else if(numDoubles == 10){
                    color baseColor = color(tempDoubles[0], tempDoubles[1], tempDoubles[2]);
                    color spotColor = color(tempDoubles[3], tempDoubles[4], tempDoubles[5]);
                    currMaterial = new Phong_material(baseColor, spotColor, tempDoubles[6], tempDoubles[7], tempDoubles[8], tempDoubles[9]);
                }
                else{
                    cout << "invalid material";
                    break;
                }
                enviroment.addMaterial(currMaterial);
            }
            else if(strIn == "sphere"){
                double x;
                double y;
                double z;
                double r;
                infile >> x >> y >> z >> r;
                material* currMaterial = enviroment.getCurrMaterial();
                enviroment.addShape(new sphere(point3D(x, y, z), r, currMaterial));
            }
            else if(strIn == "cylinder"){
                double px;
                double py;
                double pz;
                double vx;
                double vy;
                double vz;
                double r;
                double h;
                infile >> px >> py >> pz >> vx >> vy >> vz >> r >> h;
                material* currMaterial = enviroment.getCurrMaterial();
                enviroment.addShape(new cylinder(point3D(px, py, pz), vector3D(vx, vy, vz), r, h, currMaterial));
            }
            else if(strIn == "parallel"){
                cout << "Impliment parallel keyword" << endl;
            }
            else if(strIn == "light"){
                double x;
                double y;
                double z;
                int lightType;
                double r;
                double g;
                double b;
                infile >> x >> y >> z >> lightType >> r >> g >> b;
                color lightColor = color(r,g,b);
                switch (lightType){
                case 0:
                    enviroment.addLight(new directional_light(vector3D(x, y, z), lightColor));
                    break;
                case 1:
                    enviroment.addLight(new point_light(point3D(x, y, z), lightColor));
                    break;
                default:
                    cout << "Invalid light type" << endl;
                    break;
                }
            }
        }
        infile.close();
        
    }
    //Reports an error if the file fails to open
    else 
    {
        cout << "Unable to open file " << argv[1] << endl;
        return -1;
    }
    //If either given vector is a null vector or they are colinear, stop the program
    if(enviroment.isInvalid()){
        cout << "Vectors given are invalid" << endl;
        return -1;
    }

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
    return 0;
}
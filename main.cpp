#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <sstream>
#include <stdexcept>

#include "raycaster.h"
#include "shape.h"
#include "vector.h"
#include "point.h"
#include "color.h"
#include "material.h"
#include "lightsource.h"
#include "scene.h"
#include "camera.h"
#include "triangle.h"

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
    scene* environment = new scene();

    //variables to store for the camera
    point3D eye;
    vector3D viewdir;
    vector3D updir;
    double fov;
    int width;
    int height;

    Phong_material* latestPhong;
    material* currMaterial;
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
                eye = point3D(x, y, z);
            }
            else if(strIn == "viewdir"){
                double x;
                double y;
                double z;
                infile >> x >> y >> z;
                viewdir = vector3D(x, y, z);
            }
            else if(strIn == "updir"){
                double x;
                double y;
                double z;
                infile >> x >> y >> z;
                updir = vector3D(x, y, z);
            }
            else if(strIn == "fov" || strIn == "vfov"){
                infile >> fov;
            }
            else if(strIn == "imsize"){
                infile >> width >> height;
            }
            else if(strIn == "bkgcolor"){
                double r;
                double g;
                double b;
                infile >> r >> g >> b;
                environment->setBackgroundColor(color(r, g, b));
            }
            else if(strIn == "mtlcolor"){
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
                    currMaterial = new flat_material(color(tempDoubles[0], tempDoubles[1], tempDoubles[2]));
                }
                else if(numDoubles == 10){
                    color baseColor = color(tempDoubles[0], tempDoubles[1], tempDoubles[2]);
                    color spotColor = color(tempDoubles[3], tempDoubles[4], tempDoubles[5]);
                    latestPhong = new Phong_material(baseColor, spotColor, tempDoubles[6], tempDoubles[7], tempDoubles[8], tempDoubles[9]);
                    currMaterial = latestPhong;
                }
                else{
                    cout << "invalid material";
                    break;
                }
                environment->addMaterial(currMaterial);
            }
            else if(strIn == "sphere"){
                double x;
                double y;
                double z;
                double r;
                infile >> x >> y >> z >> r;
                environment->addShape(new sphere(point3D(x, y, z), r, currMaterial));
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
                environment->addShape(new cylinder(point3D(px, py, pz), vector3D(vx, vy, vz), r, h, currMaterial));
            }
            else if(strIn == "parallel"){
                throw invalid_argument("parallel keyword not implimented");
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
                    environment->addLight(new directional_light(vector3D(x, y, z), lightColor));
                    break;
                case 1:
                    environment->addLight(new point_light(point3D(x, y, z), lightColor));
                    break;
                default:
                    throw invalid_argument("Light types must be 0 or 1");
                    break;
                }
            }
            else if(strIn == "v"){
                double x;
                double y;
                double z;
                infile >> x >> y >> z;
                environment->addVertex(new point3D(x, y, z));
            }
            else if(strIn == "f"){
                string instring;
                int nums[] = {0,0,0,0,0,0,0,0,0};
                getline(infile, instring);
                int j = 0;
                int faceType = 0;
                for(int i = 1; i < instring.length(); i++){
                    switch(instring.at(i)){
                        case '0':
                            nums[j] = nums[j]*10 + 0;
                            break;
                        case '1':
                            nums[j] = nums[j]*10 + 1;
                            break;
                        case '2':
                            nums[j] = nums[j]*10 + 2;
                            break;
                        case '3':
                            nums[j] = nums[j]*10 + 3;
                            break;
                        case '4':
                            nums[j] = nums[j]*10 + 4;
                            break;
                        case '5':
                            nums[j] = nums[j]*10 + 5;
                            break;
                        case '6':
                            nums[j] = nums[j]*10 + 6;
                            break;
                        case '7':
                            nums[j] = nums[j]*10 + 7;
                            break;
                        case '8':
                            nums[j] = nums[j]*10 + 8;
                            break;
                        case '9':
                            nums[j] = nums[j]*10 + 9;
                            break;
                        case '/':
                            if(instring.at(i+1) == '/'){
                                faceType = 1;
                            }
                        case ' ':
                            j++;
                            break;
                        default:
                            throw invalid_argument("Invalid triangle face type");
                            break;
                    }
                }
                j++;
                /**
                 cout << "parsing result " << endl;
                 for(int i = 0; i < 9; i++){
                    cout << "nums[" << i << "] = " << nums[i] << endl;
                 }
                 */
                if(j == 3){
                    environment->addFlatFace(nums, currMaterial);
                } else if(faceType == 1){
                    environment->addSmoothFace(nums, currMaterial);
                } else if((j == 6) && (faceType == 0)){
                    environment->addTexturedFlatFace(nums, currMaterial);
                } else if(j == 9){
                    environment->addTexturedSmoothFace(nums, currMaterial);
                }
                else {
                    cout << "face failed to read" << endl;
                }
            }
            else if(strIn == "vn") {
                double x;
                double y;
                double z;
                infile >> x >> y >> z;
                vector3D* normal = new vector3D(x, y, z);
                normal->normalize();
                environment->addNormal(normal);
            }
            else if(strIn == "vt") {
                double u;
                double v;
                infile >> u >> v;
                uvCord* newCord = new uvCord();
                newCord->u = u;
                newCord->v = v;
                environment->addTextureCord(newCord);
            }
            else if(strIn == "texture") {
                string filename;
                infile >> filename;
                string directory = "./texture/";
                directory.append(filename);
                ifstream textureFile;
                textureFile.open(directory);
                if (!textureFile.is_open() ) { 
                    cout << filename << " unable to be opened" << endl;
                }
                string junk;
                int texturewidth;
                int textureheight;
                textureFile >> junk >> texturewidth >> textureheight >> junk;
                texture_material* newTexture = new texture_material(texturewidth, textureheight, latestPhong);
                //latestPhong->printInfo();
                //newTexture->printInfo();
                double r;
                double g;
                double b;
                for(int i = 0; i < texturewidth*textureheight; i++){
                    textureFile >> r >> g >> b;
                    newTexture->textureData[i] = color(r/255.0,g/255.0,b/255.0);
                }
                currMaterial = newTexture;
                environment->addMaterial(currMaterial);
                textureFile.close();
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
    camera cam = camera(eye, viewdir, updir, fov, width, height, environment);
    //If either given vector is a null vector or they are colinear, stop the program
    if(cam.isInvalid()){
        cout << "View and up directions are invalid" << endl;
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
        cam.castAllRays();
        //this is where the printing out the image
        //This has to be build from bottom to top because the rays start at the bottom left corner
        color* image = cam.getColors();
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
    delete environment;
    return 0;
}
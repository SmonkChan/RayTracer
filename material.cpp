#include "material.h"

Phong_material::Phong_material(color bColor, color highlight, double ka, double kd, double ks, double n){
    baseColor = bColor;
    specularHighlight = highlight;
    specularA = ka;
    specularD = kd;
    specularS = ks;
    specularExponent = n;
}

Phong_material::Phong_material(){
    baseColor = color(0,0,0);
    specularHighlight = color(0,0,0);
    specularA = 0;
    specularD = 0;
    specularS = 0;
    specularExponent = 0; 
}

double max(double x, double y){
    if(x > y){return x;}
    else{return y;}
}

color Phong_material::phong_illumination(color colorAtPoint, point3D rayOrigin, point3D intersection, shape* intersectedShape, scene* environment){
    //Cacluating the ambient lighting as a base color
    double redComp = (specularA*colorAtPoint.getRed());
    double greenComp = (specularA*colorAtPoint.getGreen());
    double blueComp = (specularA*colorAtPoint.getBlue());

    raycaster rays = raycaster();
    for(int i = 0; i < environment->numLights; i++){
        //for each light source we check if there is a shadow
        //then we calculate the the influence it has on the color of the pixel
        vector3D lightDir = environment->allLights[i]->getLightDirection(intersection);
        double distance = environment->allLights[i]->distanceFromLight(intersection);
        rays.shootRay(intersection, lightDir, distance, environment);
        color lightShadow;
        if(distance < environment->allLights[i]->distanceFromLight(intersection)){
            lightShadow = color(0,0,0);
        }
        else{
            lightShadow = environment->allLights[i]->getLightColor(distance);
        }
        vector3D normal = intersectedShape->findNormal(intersection, rayOrigin);
        double kdNL = specularD*normal.dotProduct(lightDir);
        vector3D H = (lightDir + ((rayOrigin-intersection).getNormalVector())).multiplyByScalar(0.5);
        double magnitude = H.magnitude();
        if(fabs(magnitude) > 0.00000000001){H = H.multiplyByScalar(1/magnitude);}
        double ksNH = specularS*pow(normal.dotProduct(H), specularExponent);
        redComp += max(0,lightShadow.getRed())*(max(0,(colorAtPoint.getRed()*kdNL)) + max(0, specularHighlight.getRed()*ksNH));
        greenComp += max(0,lightShadow.getGreen())*(max(0,(colorAtPoint.getGreen()*kdNL)) + max(0, specularHighlight.getGreen()*ksNH));
        blueComp += max(0,lightShadow.getBlue())*(max(0,(colorAtPoint.getBlue()*kdNL)) + max(0, specularHighlight.getBlue()*ksNH));
    }
    if (redComp > 1){redComp = 1;}
    if (greenComp > 1){greenComp = 1;}
    if (blueComp > 1){blueComp = 1;}
    return color(redComp, greenComp, blueComp);
}

color Phong_material::calculateColor(point3D rayOrigin, point3D intersection, shape* intersectedShape, scene* environment){
    color result_color = phong_illumination(baseColor, rayOrigin, intersection, intersectedShape, environment);
    return result_color;
}

texture_material::texture_material(int width, int height, Phong_material* material_properties) {
    imWidth = width;
    imHeight = height;
    textureData = new color[width*height];
    this->specularHighlight = material_properties->specularHighlight;
    this->specularA = material_properties->specularA;
    this->specularD = material_properties->specularD;
    this->specularS = material_properties->specularS;
    this->specularExponent = material_properties->specularExponent;
}

texture_material::~texture_material(){
    delete[] textureData;
}

color texture_material::calculateColor(point3D rayOrigin, point3D intersection, shape* intersectedShape, scene* environment) {
    double width_cord = 0;
    double height_cord = 0;
    intersectedShape->getTextureCords(intersection, width_cord, height_cord);
    //std::cout << "width_cord: " << width_cord << std::endl;
    //std::cout << "height_cord: " << height_cord << std::endl;
    color colorAtPoint =  textureData[(int)(round(width_cord*imWidth) + round(height_cord*imHeight)*imWidth)];
    //std::cout << "color at point: " << colorAtPoint.getString() << std::endl;
    color result_color = phong_illumination(colorAtPoint, rayOrigin, intersection, intersectedShape, environment);
    //std::cout << "result color: " << result_color.getString() << std::endl;
    return result_color;
}

void flat_material::printInfo() {
    std::cout << "Flat Material Info:" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Base Color:         " << baseColor.getString() << std::endl << std::endl;
}

void Phong_material::printInfo() {
    std::cout << "Phong Material Info:" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Base Color:         " << baseColor.getString() << std::endl;
    std::cout << "Specular Highlight: " << specularHighlight.getString() << std::endl;
    std::cout << "Specular Ambient:   " << specularA << std::endl;
    std::cout << "Specular Difuse:    " << specularD << std::endl;
    std::cout << "Specular Spotlight: " << specularS << std::endl;
    std::cout << "Specular Exponent:  " << specularExponent << std::endl << std::endl;
}

void texture_material::printInfo() {
    std::cout << "Texture Material Info:" << std::endl;
    std::cout << "================================" << std::endl;
    std::cout << "Image Width:        " << imWidth << std::endl;
    std::cout << "Image Height:       " << imHeight << std::endl;
    std::cout << "Specular Highlight: " << specularHighlight.getString() << std::endl;
    std::cout << "Specular Ambient:   " << specularA << std::endl;
    std::cout << "Specular Difuse:    " << specularD << std::endl;
    std::cout << "Specular Spotlight: " << specularS << std::endl;
    std::cout << "Specular Exponent:  " << specularExponent << std::endl << std::endl;
}
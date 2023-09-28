#include "material.h"

material::material(color base){
    baseColor = base;
}

color material::calculateColor(){
    return baseColor;
}

color material::calculateColor(point3D rayOrigin, point3D intersection, lightsource** allLights, color* lightShadow, vector3D* lightDirection, int numLights, vector3D normal){
    return baseColor;
}

Phong_material::Phong_material(color baseColor, color highlight, double ka, double kd, double ks, double n){

}

double max(double x, double y){
    if(x > y){return x;}
    else{return y;}
}

color Phong_material::calculateColor(point3D rayOrigin, point3D intersection, lightsource** allLights, color* lightShadow, vector3D* lightDirection, int numLights, vector3D normal){

    //Cacluating the ambient lighting as a base color
    double redComp = (specularA*baseColor.getRed());
    double greenComp = (specularA*baseColor.getGreen());
    double blueComp = (specularA*baseColor.getBlue());

    for(int i = 0; i < numLights; i++){
        //for each light source we check if there is a shadow
        //then we calculate the the influence it has on the color of the pixel
        vector3D lightDir = lightDirection[i];
        double kdNL = specularD*normal.dotProduct(lightDir);
        vector3D H = ((lightDir + (rayOrigin-intersection).getNormalVector()).multiplyByScalar(0.5)).getNormalVector();
        double ksNH = specularS*pow(normal.dotProduct(H), specularExponent);
        redComp += lightShadow->getRed()*(max(0,(baseColor.getRed()*kdNL)) + max(0, specularHighlight.getRed()*ksNH));
        greenComp += lightShadow->getGreen()*(max(0,(baseColor.getGreen()*kdNL)) + max(0, specularHighlight.getGreen()*ksNH));
        blueComp += lightShadow->getBlue()*(max(0,(baseColor.getBlue()*kdNL)) + max(0, specularHighlight.getBlue()*ksNH));
    }

    return color(redComp, greenComp, blueComp);
}
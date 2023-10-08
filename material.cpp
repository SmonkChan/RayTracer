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

Phong_material::Phong_material(color bColor, color highlight, double ka, double kd, double ks, double n){
    baseColor = bColor;
    specularHighlight = highlight;
    specularA = ka;
    specularD = kd;
    specularS = ks;
    specularExponent = n;
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
        vector3D H = (lightDir + ((rayOrigin-intersection).getNormalVector())).multiplyByScalar(0.5);
        double magnitude = H.magnitude();
        if(magnitude != 0){H = H.multiplyByScalar(1/magnitude);}
        double ksNH = specularS*pow(normal.dotProduct(H), specularExponent);
        redComp += max(0,lightShadow[i].getRed())*(max(0,(baseColor.getRed()*kdNL)) + max(0, specularHighlight.getRed()*ksNH));
        greenComp += max(0,lightShadow[i].getGreen())*(max(0,(baseColor.getGreen()*kdNL)) + max(0, specularHighlight.getGreen()*ksNH));
        blueComp += max(0,lightShadow[i].getBlue())*(max(0,(baseColor.getBlue()*kdNL)) + max(0, specularHighlight.getBlue()*ksNH));
    }
    if (redComp > 1){redComp = 1;}
    if (greenComp > 1){greenComp = 1;}
    if (blueComp > 1){blueComp = 1;}
    return color(redComp, greenComp, blueComp);
}
#include "material.h"

material::material(color base){
    baseColor = base;
}

color material::calculateColor(){
    return baseColor;
}

Phong_material::Phong_material(color baseColor, color highlight, double ka, double kd, double ks, double n){

}

double max(double x, double y){
    if(x > y){return x;}
    else{return y;}
}

color Phong_material::calculateColor(point3D eye, point3D intersection, lightsource* light, vector3D normal){
    vector3D lightDir = light->getLightDirection(intersection);
    double kdNL = specularD*normal.dotProduct(lightDir);
    vector3D H = ((lightDir + (eye-intersection).getNormalVector()).multiplyByScalar(0.5)).getNormalVector();
    double ksNH = specularS*pow(normal.dotProduct(H), specularExponent);

    double redComp = (specularA*baseColor.getRed()) + max(0,(baseColor.getRed()*kdNL)) + (specularHighlight.getRed()*ksNH);
    double greenComp = (specularA*baseColor.getGreen()) + max(0,(baseColor.getGreen()*kdNL)) + (specularHighlight.getGreen()*ksNH);
    double blueComp = (specularA*baseColor.getBlue()) + max(0,(baseColor.getBlue()*kdNL)) + (specularHighlight.getBlue()*ksNH);
    return color(redComp, greenComp, blueComp);
}
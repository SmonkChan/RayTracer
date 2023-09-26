#include "material.h"

material::material(color base){
    baseColor = base;
}

color material::calculateColor(){
    return baseColor;
}

Phong_material::Phong_material(color baseColor, color highlight, double ka, double kd, double ks, double n){

}

color Phong_material::calculateColor(point3D intersection, lightsource light){
    return color(0.0,0.0,0.0);
}
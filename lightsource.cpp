#include "lightsource.h"

directional_light::directional_light(vector3D v, color c){
    lightDirection = v;
}

vector3D directional_light::getLightDirection(point3D p){
    return lightDirection;
}

point_light::point_light(point3D p, color c){
    lightOrigin = p;
}

vector3D point_light::getLightDirection(point3D p){
    return (lightOrigin-p).getNormalVector();
}
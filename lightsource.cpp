#include "lightsource.h"

directional_light::directional_light(vector3D v, color c){
    lightDirection = v;
}

vector3D directional_light::getLightDirection(point3D p){
    return lightDirection;
}

double directional_light::distanceFromLight(point3D p){{return INFINITY;}}

point_light::point_light(point3D p, color c){
    lightOrigin = p;
}

vector3D point_light::getLightDirection(point3D p){
    return (lightOrigin-p).getNormalVector();
}

double point_light::distanceFromLight(point3D p){
    return (lightOrigin-p).magnitude();
}

attenuated_light::attenuated_light(point3D p, color c, double C1, double C2, double C3){
    lightOrigin = p;
    lightColor = c;
    c1 = C1;
    c2 = C2;
    c3 = C3;
}

color attenuated_light::getLightColor(double distance){
    double red = lightColor.getRed()/(c1 + c2*distance + pow(c3*distance, 2));
    double green = lightColor.getGreen()/(c1 + c2*distance + pow(c3*distance, 2));
    double blue = lightColor.getBlue()/(c1 + c2*distance + pow(c3*distance, 2));
    return color(red, green, blue);
}
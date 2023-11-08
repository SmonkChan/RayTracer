#ifndef VECTOR_H
#define VECTOR_H
#include <tuple>
#include<string>
//Vector defines the vector class that is used extensivly 
//Contains basic constructors and methods as well as methods to use with vectors
//such as cross product and dot product
class vector3D{
    private:
        double v[3];
    public:
        vector3D();
        vector3D(double Vx, double Vy, double Vz);
        vector3D(const vector3D& vector2);
        ~vector3D();

        //getters and setters
        double getX();
        double getY();
        double getZ();

        //Other useful methods
        void operator=(const vector3D& vector2);
        vector3D operator+(vector3D v2);
        vector3D operator-(vector3D v2);
        vector3D crossProduct(vector3D v2);
        double dotProduct(vector3D v2);
        double magnitude();
        vector3D multiplyByScalar(double scalar);
        void normalize();
        vector3D getNormalVector();
        bool isNullVector();
        bool isColinear(vector3D v2);

        std::string printVector();
};
#endif
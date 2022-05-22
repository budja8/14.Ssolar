#ifndef SUN_H
#define SUN_H
#include "Object.hpp"
#include <armadillo>

#pragma once

class Sun : public Object 
{
public:
    Sun(string file, float size, float r, float g, float b, float ka, float kd);
    void draw(float Ia, float Ip, arma::frowvec3 F);
    arma::Mat<double> transf();
private:
    float r, g, b;
    float size;
    float ka, kd;
    arma::Mat<double> s_transf;
};

#endif
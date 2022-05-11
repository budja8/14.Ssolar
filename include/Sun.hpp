#ifndef SUN_H
#define SUN_H
#include "Object.hpp"
#include <armadillo>

#pragma once

class Sun : public Object 
{
public:
    Sun(string file, float size, float r, float g, float b);
    void draw();
    arma::Mat<double> transf();
private:
    float r, g, b;
    float size;
    arma::Mat<double> s_transf;
};

#endif
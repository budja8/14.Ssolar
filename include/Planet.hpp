#ifndef PLANET_H
#define PLANET_H
#include "Object.hpp"
#include "Transformaciones.hpp"
#include <armadillo>

#pragma once

class Planet : public Object {
public:
    Planet(string file, float rotation, float speed, float distance, float size, float r, float g, float b, arma::Mat<double> sun_transf);
    void draw();
    void draw(arma::Mat<double> transf);
    arma::Mat<double> transf();
private:
    float rotation;
    float speed;
    float distance;
    float size;
    float r, g, b;
    Transformaciones Tr;
    arma::Mat<double> sun_transf;
    arma::Mat<double> t_transf;
};

#endif
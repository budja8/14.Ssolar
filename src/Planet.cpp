#include "../include/Planet.hpp"
#include <GL/glu.h>


Planet::Planet(string file, float rotation, float speed, float distance, float size, float r, float g, float b, arma::Mat<double> sun_transf, float ka, float kd) : Object(file)
{
    this->rotation = rotation;
    this->speed = speed;
    this->distance = distance;
    this->size = size;
    this->r = r;    
    this->g = g;
    this->b = b;
    this->ka = ka;
    this->kd = kd;
    this->sun_transf = sun_transf;    
}

void Planet::draw(float Ia, float Ip, arma::frowvec3 F){
    // Dibujar Planeta
    this->rotation = (this->rotation < 360.0f) ? this->rotation + this->speed : 0.0f;
    arma::Mat<double> p_transf = sun_transf * Tr.Ry(this->rotation) * Tr.T(this->distance, 0.0, 0.0) * Tr.S(this->size, this->size, this->size);

    vector<Face> planeta_faces = getFaces();
    vector<Vertex> planeta_vertices = getVertex();

    glBegin(GL_TRIANGLES);
    for (Face f : planeta_faces)
    {
        arma::frowvec3 N = f.getNormal();
        arma::frowvec3 V = {planeta_vertices[f.getIndVertex()[0]].getX(),
                            planeta_vertices[f.getIndVertex()[0]].getY(),
                            planeta_vertices[f.getIndVertex()[0]].getZ()};
        arma::frowvec3 L = F - V;
        L = arma::normalise(L);
        float costheta = arma::dot(N, L);
        float I = (Ia * this->ka) + (Ip * this->kd * costheta);

        float rl = this->r * I;
        float gl = this->g * I;
        float bl = this->b * I;

        glColor3f(rl, gl, bl);
        // Recorrer los vértices de la cara
        for (long v_ind : f.getIndVertex())
        {
            // Dibujar el objeto....
            arma::Col<double> vp = p_transf * planeta_vertices[v_ind].homg();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
    }
    glEnd();
    // Fin dibujado de Planeta
}

void Planet::draw(arma::Mat<double> transf, float Ia, float Ip, arma::frowvec3 F){
    // Dibujar Planeta
    this->rotation = (this->rotation < 360.0f) ? this->rotation + this->speed : 0.0f;
    arma::Mat<double> p_transf = transf * Tr.Ry(this->rotation) * Tr.T(this->distance, 0.0, 0.0) * Tr.S(this->size, this->size, this->size);

    vector<Face> planeta_faces = getFaces();
    vector<Vertex> planeta_vertices = getVertex();

    //glColor3f(this->r, this->g, this->b);
    glBegin(GL_TRIANGLES);
    for (Face f : planeta_faces)
    {
        arma::frowvec3 N = f.getNormal();
        arma::frowvec3 V = {planeta_vertices[f.getIndVertex()[0]].getX(),
                            planeta_vertices[f.getIndVertex()[0]].getY(),
                            planeta_vertices[f.getIndVertex()[0]].getZ()};
        arma::frowvec3 L = F - V;
        L = arma::normalise(L);
        float costheta = arma::dot(N, L);
        float I = (Ia * this->ka) + (Ip * this->kd * costheta);

        float rl = this->r * I;
        float gl = this->g * I;
        float bl = this->b * I;
        
        glColor3f(rl, gl, bl);
        // Recorrer los vértices de la cara
        for (long v_ind : f.getIndVertex())
        {
            // Dibujar el objeto....
            arma::Col<double> vp = p_transf * planeta_vertices[v_ind].homg();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
    }
    glEnd();
    // Fin dibujado de Planeta
}

arma::Mat<double> Planet::transf(){
    this->rotation = (this->rotation < 360.0f) ? this->rotation + this->speed : 0.0f;
    arma::Mat<double> p_transf = sun_transf * Tr.Ry(this->rotation) * Tr.T(this->distance, 0.0, 0.0) * Tr.S(this->size, this->size, this->size);

    this->t_transf = p_transf;
    return t_transf;
}
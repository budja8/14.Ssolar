#include "../include/Sun.hpp"
#include "../include/Transformaciones.hpp"
#include <GL/glu.h>

Sun::Sun(string file, float size, float r, float g, float b, float ka, float kd) : Object(file)
{
    this->size = size;
    this->r = r;
    this->g = g;
    this->b = b;
    this->ka = ka;
    this->kd = kd;
}

void Sun::draw(float Ia, float Ip, arma::frowvec3 F){
    vector<Face> sol_faces = getFaces();
    vector<Vertex> sol_vertices = getVertex();
    
    glBegin(GL_TRIANGLES);
    for (Face f : sol_faces)
    {
        arma::frowvec3 N = f.getNormal();
        arma::frowvec3 V = {sol_vertices[f.getIndVertex()[0]].getX(),
                            sol_vertices[f.getIndVertex()[0]].getY(),
                            sol_vertices[f.getIndVertex()[0]].getZ()};
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
            arma::Col<double> vp = this->s_transf * sol_vertices[v_ind].homg();
            glVertex3f(vp.at(0), vp.at(1), vp.at(2));
        }
    }
    glEnd();
    // Fin dibujado del Sol
}

arma::Mat<double> Sun::transf(){
    Transformaciones Tr;
    arma::Mat<double> s_transf = Tr.S(size, size, size);
    this->s_transf = s_transf;

    return s_transf;
}
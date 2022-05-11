#include "../include/Sun.hpp"
#include "../include/Transformaciones.hpp"
#include <GL/glu.h>

Sun::Sun(string file, float size, float r, float g, float b) : Object(file)
{
    this->size = size;
    this->r = r;
    this->g = g;
    this->b = b;
}

void Sun::draw(){
    vector<Face> sol_faces = getFaces();
    vector<Vertex> sol_vertices = getVertex();
    
    glColor3f(this->r, this->g, this->b);
    glBegin(GL_TRIANGLES);
    for (Face f : sol_faces)
    {
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
#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "include/Planet.hpp"
#include "include/Sun.hpp"
#include "include/Transformaciones.hpp" 

using namespace std;

int main(void)
{
    arma::frowvec eye = {0.0, 0.0, 10.0};
    arma::frowvec camera = {0.0, 0.0, 0.0};
    GLFWwindow *window;
    
    //                       (model, size,  r,   g, b)
    Sun sol = Sun("models/golf.ply", 0.4, 1.0, 1.0, 0.0);
    arma::Mat<double> s_transf = sol.transf();

    //                                (model,  rot, spd, dist, size,  r,   g,  b,  s_transf)
    Planet mercurio = Planet("models/golf.ply", 0.0f, 6.0, -0.6, 0.07, 1.0, 0.5, 0.0, s_transf);
    Planet venus = Planet("models/golf.ply", 0.0f, 4.0, -0.8, 0.1, 0.9, 0.68, 0.09, s_transf);
    Planet tierra = Planet("models/golf.ply", 0.0f, 2.0, -1.1, 0.16, 0.0, 0.0, 1.0, s_transf);
    arma::Mat<double> t_transf = tierra.transf();  
    Planet luna = Planet("models/golf.ply", 0.0f, 5.0, -1.4, 0.3, 1.0, 1.0, 1.0, t_transf);
    Planet marte = Planet("models/putter.ply", 0.0f, 1.0, -1.3, 0.085, 1.0, 0.0, 0.0, s_transf);
    Planet jupiter = Planet("models/putter.ply", 0.0f, 0.8, -1.6, 0.47, 0.5, 0.25, 0.0, s_transf);
    Planet saturno = Planet("models/putter.ply", 0.0f, 0.5, -1.9, 0.32, 0.7, 0.6, 0.11, s_transf);
    Planet urano = Planet("models/putter.ply", 0.0f, 0.3, -2.2, 0.23, 0.11, 0.77, 0.77, s_transf);
    Planet neptuno = Planet("models/putter.ply", 0.0f, 0.1, -2.5, 0.2, 0.11, 0.53, 0.77, s_transf);

    if (!glfwInit())
    {
        cout << stderr << "Fallo al inicializar GLFW." << endl;
        getchar();
        return -1;
    }

    window = glfwCreateWindow(1024, 768, "Sistema Solar", NULL, NULL);
    if (window == NULL)
    {
        cout << stderr << "Fallo al abrir la ventana de GLFW." << endl;
        getchar();
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    //  Proyecciones
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ar = width / height;

    //  Proyección en paralelo
    glViewport(0, 0, width, height);
    glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);

    //  Proyección en perspectiva
    //    glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2],
                  camera[0], camera[1], camera[2],
                  0.0, 1.0, 0.0);

        sol.draw();
        mercurio.draw();
        venus.draw();
        tierra.draw();
        arma::Mat<double> t_transf = tierra.transf();  
        luna.draw(t_transf);
        marte.draw();
        jupiter.draw();
        saturno.draw();
        urano.draw();
        neptuno.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    glfwTerminate();

    return 0;
}
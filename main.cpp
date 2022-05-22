#include <GL/glu.h>
#include <GLFW/glfw3.h>
#include <armadillo>
#include "include/Planet.hpp"
#include "include/Sun.hpp"
#include "include/Transformaciones.hpp" 

using namespace std;

int main(void)
{
    GLFWwindow *window;
    //                       (model, size,  r,   g,  b,   ka,  kd)
    Sun sol = Sun("models/roca.ply", 0.4, 1.0, 1.0, 0.0, 0.9, 0.9);
    arma::Mat<double> s_transf = sol.transf();

    //                             (model, rot, spd, dist, size, r,  g,   b,  s_transf,  ka, kd)
    Planet mercurio = Planet("models/roca.ply", 0.0f, 6.0, -0.6, 0.07, 1.0, 0.5, 0.0, s_transf, 0.9, 0.8);
    Planet venus = Planet("models/roca.ply", 0.0f, 4.0, -0.8, 0.1, 0.9, 0.68, 0.09, s_transf, 0.8, 0.7);
    Planet tierra = Planet("models/roca.ply", 0.0f, 2.0, -1.1, 0.16, 0.0, 0.0, 1.0, s_transf, 0.7, 0.6);
    arma::Mat<double> t_transf = tierra.transf();  
    Planet luna = Planet("models/roca.ply", 0.0f, 5.0, -1.4, 0.3, 1.0, 1.0, 1.0, t_transf, 0.6, 0.6);
    Planet marte = Planet("models/roca.ply", 0.0f, 1.0, -1.3, 0.085, 1.0, 0.0, 0.0, s_transf, 0.5, 0.6);
    Planet jupiter = Planet("models/roca.ply", 0.0f, 0.8, -1.6, 0.47, 0.5, 0.25, 0.0, s_transf, 0.4, 0.5);
    Planet saturno = Planet("models/roca.ply", 0.0f, 0.5, -1.9, 0.32, 0.7, 0.6, 0.11, s_transf, 0.4, 0.5);
    Planet urano = Planet("models/roca.ply", 0.0f, 0.3, -2.2, 0.23, 0.11, 0.77, 0.77, s_transf, 0.3, 0.5);
    Planet neptuno = Planet("models/roca.ply", 0.0f, 0.1, -2.5, 0.2, 0.11, 0.53, 0.77, s_transf, 0.3, 0.5);

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

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    arma::frowvec eye = {0.0, 0.0, 10.0};
    arma::frowvec camera = {0.0, 0.0, 0.0};
    arma::frowvec vup = {0.0, 1.0, 0.0};

    float Ia = 0.9;
    float Ip = 0.8; //Intensidad del foco
    arma::frowvec F = {0.0, 10.0, 0.0};

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(eye[0], eye[1], eye[2], //posicion de eye
                  camera[0], camera[1], camera[2],//posicion a la que apunta eye
                  vup[0], vup[1], vup[2]); //vup   

        if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
            eye = {0.0, 10.0, 0.0};
            vup = {0.0, 0.0, -1.0};
        }else if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
            eye = {10.0, 0.0, 10.0};
            vup = {0.0, 1.0, 0.0};
        }else if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
            eye = {0.0, -10.0, 0.0};
            vup = {0.0, 0.0, -1.0};
        }

        //Proyecciones
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        int width, height;
        glfwGetFramebufferSize(window, &width, &height);

        float ar = width / height;

        //Proyección en paralelo
        glViewport(0, 0, width, height);
        //     izq, der, down, up,   near, far 
        glOrtho(-ar, ar, -1.0, 1.0, -20.0, 20.0);

        //Proyección en perspectiva
        //glFrustum(-ar, ar, -ar, ar, 2.0, 4.0);

        sol.draw(Ia, Ip, F);
        mercurio.draw(Ia, Ip, F);
        venus.draw(Ia, Ip, F);
        tierra.draw(Ia, Ip, F);
        arma::Mat<double> t_transf = tierra.transf();  
        luna.draw(t_transf, Ia, Ip, F);
        marte.draw(Ia, Ip, F);
        jupiter.draw(Ia, Ip, F);
        saturno.draw(Ia, Ip, F);
        urano.draw(Ia, Ip, F);
        neptuno.draw(Ia, Ip, F);

        glfwSwapBuffers(window);
        glfwPollEvents();

    } while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
             glfwWindowShouldClose(window) == 0);

    glfwTerminate();

    return 0;
}
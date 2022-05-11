#include <iostream>
#include "../include/Face.hpp"  

using namespace std;

Face::Face(vector<unsigned int> vectex_indices){
    this->vectex_indices = vectex_indices;
}

void Face::print(){
    int salto = 0;
    for(int i=0; i<this->vectex_indices.size(); i++){
        salto++;
        cout << this->vectex_indices[i] << " ";
        if(salto==3){
            cout << endl;
            salto=0;
        }
    }
}

vector<unsigned long> Face::getIndVertex(){
    int salto = 0;
    vector<unsigned long> lista;
    for(int i=0; i<this->vectex_indices.size(); i++){
        salto++;
        lista.push_back(vectex_indices[i]);
        if(salto==3){
            cout << endl;
            salto=0;
        }
    }
    return(lista);
}

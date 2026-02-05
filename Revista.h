#ifndef REVISTA_H
#define REVISTA_H

#include "Material.h"

using namespace std;
class Revista : public Material {
    private:
    int numEdicion;
    string mesPublicacion;

    public: 
    Revista(string titulo, string codigoidentificador, string autor, int numEdicion, string mesPublicacion)
        : Material(titulo, codigoidentificador, autor), numEdicion(numEdicion), mesPublicacion(mesPublicacion) {}

    int calcularDiasPrestamo() const override {return 0;} // return 0 porque las revistas no se prestan
    void mostrarInformacion() const override {
        cout << "Titulo = " << titulo << endl;
        cout << "Codigo Identificador = " << codigoidentificador << endl;
        cout << "Autor = " << autor << endl;
        cout << "Numero de Edicion = " << numEdicion << endl;
        cout << "Mes de Publicacion = " << mesPublicacion << endl;
        cout << "Días de préstamo: Solo se consulta en sala" << endl;
        cout << "Estado: " << (disponible ? "Disponible" : "Prestado") << endl;
    }

    int getNumEdicion() const {return numEdicion;}
    string getMesPublicacion() const {return mesPublicacion;}
};







#endif
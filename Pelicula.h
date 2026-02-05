#ifndef PELI_H
#define PELI_H

#include "Material.h"

using namespace std;
class Pelicula : public Material{
    private:
    int duracionMinutos;
    string genero;

    public:
    Pelicula(string titulo, string codigoidentificador, string autor, int duracionMinutos, string genero)
        : Material(titulo, codigoidentificador, autor), duracionMinutos(duracionMinutos), genero(genero) {}

    int calcularDiasPrestamo() const override {return 3;} // return 3 porque las peliculas se prestan por 3 dias
    void mostrarInformacion() const override {
        cout << "Titulo = " << titulo << endl;
        cout << "Codigo Identificador = " << codigoidentificador << endl;
        cout << "Autor = " << autor << endl;
        cout << "Duracion en Minutos = " << duracionMinutos << endl;
        cout << "Genero = " << genero << endl;
        cout << "Días de préstamo: " << calcularDiasPrestamo() << endl;
        cout << "Estado: " << (disponible ? "Disponible" : "Prestado") << endl;
    }

    int getDuracionMinutos() const {return duracionMinutos;}
    string getGenero() const {return genero;}
};







#endif
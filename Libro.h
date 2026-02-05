#ifndef LIBRO_H
#define LIBRO_H

#include "Material.h"

using namespace std;

class Libro : public Material {  //colocamos a un lado de la clase hija la clase padre de la que va herdar sus atributos y metodos
    private:
    int numPaginas;
    string ISBN;

    public:
    Libro(string titulo, string codigoidentificador, string autor, int numPaginas, string isbn) 
        : Material(titulo, codigoidentificador, autor), numPaginas(numPaginas), ISBN(isbn) {}

    int calcularDiasPrestamo() const override {return 15;} // return 15 porque los libros se prestan 15 dias
    void mostrarInformacion() const override {
        cout << "Titulo = " << titulo << endl;
        cout << "Codigo Identificador = " << codigoidentificador << endl;
        cout << "Autor = " << autor << endl;
        cout << "Numero de Paginas = " << numPaginas << endl;
        cout << "ISBN = " << ISBN << endl;
        cout << "Días de préstamo: " << calcularDiasPrestamo() << endl;
        cout << "Estado: " << (disponible ? "Disponible" : "Prestado") << endl;
    }

    int getNumPaginas() const {return numPaginas;}
    string getISBN() const {return ISBN;}

};






#endif
#ifndef METERIAL_H
#define METERIAL_H
#include <iostream>
#include <string>

using namespace std;

class Material {
    protected:     // usamos portected para que las clases hijas puedan heredar lo que hay dentro
    string titulo;
    string codigoidentificador;    //las variables que van a heredar todas las clases hijas
    string autor;
    bool disponible;

    public:
        Material(string tit, string cod, string aut) : titulo(tit), codigoidentificador(cod), autor(aut), disponible(true) {}

        virtual ~Material() {}

        virtual int calcularDiasPrestamo() const = 0;
        virtual void mostrarInformacion() const = 0;
        
                            // todo esto lo heredan las clases hijas solo se le agragan los atributos extras

        string getTitulo() const {return titulo;}
        string getCodigoIdentificador() const {return codigoidentificador;}
        string getAutor() const {return autor;}
        bool estaDisponible() const {return disponible;}
        void setDisponible(bool disp){disponible = disp;}

        
};

#endif
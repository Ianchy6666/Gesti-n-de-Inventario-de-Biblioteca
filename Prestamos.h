#ifndef PRESTAMOS_H
#define PRESTAMOS_H 

#include "Material.h"

using namespace std;

class Prestamos {
    private:
        Material* material;
        string nombreUsuario;
        int diasdeprestamo;
        int diastranscurridos;

    public:  //esto va a calcular los dias de prestamo y las multas en caso de que existan
        Prestamos(Material* mat, string usuario) : material(mat), nombreUsuario(usuario), diastranscurridos(0) {
        diasdeprestamo = material->calcularDiasPrestamo();
    }

        void agregardias (int dias){
            diastranscurridos += dias;
        }
        int calculardiasderetraso() const {
            int retraso = diastranscurridos - diasdeprestamo;
            return(retraso > 0 ? retraso : 0);
        }
        double calcularmulta() const {  //esto calcula las multas para nada abusivas
            return calculardiasderetraso() * 100.0;
        }
        void devolver (){
            material->setDisponible(true);
        }
        void mostrarInformacion() const{
            cout << "Usuario = " << nombreUsuario << endl;
            cout << "Material = " << material->getTitulo() << endl;
            cout << "Codgio Identificador = " << material->getCodigoIdentificador() << endl;
            cout << "Autor = " << material->getAutor() << endl;
            cout << "Dias de Prestamo = " << diasdeprestamo << endl;
            cout << "Dias Transcurridos = " << diastranscurridos << endl;
            
            int retraso = calculardiasderetraso();
            if (retraso > 0) {
                cout << "Dias de Retrasop = " << retraso << endl;
                cout << "Multa = " << calcularmulta() << endl;
            } else {
                cout << "No hay retraso, aun..." << endl;

            }
        
        }
    Material* getMaterial() const {return material;}
    string getNombreUsuario() const {return nombreUsuario;}
    string getCodigoIdentificador() const {return material->getCodigoIdentificador();}
    int getdiasTranscurridos() const {return diastranscurridos;}
    int getdiasdeprestamo() const {return diasdeprestamo;}
    
};






#endif
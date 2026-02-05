#ifndef BIBLIOTECA_H
#define BIBLIOTECA_H

#include "Material.h"
#include "Revista.h"
#include "Libro.h"
#include "Pelicula.h"
#include "Prestamos.h"
#include <vector>

using namespace std;

class Biblioteca {
    private:
        vector<Material*> inventario;
        vector<Prestamos*> prestamoActivo;
        string nombreBiblioteca;


    public:              //con esto es como vamos a manejar todo el inventario
        Biblioteca (string nombre) : nombreBiblioteca(nombre){}
        ~Biblioteca(){
            for (Material* m : inventario) delete m;
            for (Prestamos* p : prestamoActivo) delete p;
        }
            
        void agregarMaterial(Material* material){   //esto agrega los materiales
            inventario.push_back(material);
            cout << "Material agregado " << endl;
        }
        Material* buscarMaterial(string codigo){   //esto buscar por su codigo
            for(Material* m : inventario) {
                if (m->getCodigoIdentificador() == codigo) return m;
            }
            return nullptr;
        }
        void mostrarInventario() const {  //esto muestra el inventario 
            cout << "Inventario de la biblioteca " << endl;
            if (inventario.empty()) {
                cout << "Inventario vacio" << endl;
                return;
            }
            for (size_t i = 0; i < inventario.size(); i++){
                cout << "[" << i + 1 << "]";
                inventario[i]->mostrarInformacion();
                
            }
            
        }
        bool procesarPrestamo(string codigo, string usuario) {  //esto preocesa los prestamos
            Material* material = buscarMaterial(codigo);
            if (!material) {
                cout << "Material no encontrado" << endl;
                return false;
            }
            if (!material->estaDisponible()) {
                cout << "Material no disponible" << endl;
                return false;
            }
            if (material->calcularDiasPrestamo() == 0){ // esto es por si alguin quiere pedir prestada una revista
                cout << "Las revistas solo se consultan en sala" << endl;
                return false;
            }
            Prestamos* prestamo = new Prestamos(material, usuario);
            prestamoActivo.push_back(prestamo);
            material->setDisponible(false);

            cout << "Prestamo exitoso" << endl;
            cout << "Usuario: "<< usuario << endl;
            cout << "Material: " << material->getTitulo() << endl;
            cout << "Dias de Prestamo: " << material->calcularDiasPrestamo() << endl;
            
            return true;
        }
        bool devolverMaterial(string codigo){    //esto es para devolver las cosas prestadas 
            for(auto it = prestamoActivo.begin(); it != prestamoActivo.end(); ++it){
                if((*it)->getCodigoIdentificador() == codigo) {
                    Prestamos* p = *it;
                    cout << "Devolucion procesada " << endl;
                    int retraso =p->calculardiasderetraso();
                    if (retraso > 0) {
                        cout << "Retraso: " << retraso << " dias" << endl;
                        cout << "Multa: " << p->calcularmulta() << endl;
                    } else {
                        cout << "No hay multa" << endl;
                    }
                    p->devolver();
                    delete p;
                    prestamoActivo.erase(it);
                    return true;
                }
            }
            cout << "Prestamo no encontrado" << endl;
            return false;
        }
        void mostrarPrestamosActivos() const {    //esto muestra los prestamos que esten activos
            cout << "Prestamos actuales" << endl;
            if (prestamoActivo.empty()) {
                cout << "No hay prestamos" << endl;
                return;
            }
            for (size_t i = 0; i < prestamoActivo.size(); i++){
                cout << "[" << i + 1 << "]";
                prestamoActivo[i]->mostrarInformacion();
            }
        }
        void simularDias(string codigo, int dias) const {   //esto simula los dias para no meter cosas mas complejas
            for(Prestamos* p : prestamoActivo)
                if (p->getCodigoIdentificador() == codigo) {
                    p->agregardias(dias);
                    cout << "Dias simulados: " << dias << endl;
                    return;
                }
            cout << "Prestamo no encontrado" << endl;
        }
        string getNombre() const {return nombreBiblioteca;}
        const vector<Material*>& getInventario() const {return inventario;}
        const vector<Prestamos*>& getPrestamoActivo() const {return prestamoActivo;}
};

#endif
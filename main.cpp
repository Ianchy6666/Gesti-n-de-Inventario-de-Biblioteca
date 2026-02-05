#include <iostream>
#include "Biblioteca.h"

using namespace std;

void mostrarMenu() {
    cout << "SISTEMA DE BIBLIOTECA" << endl;
    cout << "1.  Agregar Libro" << endl;
    cout << "2.  Agregar Revista" << endl;
    cout << "3.  Agregar Pelicula" << endl;
    cout << "4.  Mostrar Inventario" << endl;
    cout << "5.  Buscar Material" << endl;
    cout << "6.  Realizar Prestamo" << endl;
    cout << "7.  Devolver Material" << endl;
    cout << "8.  Mostrar Prestamos Activos" << endl;
    cout << "9.  Simular Dias" << endl;
    cout << "10. Salir" << endl;
    cout << "\nOpcion: ";
}

int main() {
    Biblioteca biblioteca("Biblioteca");   //Aqui llamamos a la clase biblioteca 
    int opcion;
        
    cout << "Bienvenido a " << biblioteca.getNombre() << "!" << endl;
    
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();
        
        string titulo, codigo, autor, extra;
        int numero;
        
        switch(opcion) {
            case 1: // Este caso es para los libros
                cout << "\nTítulo: "; getline(cin, titulo);
                cout << "Codigo: "; getline(cin, codigo);
                cout << "Autor: "; getline(cin, autor);
                cout << "ISBN: "; getline(cin, extra);
                cout << "Paginas: "; cin >> numero;
                biblioteca.agregarMaterial(new Libro(titulo, codigo, autor, numero, extra));
                break;
                
            case 2: // Este caso es para las revistas
                cout << "\nTitulo: "; getline(cin, titulo);
                cout << "Codigo: "; getline(cin, codigo);
                cout << "Editor: "; getline(cin, autor);
                cout << "Edicion: "; cin >> numero;
                cin.ignore();
                cout << "Mes: "; getline(cin, extra);
                biblioteca.agregarMaterial(new Revista(titulo, codigo, autor, numero, extra));
                break;
                
            case 3: // Este caso es para las peliculas
                cout << "\nTitulo: "; getline(cin, titulo);
                cout << "Codigo: "; getline(cin, codigo);
                cout << "Director: "; getline(cin, autor);
                cout << "Genero: "; getline(cin, extra);
                cout << "Duracion: "; cin >> numero;
                biblioteca.agregarMaterial(new Pelicula(titulo, codigo, autor, numero, extra));
                break;
                
            case 4: // Esto muestra el inventario
                biblioteca.mostrarInventario();
                break;
                
            case 5: // Esto es para buscar con el codigo
                cout << "\nCodigo: "; getline(cin, codigo);
                {
                    Material* m = biblioteca.buscarMaterial(codigo);
                    if (m) m->mostrarInformacion();
                    else cout << "\nNo encontrado." << endl;
                }
                break;
                
            case 6: // Esto es para hacer los prestamos
                cout << "\nCodigo: "; getline(cin, codigo);
                cout << "Usuario: "; getline(cin, autor);
                biblioteca.procesarPrestamo(codigo, autor);
                break;
                
            case 7: // Esto es para devolver los prestamos
                cout << "\nCodigo: "; getline(cin, codigo);
                biblioteca.devolverMaterial(codigo);
                break;
                
            case 8: // Esto muestra los prestamos activos
                biblioteca.mostrarPrestamosActivos();
                break;
                
            case 9: // Esto es para simular los dias para ver que sucede con los prestamos
                cout << "\nCodigo del prestamo: "; getline(cin, codigo);
                cout << "Daas para simular: "; cin >> numero;
                biblioteca.simularDias(codigo, numero);
                break;
                
            case 10:
                cout << "\nHasta pronto" << endl;
                break;
                
            default:
                cout << "\nOpcion invalida." << endl;
        }
        
    } while(opcion != 10);
    
    return 0;
}
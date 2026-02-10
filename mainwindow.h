#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QMessageBox>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include "Biblioteca.h"

using namespace std;

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void agregarMaterial();
    void actualizarInventario();
    void buscarMaterial();
    void realizarPrestamo();
    void devolverMaterial();
    void actualizarPrestamos();
    void simularDias();
    void cambiarTipo(int index);
    void eliminarMaterial();

private:
    Biblioteca* biblioteca;
    QTabWidget* tabs;

    QTableWidget* tablaInventario;
    QLineEdit* txtBuscar;

    QComboBox* comboTipo;
    QLineEdit *txtTitulo, *txtCodigo, *txtAutor;

    QWidget *widgetLibro, *widgetRevista, *widgetPelicula;
    QLineEdit *txtISBN, *txtMes, *txtGenero;
    QSpinBox *spinPaginas, *spinEdicion, *spinDuracion;

    QTableWidget* tablaPrestamos;
    QLineEdit *txtCodigoPrestamo, *txtUsuario, *txtCodigoSimular;
    QSpinBox* spinDias;

    void setupUI();
};

#endif

#include "mainwindow.h"
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    biblioteca = new Biblioteca("Biblioteca Central");

    setupUI();
    actualizarInventario();

    setWindowTitle("Sistema de Biblioteca");
    resize(900, 600);
}

MainWindow::~MainWindow() {
    delete biblioteca;
}

void MainWindow::setupUI() {
    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout* layout = new QVBoxLayout(central);

    QLabel* titulo = new QLabel("BIBLIOTECA");
    QFont font = titulo->font();
    font.setPointSize(16);
    font.setBold(true);
    titulo->setFont(font);
    titulo->setAlignment(Qt::AlignCenter);
    layout->addWidget(titulo);

    tabs = new QTabWidget();
    layout->addWidget(tabs);

    //Ver el inventario
    QWidget* tabInv = new QWidget();
    QVBoxLayout* layInv = new QVBoxLayout(tabInv);

    QHBoxLayout* buscarLay = new QHBoxLayout();
    buscarLay->addWidget(new QLabel("Buscar:"));
    txtBuscar = new QLineEdit();
    buscarLay->addWidget(txtBuscar);
    QPushButton* btnBuscar = new QPushButton("Buscar");
    buscarLay->addWidget(btnBuscar);
    QPushButton* btnEliminar = new QPushButton("Eliminar");
    btnEliminar->setStyleSheet("background-color: #e74c3c; color: white; padding: 4px;");
    buscarLay->addWidget(btnEliminar);
    QPushButton* btnActInv = new QPushButton("Recargar");
    buscarLay->addWidget(btnActInv);
    layInv->addLayout(buscarLay);

    tablaInventario = new QTableWidget();
    tablaInventario->setColumnCount(6);
    tablaInventario->setHorizontalHeaderLabels({"Código", "Título", "Autor", "Tipo", "Detalles", "Estado"});
    tablaInventario->horizontalHeader()->setStretchLastSection(true);
    tablaInventario->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layInv->addWidget(tablaInventario);

    connect(btnBuscar, &QPushButton::clicked, this, &MainWindow::buscarMaterial);
    connect(btnEliminar, &QPushButton::clicked, this, &MainWindow::eliminarMaterial);
    connect(btnActInv, &QPushButton::clicked, this, &MainWindow::actualizarInventario);

    tabs->addTab(tabInv, "Inventario");

    //Agregar un material
    QWidget* tabAdd = new QWidget();
    QVBoxLayout* layAdd = new QVBoxLayout(tabAdd);

    QGroupBox* group = new QGroupBox("Agregar Material");
    QVBoxLayout* formLay = new QVBoxLayout(group);

    QHBoxLayout* tipoLay = new QHBoxLayout();
    tipoLay->addWidget(new QLabel("Tipo:"));
    comboTipo = new QComboBox();
    comboTipo->addItems({"Libro", "Revista", "Película"});
    tipoLay->addWidget(comboTipo);
    formLay->addLayout(tipoLay);

    QHBoxLayout* titLay = new QHBoxLayout();
    titLay->addWidget(new QLabel("Título:"));
    txtTitulo = new QLineEdit();
    titLay->addWidget(txtTitulo);
    formLay->addLayout(titLay);

    QHBoxLayout* codLay = new QHBoxLayout();
    codLay->addWidget(new QLabel("Código:"));
    txtCodigo = new QLineEdit();
    codLay->addWidget(txtCodigo);
    formLay->addLayout(codLay);

    QHBoxLayout* autLay = new QHBoxLayout();
    autLay->addWidget(new QLabel("Autor/Director:"));
    txtAutor = new QLineEdit();
    autLay->addWidget(txtAutor);
    formLay->addLayout(autLay);

    widgetLibro = new QWidget();
    QVBoxLayout* libroLay = new QVBoxLayout(widgetLibro);
    QHBoxLayout* isbnLay = new QHBoxLayout();
    isbnLay->addWidget(new QLabel("ISBN:"));
    txtISBN = new QLineEdit();
    isbnLay->addWidget(txtISBN);
    libroLay->addLayout(isbnLay);
    QHBoxLayout* pagsLay = new QHBoxLayout();
    pagsLay->addWidget(new QLabel("Páginas:"));
    spinPaginas = new QSpinBox();
    spinPaginas->setRange(1, 10000);
    pagsLay->addWidget(spinPaginas);
    libroLay->addLayout(pagsLay);

    widgetRevista = new QWidget();
    QVBoxLayout* revistaLay = new QVBoxLayout(widgetRevista);
    QHBoxLayout* edLay = new QHBoxLayout();
    edLay->addWidget(new QLabel("Edición:"));
    spinEdicion = new QSpinBox();
    spinEdicion->setRange(1, 10000);
    edLay->addWidget(spinEdicion);
    revistaLay->addLayout(edLay);
    QHBoxLayout* mesLay = new QHBoxLayout();
    mesLay->addWidget(new QLabel("Mes:"));
    txtMes = new QLineEdit();
    mesLay->addWidget(txtMes);
    revistaLay->addLayout(mesLay);
    widgetRevista->hide();

    widgetPelicula = new QWidget();
    QVBoxLayout* peliLay = new QVBoxLayout(widgetPelicula);
    QHBoxLayout* genLay = new QHBoxLayout();
    genLay->addWidget(new QLabel("Género:"));
    txtGenero = new QLineEdit();
    genLay->addWidget(txtGenero);
    peliLay->addLayout(genLay);
    QHBoxLayout* durLay = new QHBoxLayout();
    durLay->addWidget(new QLabel("Duración:"));
    spinDuracion = new QSpinBox();
    spinDuracion->setRange(1, 1000);
    durLay->addWidget(spinDuracion);
    peliLay->addLayout(durLay);
    widgetPelicula->hide();

    formLay->addWidget(widgetLibro);
    formLay->addWidget(widgetRevista);
    formLay->addWidget(widgetPelicula);

    QPushButton* btnAdd = new QPushButton("Agregar");
    btnAdd->setStyleSheet("background-color: #27ae60; color: white; padding: 8px;");
    formLay->addWidget(btnAdd);

    layAdd->addWidget(group);
    layAdd->addStretch();

    connect(comboTipo, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::cambiarTipo);
    connect(btnAdd, &QPushButton::clicked, this, &MainWindow::agregarMaterial);

    tabs->addTab(tabAdd, "Agregar");

    //Para los préstamos
    QWidget* tabPres = new QWidget();
    QVBoxLayout* layPres = new QVBoxLayout(tabPres);

    QGroupBox* groupPres = new QGroupBox("Préstamo/Devolución");
    QVBoxLayout* formPres = new QVBoxLayout(groupPres);

    QHBoxLayout* codPresLay = new QHBoxLayout();
    codPresLay->addWidget(new QLabel("Código:"));
    txtCodigoPrestamo = new QLineEdit();
    codPresLay->addWidget(txtCodigoPrestamo);
    formPres->addLayout(codPresLay);

    QHBoxLayout* usrLay = new QHBoxLayout();
    usrLay->addWidget(new QLabel("Usuario:"));
    txtUsuario = new QLineEdit();
    usrLay->addWidget(txtUsuario);
    formPres->addLayout(usrLay);

    QHBoxLayout* btnPresLay = new QHBoxLayout();
    QPushButton* btnPres = new QPushButton("Prestar");
    btnPres->setStyleSheet("background-color: #3498db; color: white; padding: 6px;");
    QPushButton* btnDev = new QPushButton("Devolver");
    btnDev->setStyleSheet("background-color: #e67e22; color: white; padding: 6px;");
    btnPresLay->addWidget(btnPres);
    btnPresLay->addWidget(btnDev);
    formPres->addLayout(btnPresLay);

    layPres->addWidget(groupPres);

    // Simular días
    QGroupBox* groupSim = new QGroupBox("Simular Días");
    QHBoxLayout* simLay = new QHBoxLayout(groupSim);
    simLay->addWidget(new QLabel("Código:"));
    txtCodigoSimular = new QLineEdit();
    simLay->addWidget(txtCodigoSimular);
    simLay->addWidget(new QLabel("Días:"));
    spinDias = new QSpinBox();
    spinDias->setRange(1, 100);
    simLay->addWidget(spinDias);
    QPushButton* btnSim = new QPushButton("Simular");
    simLay->addWidget(btnSim);
    layPres->addWidget(groupSim);

    QHBoxLayout* titPresLay = new QHBoxLayout();
    titPresLay->addWidget(new QLabel("Préstamos Activos:"));
    QPushButton* btnActPres = new QPushButton("Recargar");
    titPresLay->addStretch();
    titPresLay->addWidget(btnActPres);
    layPres->addLayout(titPresLay);

    tablaPrestamos = new QTableWidget();
    tablaPrestamos->setColumnCount(5);
    tablaPrestamos->setHorizontalHeaderLabels({"Código", "Material", "Usuario", "Días", "Estado"});
    tablaPrestamos->horizontalHeader()->setStretchLastSection(true);
    tablaPrestamos->setEditTriggers(QAbstractItemView::NoEditTriggers);
    layPres->addWidget(tablaPrestamos);

    connect(btnPres, &QPushButton::clicked, this, &MainWindow::realizarPrestamo);
    connect(btnDev, &QPushButton::clicked, this, &MainWindow::devolverMaterial);
    connect(btnSim, &QPushButton::clicked, this, &MainWindow::simularDias);
    connect(btnActPres, &QPushButton::clicked, this, &MainWindow::actualizarPrestamos);

    tabs->addTab(tabPres, "Préstamos");
}

void MainWindow::cambiarTipo(int index) {
    widgetLibro->setVisible(index == 0);
    widgetRevista->setVisible(index == 1);
    widgetPelicula->setVisible(index == 2);
}

void MainWindow::agregarMaterial() {
    string titulo = txtTitulo->text().toStdString();
    string codigo = txtCodigo->text().toStdString();
    string autor = txtAutor->text().toStdString();

    if (titulo.empty() || codigo.empty() || autor.empty()) {
        QMessageBox::warning(this, "Error", "Complete todos los campos obligatorios");
        return;
    }

    int tipo = comboTipo->currentIndex();

    if (tipo == 0) { // Libro
        string isbn = txtISBN->text().toStdString();
        int paginas = spinPaginas->value();

        if (isbn.empty() || paginas == 0) {
            QMessageBox::warning(this, "Error", "Complete ISBN y número de páginas");
            return;
        }

        biblioteca->agregarMaterial(new Libro(titulo, codigo, autor, paginas, isbn));

    } else if (tipo == 1) { // Revista
        string mes = txtMes->text().toStdString();
        int edicion = spinEdicion->value();

        if (mes.empty() || edicion == 0) {
            QMessageBox::warning(this, "Error", "Complete mes y número de edición");
            return;
        }

        biblioteca->agregarMaterial(new Revista(titulo, codigo, autor, edicion, mes));

    } else { // Película
        string genero = txtGenero->text().toStdString();
        int duracion = spinDuracion->value();

        if (genero.empty() || duracion == 0) {
            QMessageBox::warning(this, "Error", "Complete género y duración");
            return;
        }

        biblioteca->agregarMaterial(new Pelicula(titulo, codigo, autor, duracion, genero));
    }

    QMessageBox::information(this, "Éxito", "Material agregado correctamente");

    // Limpiar formulario
    txtTitulo->clear();
    txtCodigo->clear();
    txtAutor->clear();
    txtISBN->clear();
    txtMes->clear();
    txtGenero->clear();
    spinPaginas->setValue(0);
    spinEdicion->setValue(0);
    spinDuracion->setValue(0);

    actualizarInventario();
}

void MainWindow::actualizarInventario() {
    tablaInventario->setRowCount(0);
    const vector<Material*>& inv = biblioteca->getInventario();

    for (size_t i = 0; i < inv.size(); i++) {
        Material* m = inv[i];
        int row = tablaInventario->rowCount();
        tablaInventario->insertRow(row);

        tablaInventario->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(m->getCodigoIdentificador())));
        tablaInventario->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(m->getTitulo())));
        tablaInventario->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(m->getAutor())));

        QString tipo = "?";
        QString detalles = "";

        if (Libro* libro = dynamic_cast<Libro*>(m)) {
            tipo = "Libro";
            detalles = QString("ISBN: %1 | %2 págs").arg(QString::fromStdString(libro->getISBN())).arg(libro->getNumPaginas());
        } else if (Revista* revista = dynamic_cast<Revista*>(m)) {
            tipo = "Revista";
            detalles = QString("Ed. %1 | %2").arg(revista->getNumEdicion()).arg(QString::fromStdString(revista->getMesPublicacion()));
        } else if (Pelicula* peli = dynamic_cast<Pelicula*>(m)) {
            tipo = "Película";
            detalles = QString("%1 | %2 min").arg(QString::fromStdString(peli->getGenero())).arg(peli->getDuracionMinutos());
        }

        tablaInventario->setItem(row, 3, new QTableWidgetItem(tipo));
        tablaInventario->setItem(row, 4, new QTableWidgetItem(detalles));
        tablaInventario->setItem(row, 5, new QTableWidgetItem(m->estaDisponible() ? "Disponible" : "Prestado"));
    }

    //Para ajustar ancho de columnas
    tablaInventario->resizeColumnsToContents();
}

void MainWindow::buscarMaterial() {
    string codigo = txtBuscar->text().toStdString();
    Material* m = biblioteca->buscarMaterial(codigo);

    if (m) {
        QString info = QString("INFORMACIÓN DEL MATERIAL\n\n");
        info += QString("Código: %1\n").arg(QString::fromStdString(m->getCodigoIdentificador()));
        info += QString("Título: %1\n").arg(QString::fromStdString(m->getTitulo()));
        info += QString("Autor/Director: %1\n").arg(QString::fromStdString(m->getAutor()));

        // Detalles específicos según tipo
        if (Libro* libro = dynamic_cast<Libro*>(m)) {
            info += QString("\nTipo: Libro\n");
            info += QString("ISBN: %1\n").arg(QString::fromStdString(libro->getISBN()));
            info += QString("Páginas: %1\n").arg(libro->getNumPaginas());
            info += QString("Días de préstamo: 15 días\n");
        } else if (Revista* revista = dynamic_cast<Revista*>(m)) {
            info += QString("\nTipo: Revista\n");
            info += QString("Edición: %1\n").arg(revista->getNumEdicion());
            info += QString("Mes: %1\n").arg(QString::fromStdString(revista->getMesPublicacion()));
            info += QString("Préstamo: Solo consulta en sala\n");
        } else if (Pelicula* peli = dynamic_cast<Pelicula*>(m)) {
            info += QString("\nTipo: Película\n");
            info += QString("Género: %1\n").arg(QString::fromStdString(peli->getGenero()));
            info += QString("Duración: %1 minutos\n").arg(peli->getDuracionMinutos());
            info += QString("Días de préstamo: 3 días\n");
        }

        info += QString("\nEstado: %1").arg(m->estaDisponible() ? "Disponible" : "Prestado");

        QMessageBox::information(this, "Material Encontrado", info);
    } else {
        QMessageBox::warning(this, "Error", "Material no encontrado");
    }
}

void MainWindow::realizarPrestamo() {
    string codigo = txtCodigoPrestamo->text().toStdString();
    string usuario = txtUsuario->text().toStdString();

    if (codigo.empty() || usuario.empty()) {
        QMessageBox::warning(this, "Error", "Complete todos los campos");
        return;
    }

    if (biblioteca->procesarPrestamo(codigo, usuario)) {
        QMessageBox::information(this, "Éxito", "Préstamo realizado");
        txtCodigoPrestamo->clear();
        txtUsuario->clear();
        actualizarPrestamos();
        actualizarInventario();
    }
}

void MainWindow::devolverMaterial() {
    string codigo = txtCodigoPrestamo->text().toStdString();

    if (codigo.empty()) {
        QMessageBox::warning(this, "Error", "Ingrese el código");
        return;
    }

    if (biblioteca->devolverMaterial(codigo)) {
        txtCodigoPrestamo->clear();
        actualizarPrestamos();
        actualizarInventario();
    }
}

void MainWindow::actualizarPrestamos() {
    tablaPrestamos->setRowCount(0);
    const vector<Prestamos*>& prest = biblioteca->getPrestamoActivo();

    for (size_t i = 0; i < prest.size(); i++) {
        Prestamos* p = prest[i];
        int row = tablaPrestamos->rowCount();
        tablaPrestamos->insertRow(row);

        tablaPrestamos->setItem(row, 0, new QTableWidgetItem(QString::fromStdString(p->getCodigoIdentificador())));
        tablaPrestamos->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(p->getMaterial()->getTitulo())));
        tablaPrestamos->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(p->getNombreUsuario())));
        tablaPrestamos->setItem(row, 3, new QTableWidgetItem(QString("%1/%2").arg(p->getdiasTranscurridos()).arg(p->getdiasdeprestamo())));

        QString estado;
        int retraso = p->calculardiasderetraso();
        if (retraso > 0) {
            estado = QString("Retraso: %1d - Multa: $%2").arg(retraso).arg(p->calcularmulta());
        } else {
            estado = "OK";
        }

        tablaPrestamos->setItem(row, 4, new QTableWidgetItem(estado));
    }
}

void MainWindow::simularDias() {
    string codigo = txtCodigoSimular->text().toStdString();
    int dias = spinDias->value();

    biblioteca->simularDias(codigo, dias);
    actualizarPrestamos();

    QMessageBox::information(this, "OK", QString("Simulados %1 días").arg(dias));
}

void MainWindow::eliminarMaterial() {
    string codigo = txtBuscar->text().toStdString();

    if (codigo.empty()) {
        QMessageBox::warning(this, "Error", "Ingrese el código del material a eliminar");
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Confirmar",
                                  "¿Está seguro de eliminar este material?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        if (biblioteca->eliminarMaterial(codigo)) {
            QMessageBox::information(this, "Éxito", "Material eliminado");
            txtBuscar->clear();
            actualizarInventario();
        } else {
            QMessageBox::warning(this, "Error", "No se pudo eliminar, Material prestado o no existe");
        }
    }
}

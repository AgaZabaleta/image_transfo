#include "mainwindow.h"
#include "application.h"

MainWindow::MainWindow(QWidget* parent):QMainWindow(parent), application(new Application(this))
{
    setCentralWidget(application);
    resize(500,500);
    setWindowTitle(tr("Edition d'image"));
}


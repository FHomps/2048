#include "mainwindow.h"
#include <QApplication>
#include "grid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MainWindow window;
    window.setFixedSize(640, 480);
    
    Grid g(&window);
    g.initGrid();
    
    window.show();
    return a.exec();
}

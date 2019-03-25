#include "mainwindow.h"
#include <QApplication>
#include "grid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MainWindow window;
    window.setFixedSize(640, 480);
    
    Grid grid(&window);
	
	QObject::connect(&window, SIGNAL(move(Grid::Direction)), &grid, SLOT(move(Grid::Direction)));
	
    grid.initGrid();

    window.show();
    return a.exec();
}

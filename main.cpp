#include "mainwindow.h"
#include <QApplication>
#include "grid.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    
    MainWindow window;
	window.setFixedSize(640, 640);
    Grid grid(&window, Pos(4, 4));
	
	QObject::connect(&window, SIGNAL(move(Grid::Direction)), &grid, SLOT(move(Grid::Direction)));	
	QObject::connect(&window, SIGNAL(restartGrid()), &grid, SLOT(restart()));
	
    grid.initGrid();

    window.show();
    return a.exec();
}

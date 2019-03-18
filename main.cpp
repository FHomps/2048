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
	
	for (int i = 0; i < 10; i++) {
		g.printGrid();
		g.move(Grid::LEFT);
		std::cout << std::endl;
	}
    
    window.show();
    return a.exec();
}

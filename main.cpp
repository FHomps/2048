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

	do {
		g.printGrid();
		std::cout << std::endl;
	} while (g.move(Grid::LEFT));
	
    window.show();
    return a.exec();
}

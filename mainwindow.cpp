#include "mainwindow.h"
#include "tile.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setGeometry(0,0,480,480);
}

MainWindow::~MainWindow()
{
    //
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_Left:
        emit move(Grid::LEFT);
        break;
    case Qt::Key_Right:
        emit move(Grid::RIGHT);
        break;
    case Qt::Key_Up:
        emit move(Grid::UP);
        break;
    case Qt::Key_Down:
        emit move(Grid::DOWN);
        break;
	case Qt::Key_Space:
		emit restartGrid();
		break;
    default:
        break;
    }
}

#include "mainwindow.h"
#include "tile.h"

MainWindow::MainWindow(int width, int height, QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize((width > 100 ? width : 100), (height > 100 ? height : 100));

    grid = new Grid(this);
    const int gridSize((width < 0.8*height ? width : static_cast<int>(0.8*height)));
    grid->setGeometry(0,0,gridSize,gridSize);
    grid->setStyleSheet("QWidget { background-color: #CDC1B4; }");

    QObject::connect(this, SIGNAL(move(Grid::Direction)), grid, SLOT(move(Grid::Direction)));
    QObject::connect(this, SIGNAL(restartGrid()), grid, SLOT(restart()));

    grid->initGrid();
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

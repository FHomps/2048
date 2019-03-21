#include "mainwindow.h"
#include "tile.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    this->setGeometry(0,0,480,480);
    m_tile1 = new Tile(Pos(0,0), 11, this);
    m_tile2 = new Tile(Pos(2,0), 8, this);
    m_tile3 = new Tile(Pos(3,3), 5, this);
    m_tile4 = new Tile(Pos(1,1), 6, this);

    m_tile3->setPosition(Pos(2,2));
    m_tile2->setPosition(Pos(2,1));
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
        emit left();
        break;
    case Qt::Key_Right:
        emit right();
        break;
    case Qt::Key_Up:
        emit up();
        break;
    case Qt::Key_Down:
        emit down();
        break;
    default:
        break;
    }
}

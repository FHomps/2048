#include "mainwindow.h"
#include "tile.h"
#include <QInputDialog>
#include <QMessageBox>
#include "colorwindow.h"

MainWindow::MainWindow(int width, int height, QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize((width > 100 ? width : 100), (height > 100 ? height : 100));

    QMessageBox::information(this, "Shortcuts", "Game Shortcuts:\nMove tiles with arrows\nReset game with space\nOpen settings dialog with S\nQuit with Q");

    m_grid = new Grid(this, Pos(4,4));

    QObject::connect(this, SIGNAL(move(Grid::Direction)), m_grid, SLOT(move(Grid::Direction)));
    QObject::connect(this, SIGNAL(restartGrid()), m_grid, SLOT(restart()));
    QObject::connect(this, SIGNAL(settings()), this, SLOT(openSettings()));
    QObject::connect(this, SIGNAL(quit()), qApp, SLOT(quit()));

    m_grid->initGrid();
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
    case Qt::Key_S:
        emit settings();
        break;
    case Qt::Key_Q:
        emit quit();
        break;
    default:
        break;
    }
}

void MainWindow::openSettings()
{
    ColorWindow* colorWindow = new ColorWindow(this);
    QObject::connect(colorWindow, SIGNAL(newGrid(int, int)), this, SLOT(newGrid(int, int)));
    colorWindow->exec();
}

void MainWindow::newGrid(int rowNumber, int colNumber)
{
    delete m_grid;
    m_grid = new Grid(this, Pos(rowNumber, colNumber));

    QObject::connect(this, SIGNAL(move(Grid::Direction)), m_grid, SLOT(move(Grid::Direction)));
    QObject::connect(this, SIGNAL(restartGrid()), m_grid, SLOT(restart()));

    m_grid->initGrid();
}

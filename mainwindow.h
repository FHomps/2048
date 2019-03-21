#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include "tile.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

signals:
    void left();
    void right();
    void up();
    void down();

    //test
    void move(Pos pos);
    
private:
    Tile *m_tile1;
    Tile *m_tile2;
    Tile *m_tile3;
    Tile *m_tile4;
};

#endif // MAINWINDOW_H

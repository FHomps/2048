#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include "grid.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(int width, int height, QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

signals:
    void move(Grid::Direction);
    void restartGrid();

private:
    Grid* grid;
    QLabel score;
};

#endif // MAINWINDOW_H

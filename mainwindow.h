#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QPushButton>
#include "grid.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = nullptr);
    explicit MainWindow(int width, int height, QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent *event);

public slots:
    void openSettings();
    void newGrid(int rowNumber, int colNumber);

signals:
    void move(Grid::Direction);
    void restartGrid();
    void settings();
    void quit();

private:
    Grid* m_grid;
};

#endif // MAINWINDOW_H

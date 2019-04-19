#ifndef COLORWINDOW_H
#define COLORWINDOW_H

#include <QMainWindow>
#include <QVector>
#include <QColor>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QSpinBox>

class ColorWindow : public QDialog
{
    Q_OBJECT

public:
    ColorWindow(QWidget *parent = nullptr);
    ~ColorWindow();

signals:
    void newGrid(int rowNumber, int colNumber);
    void closeDialog();

public slots:
    void makeLinearInterpolation();
    void makeQuadraticInterpolation();
    void makeQuadraticBezierCurve();
    void apply();

private:
    QVector<QColor> m_colors;
    QVector<QLabel*> m_labels;
    QPushButton* m_linear;
    QPushButton* m_quadratic;
    QPushButton* m_bezier;
    QPushButton* m_apply;
    QPushButton* m_cancel;
    QSpinBox* m_rowNumber;
    QSpinBox* m_colNumber;
    QLabel* m_rowLabel;
    QLabel* m_colLabel;

    void linearInterpolation(QColor begin, QColor end);
    void quadraticInterpolation(QColor begin, QColor end, QColor milestone);
    void quadraticBezierCurve(QColor begin, QColor end, QColor milestone);
    void updateLabels();
};

#endif // COLORWINDOW_H

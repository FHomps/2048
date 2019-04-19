#include "colorwindow.h"
#include <QColorDialog>
#include <iostream>
#include <math.h>
#include "tile.h"

ColorWindow::ColorWindow(QWidget *parent): QDialog(parent)
{
    this->setFixedSize(480,480);
    m_colors = {
        QColor("#EEE4DA"),// 2
        QColor("#EFE0C9"),// 4
        QColor("#F2B179"),// 8
        QColor("#F69463"),// 16
        QColor("#F57C5F"),// 32
        QColor("#FA5D3A"),// 64
        QColor("#F1D071"),// 128
        QColor("#F2CD62"),// 256
        QColor("#ECC751"),// 512
        QColor("#EDC53F"),// 1024
        QColor("#EEC22E")// 2048
    };
    for (int i(0); i < 11; i++)
    {
        m_labels.append(new QLabel(this));
        m_labels[i]->setText(QString::number(i+1));
        if (m_colors[i].red() + m_colors[i].green() + m_colors[i].blue() < 580)
            m_labels[i]->setStyleSheet(QString::fromLatin1("QLabel { color : white; background-color : %1; border-radius: 16px; }").arg(m_colors[i].name()));
        else
            m_labels[i]->setStyleSheet(QString::fromLatin1("QLabel { color : black; background-color : %1; border-radius: 16px; }").arg(m_colors[i].name()));
        m_labels[i]->setGeometry(0, i*(this->width() / 11), 200, static_cast<int>(0.9 * static_cast<double>(this->width()) / 11));
        m_labels[i]->setFont(QFont("DejaVu", static_cast<int>(std::min(0.2*m_labels[i]->height(), 0.2*m_labels[i]->width()))));
        m_labels[i]->setAlignment(Qt::AlignCenter);
    }

    m_linear = new QPushButton(this);
    m_linear->setText("Linear Interpolation");
    m_linear->setGeometry(220,20,240,60);
    m_quadratic = new QPushButton(this);
    m_quadratic->setText("Quadratic Interpolation");
    m_quadratic->setGeometry(220,100,240,60);
    m_bezier = new QPushButton(this);
    m_bezier->setText("Quadratic Bezier Curve");
    m_bezier->setGeometry(220,180,240,60);
    m_apply = new QPushButton(this);
    m_apply->setText("Apply");
    m_apply->setGeometry(240,440,100,40);
    m_cancel = new QPushButton(this);
    m_cancel->setText("Cancel");
    m_cancel->setGeometry(360,440,100,40);
    m_rowNumber = new QSpinBox(this);
    m_rowNumber->setRange(0,100);
    m_rowNumber->setValue(4);
    m_rowNumber->setGeometry(340,320,100,40);
    m_rowLabel = new QLabel(this);
    m_rowLabel->setText("Number of\nRows: ");
    m_rowLabel->setGeometry(240,320,100,40);
    m_colNumber = new QSpinBox(this);
    m_colNumber->setRange(0,100);
    m_colNumber->setValue(4);
    m_colNumber->setGeometry(340,380,100,40);
    m_colLabel = new QLabel(this);
    m_colLabel->setText("Number of\nColumns: ");
    m_colLabel->setGeometry(240,380,100,40);

    QObject::connect(m_linear, SIGNAL(clicked()), this, SLOT(makeLinearInterpolation()));
    QObject::connect(m_quadratic, SIGNAL(clicked()), this, SLOT(makeQuadraticInterpolation()));
    QObject::connect(m_bezier, SIGNAL(clicked()), this, SLOT(makeQuadraticInterpolation()));
    QObject::connect(this, SIGNAL(closeDialog()), this, SLOT(accept()));
    QObject::connect(m_cancel, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(m_apply, SIGNAL(clicked()), this, SLOT(apply()));
}

ColorWindow::~ColorWindow()
{

}

void ColorWindow::linearInterpolation(QColor begin, QColor end)
{
    for (int i(0); i < m_colors.size(); i++)
    {
        const double t = i*(1/static_cast<double>(m_colors.size()-1));
        m_colors[i].setRed(static_cast<int>((1-t)*begin.red() + t*end.red()));
        m_colors[i].setGreen(static_cast<int>((1-t)*begin.green() + t*end.green()));
        m_colors[i].setBlue(static_cast<int>((1-t)*begin.blue() + t*end.blue()));
    }
}

void ColorWindow::quadraticInterpolation(QColor begin, QColor end, QColor milestone)
{
    const int uRed = end.red() - begin.red();
    const int uGreen = end.green() - begin.green();
    const int uBlue = end.blue() - begin.blue();

    const double milestoneScalarU = (milestone.red()*uRed + milestone.green()*uGreen + milestone.blue()*uBlue) / std::pow(std::sqrt(std::pow(uRed, 2) + std::pow(uGreen, 2) + std::pow(uBlue, 2)), 2);

    const double s = 1/(milestoneScalarU - std::pow(milestoneScalarU, 2));

    const int vRed = milestone.red() - begin.red() - static_cast<int>(milestoneScalarU*uRed);
    const int vGreen = milestone.green() - begin.green() - static_cast<int>(milestoneScalarU*uGreen);
    const int vBlue = milestone.blue() - begin.blue() - static_cast<int>(milestoneScalarU*uBlue);

    for (int i(0); i < m_colors.size(); i++)
    {
        const double t = i*(1/static_cast<double>(m_colors.size()-1));

        const int interpolatedRed = static_cast<int>(begin.red() + t*uRed + s*(t - std::pow(t,2))*vRed);
        const int interpolatedGreen = static_cast<int>(begin.green() + t*uGreen + s*(t - std::pow(t,2))*vGreen);
        const int interpolatedBlue = static_cast<int>(begin.blue() + t*uBlue + s*(t - std::pow(t,2))*vBlue);

        const int highBoundedRed = (interpolatedRed < 255 ? interpolatedRed : 255);
        const int highBoundedGreen = (interpolatedGreen < 255 ? interpolatedGreen : 255);
        const int highBoundedBlue = (interpolatedBlue < 255 ? interpolatedBlue : 255);

        const int newRed = (highBoundedRed > 0 ? highBoundedRed : 0);
        const int newGreen = (highBoundedGreen > 0 ? highBoundedGreen : 0);
        const int newBlue = (highBoundedBlue > 0 ? highBoundedBlue : 0);

        m_colors[i].setRed(newRed);
        m_colors[i].setGreen(newGreen);
        m_colors[i].setBlue(newBlue);
    }
}

void ColorWindow::quadraticBezierCurve(QColor begin, QColor end, QColor milestone)
{
    for (int i(0); i < m_colors.size(); i++)
    {
        const double t = i*(1/static_cast<double>(m_colors.size()-1));
        m_colors[i].setRed(static_cast<int>(std::pow(1-t, 2)*begin.red() + 2*(1-t)*t*milestone.red() + std::pow(t, 2)*end.red()));
        m_colors[i].setGreen(static_cast<int>(std::pow(1-t, 2)*begin.green() + 2*(1-t)*t*milestone.green() + std::pow(t, 2)*end.green()));
        m_colors[i].setBlue(static_cast<int>(std::pow(1-t, 2)*begin.blue() + 2*(1-t)*t*milestone.blue() + std::pow(t, 2)*end.blue()));
    }
}

void ColorWindow::updateLabels()
{
    for (int i(0); i < m_labels.size(); i++)
    {
        if (m_colors[i].red() + m_colors[i].green() + m_colors[i].blue() < 580)
            m_labels[i]->setStyleSheet(QString::fromLatin1("QLabel { color : white; background-color : %1; border-radius: 16px; }").arg(m_colors[i].name()));
        else
            m_labels[i]->setStyleSheet(QString::fromLatin1("QLabel { color : black; background-color : %1; border-radius: 16px; }").arg(m_colors[i].name()));
        m_labels[i]->show();
    }
}

void ColorWindow::makeLinearInterpolation()
{
    QColor begin = QColorDialog::getColor(Qt::white, this, "Couleur de départ");
    QColor end = QColorDialog::getColor(Qt::white, this, "Couleur d'arrivée");

    linearInterpolation(begin, end);
    updateLabels();
}

void ColorWindow::makeQuadraticInterpolation()
{
    QColor begin = QColorDialog::getColor(Qt::white, this, "Couleur de départ");
    QColor milestone = QColorDialog::getColor(Qt::white, this, "Point de passage");
    QColor end = QColorDialog::getColor(Qt::white, this, "Couleur d'arrivée");

    quadraticInterpolation(begin, end, milestone);
    updateLabels();
}

void ColorWindow::makeQuadraticBezierCurve()
{
    QColor begin = QColorDialog::getColor(Qt::white, this, "Couleur de départ");
    QColor milestone = QColorDialog::getColor(Qt::white, this, "Point de passage");
    QColor end = QColorDialog::getColor(Qt::white, this, "Couleur d'arrivée");

    quadraticBezierCurve(begin, end, milestone);
    updateLabels();
}

void ColorWindow::apply()
{
    for (int i(0); i < Tile::styles.size(); i++)
    {
        if (m_colors[i].red() + m_colors[i].green() + m_colors[i].blue() < 580)
            Tile::styles[i] = QString::fromLatin1("QLabel { color : white; background-color : %1; border-radius: 16px; }").arg(m_colors[i].name());
        else
            Tile::styles[i] = QString::fromLatin1("QLabel { color : black; background-color : %1; border-radius: 16px; }").arg(m_colors[i].name());
    }
    emit newGrid(m_rowNumber->value(), m_colNumber->value());
    emit closeDialog();
}

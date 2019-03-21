#ifndef TILE_H
#define TILE_H

#include <QLabel>
#include <math.h>
#include <QPropertyAnimation>

struct Pos {
    Pos(): i(0), j(0) {}
    Pos(int i, int j): i(i), j(j) {}
    int i;
    int j;
};

class Tile: public QObject
{
    Q_OBJECT
public:
    Tile();
    Tile(Pos pos, unsigned int power, QWidget *parent);

    void setPower(unsigned int power);
    unsigned int power() const;

    void setPosition(Pos pos);
    Pos position() const;

    void fadeIn();
    void fadeOut();

    bool m_fused;
private:
    static const QString styles[];
    static const int margin;

    QWidget* m_parent;
    unsigned int m_power;
    QLabel* m_label;
    Pos m_pos;
    int m_width;
    int m_height;
};

#endif // TILE_H

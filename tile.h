#ifndef TILE_H
#define TILE_H

#include <QLabel>
#include <math.h>
#include <QPropertyAnimation>
#include <QTime>
#include <QVector>

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
    Tile(Pos pos, unsigned int power, QWidget *parent, Pos const& gridSize);
	virtual ~Tile() { delete m_label; }

    void setPowerOf2(unsigned int power);
    unsigned int getPowerOf2() const;

    void setPosition(Pos pos);
    Pos getPosition() const;

	void makeLost();
	
    bool recentlyFused = false;
	
	static QPropertyAnimation const* getLastAnimation();
    static QVector<QString> styles;

public slots:
	void showTile();
	
private:
    static const int margin;

    QWidget* m_parent;
    unsigned int m_power;
    QLabel* m_label;
    Pos m_pos;
    int m_width;
    int m_height;
	
	static QPropertyAnimation* m_lastAnimation;
	static QTime m_lastAnimationTime;
};

#endif // TILE_H

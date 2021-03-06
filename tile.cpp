#include "tile.h"
#include <iostream>

QPropertyAnimation* Tile::m_lastAnimation = nullptr;
QTime Tile::m_lastAnimationTime = QTime::currentTime();

QVector<QString> Tile::styles = {
    QString("QLabel { color : black; background-color : #EEE4DA; border-radius: 16px; }"),// 2
    QString("QLabel { color : black; background-color : #EFE0C9; border-radius: 16px; }"),// 4
    QString("QLabel { color : white; background-color : #F2B179; border-radius: 16px; }"),// 8
    QString("QLabel { color : white; background-color : #F69463; border-radius: 16px; }"),// 16
    QString("QLabel { color : white; background-color : #F57C5F; border-radius: 16px; }"),// 32
    QString("QLabel { color : white; background-color : #FA5D3A; border-radius: 16px; }"),// 64
    QString("QLabel { color : white; background-color : #F1D071; border-radius: 16px; }"),// 128
    QString("QLabel { color : white; background-color : #F2CD62; border-radius: 16px; }"),// 256
    QString("QLabel { color : white; background-color : #ECC751; border-radius: 16px; }"),// 512
    QString("QLabel { color : white; background-color : #EDC53F; border-radius: 16px; }"),// 1024
    QString("QLabel { color : white; background-color : #EEC22E; border-radius: 16px; }")// 2048
};

const int Tile::margin = 5;

Tile::Tile(Pos pos, unsigned int power, QWidget* parent, Pos const& gridSize)
{
    m_parent = parent;
    recentlyFused = false;
	
    m_width = static_cast<int>((m_parent->geometry().width() - (gridSize.j+1)*margin) / gridSize.j);
    m_height = static_cast<int>((0.9*m_parent->geometry().height() - (gridSize.i+1)*margin) / gridSize.i);

    if (power < 1 || power > 11)
        throw std::domain_error("invalid power: unsigned int power must be in [1,11]");
    if (pos.i < 0 || pos.j < 0)
        throw std::domain_error("invalid position: coordinates must be positive");
    m_power = power;
    m_pos = pos;

    m_label = new QLabel(QString().setNum(std::pow(2,m_power)), parent);

    const int offset = static_cast<int>(0.1*m_parent->geometry().height());
    m_label->setGeometry(pos.j*(m_width + margin) + margin, pos.i*(m_height + margin) + margin + offset, m_width, m_height);
    m_label->setStyleSheet(styles[m_power-1]);
    m_label->setFont(QFont("DejaVu", static_cast<int>(std::min(0.2*m_height, 0.2*m_width))));
    m_label->setAlignment(Qt::AlignCenter);
}

void Tile::setPowerOf2(unsigned int power)
{
    if (power < 1)
        throw std::domain_error("invalid power: unsigned int power must be in >= 1");
    else if (power > 10)
    {
        m_power = power;
        m_label->setText("You've\nwon");
        m_label->setStyleSheet(styles[10]);
    }
    else
    {
        m_power = power;
        m_label->setText(QString().setNum(std::pow(2,m_power)));
        m_label->setStyleSheet(styles[m_power-1]);
    }
}

unsigned int Tile::getPowerOf2() const
{
    return m_power;
}

void Tile::setPosition(Pos pos)
{
    if (pos.i < 0 || pos.j < 0)
        throw std::domain_error("invalid position: coordinates must be positive");

    const int initialX = m_pos.j*(m_width + margin) + margin;
    const int finalX = pos.j*(m_width + margin) + margin;

    const int offset = static_cast<int>(0.1*m_parent->geometry().height());

    const int initialY = m_pos.i*(m_height + margin) + margin + offset;
    const int finalY = pos.i*(m_height + margin) + margin + offset;

	m_pos = pos;
	
    QPropertyAnimation *animation = new QPropertyAnimation(m_label, "geometry");
    animation->setDuration(300);
    animation->setStartValue(QRect(initialX, initialY, m_width, m_height));
    animation->setEndValue(QRect(finalX, finalY, m_width, m_height));

    animation->start();
	
	QTime tf = QTime::currentTime().addMSecs(300);
	if (m_lastAnimationTime < tf) {
		m_lastAnimationTime = tf;
		m_lastAnimation = animation;
	}
}

Pos Tile::getPosition() const
{
    return m_pos;
}

void Tile::makeLost() {
    m_label->setStyleSheet(QString("QLabel { color : white; background-color : #CDC1B4; border-radius: 16px; }"));
    m_label->setText("Game\nOver");
}

QPropertyAnimation const* Tile::getLastAnimation() {
	return m_lastAnimation;
}

void Tile::showTile() {
	if (!m_label->isVisible())
		m_label->show();
}

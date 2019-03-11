#ifndef TILE_H
#define TILE_H
#include <QLabel>

#include <iostream>
#include <cmath>

struct Pos {
    Pos() {}
    Pos(int x, int y) : x(x), y(y) {}
    int x = 0;
    int y = 0;
};

class Tile
{
public:
    
    Tile() {}
    Tile(Pos pos, int power) : m_pos(pos), m_power(power) {}
    
    void setPosition(Pos pos) { m_pos = pos; }
    Pos getPosition() const { return m_pos; }
    
    void setPowerOf2(int power) { m_power = power; }
    int getPowerOf2() const { return m_power; }
    
    void printTileInfo() const { std::cout << m_pos.x << ' ' << m_pos.y << ' ' << pow(2, m_power) << std::endl; }
    
private:
    Pos m_pos = Pos(0, 0);
    int m_power = 0;

};

#endif // TILE_H

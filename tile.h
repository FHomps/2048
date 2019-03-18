#ifndef TILE_H
#define TILE_H
#include <QLabel>

#include <iostream>
#include <cmath>

struct Pos {
    Pos() {}
    Pos(int i, int j) : i(i), j(j) {}
    int i = 0;
    int j = 0;
};

class Tile
{
public:
    
    Tile() {}
    Tile(Pos pos, unsigned int power) : m_pos(pos), m_power(power) {}
	~Tile() {}
    
    void setPosition(Pos pos) { m_pos = pos; }
    Pos getPosition() const { return m_pos; }
    
    void setPowerOf2(unsigned int power) { m_power = power; }
    unsigned int getPowerOf2() const { return m_power; }
    
    void printTileInfo() const { std::cout << m_pos.i << ' ' << m_pos.j << ' ' << pow(2, m_power) << std::endl; }
    
	bool recentlyFused = false;
	
private:
    Pos m_pos = Pos(0, 0);
    unsigned int m_power = 0;

};

#endif // TILE_H

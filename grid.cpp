#include "grid.h"
#include <random>

#include <iostream>

Grid::Grid(QWidget* parent) : QWidget (parent) {
    
}

void Grid::initGrid() {
    m_tiles.clear();
    
    srand(static_cast<uint>(time(nullptr)));
    m_tiles.push_back(Tile(Pos(rand()%4, rand()%4), rand()%3+1));
    
    m_tiles[0].printTileInfo();
}

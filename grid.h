#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include "tile.h"
#include <vector>

class Grid : public QWidget
{
public:
    Grid(QWidget* parent = nullptr);
    
    void initGrid();
    
private:
    std::vector<Tile> m_tiles;
};

#endif // GRID_H

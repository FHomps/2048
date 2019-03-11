#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include "tile.h"

class Grid : public QWidget
{
public:
    Grid();
    
private:
    Tile* m_tiles[4][4];
};

#endif // GRID_H

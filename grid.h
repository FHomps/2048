#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include "tile.h"
#include <vector>
#include <iostream>

class Grid : public QWidget
{
	Q_OBJECT
	
public:
	enum Direction { UP, DOWN, RIGHT, LEFT };
	
    Grid(QWidget* parent);
	virtual ~Grid();
	
	void addTile(Pos pos, unsigned int pow);
	void removeTile(Pos pos);
	void moveTile(Pos initialPos, Pos targetPos);
	
    void initGrid();
	void clearGrid();
		
	void printGrid() const {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				std::cout << (m_tiles[i][j] == nullptr ? "*" : std::to_string(m_tiles[i][j]->getPowerOf2())) << ' ';
			}
			std::cout << std::endl;
		}
	}
	
	
public slots:
	void move(Grid::Direction dir);
	void restart();
	
private:	
	QWidget* m_parent;
	
	Tile* m_tiles[4][4];
};

#endif // GRID_H

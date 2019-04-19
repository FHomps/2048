#ifndef GRID_H
#define GRID_H

#include <QWidget>
#include "tile.h"
#include <vector>
#include <iostream>
#include <QPushButton>

class Grid : public QWidget
{
	Q_OBJECT
	
public:
	enum Direction { UP, DOWN, RIGHT, LEFT };
	
    Grid(QWidget* parent, Pos gridSize = Pos(4, 4));
	virtual ~Grid();
	
	void addTile(Pos pos, unsigned int pow);
	void removeTile(Pos pos);
	void moveTile(Pos initialPos, Pos targetPos);
	
    void initGrid();
	void clearGrid();
	
	uint getScore() const { return m_score; }
		
	void printGrid() const {
		for (int i = 0; i < gridSize.i; i++) {
			for (int j = 0; j < gridSize.j; j++) {
				std::cout << (m_tiles[i][j] == nullptr ? "*" : std::to_string(m_tiles[i][j]->getPowerOf2())) << ' ';
			}
			std::cout << std::endl;
		}
	}
	
	const Pos gridSize;
	
public slots:
	void move(Grid::Direction dir);
	void restart();
	
private:
	QWidget* m_parent;
	
	Tile*** m_tiles;
	
	uint m_score = 0;
    QLabel* m_scoreLabel;
	
	bool hasLost = false;
	bool checkForLoss() const;
};

#endif // GRID_H

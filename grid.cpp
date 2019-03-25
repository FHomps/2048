#include "grid.h"
#include <random>

#include <iostream>

Grid::Grid(QWidget* parent) : QWidget (parent) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m_tiles[i][j] = nullptr;
		}
	}
}

Grid::~Grid() {
	clearGrid();
}

inline bool within(int i, int min, int max) { return i >= min && i < max; }

void Grid::addTile(Pos pos, unsigned int pow) {
	if (m_tiles[pos.i][pos.j] == nullptr) {
		m_tiles[pos.i][pos.j] = new Tile(pos, pow);
	}
	else {
		m_tiles[pos.i][pos.j]->setPowerOf2(pow);
	}
}

void Grid::removeTile(Pos pos) {
	if (m_tiles[pos.i][pos.j] != nullptr) {
		delete m_tiles[pos.i][pos.j];
		m_tiles[pos.i][pos.j] = nullptr;
	}
}

void Grid::moveTile(Pos initialPos, Pos targetPos) {
	if (m_tiles[initialPos.i][initialPos.j] == nullptr || m_tiles[targetPos.i][targetPos.j] != nullptr)
		return;
	m_tiles[initialPos.i][initialPos.j]->setPosition(targetPos);
	m_tiles[targetPos.i][targetPos.j] = m_tiles[initialPos.i][initialPos.j];
	m_tiles[initialPos.i][initialPos.j] = nullptr;
}

void Grid::initGrid() {
    clearGrid();
    
    srand(static_cast<uint>(time(nullptr)));
	addTile(Pos(rand()%4, rand()%4), rand()%2+1);
}

void Grid::clearGrid() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			removeTile(Pos(i, j));
		}
	}
}

bool Grid::move(Direction dir) {
	bool successfulMove = false;
	
	if (dir == LEFT) {
		for (int j = 1; j < 4; j++) {
			for (int i = 0; i < 4; i++) {
				if (m_tiles[i][j] != nullptr) {
					unsigned int pow = m_tiles[i][j]->getPowerOf2();
					int j2 = j-1;
					while (j2 > 0 && m_tiles[i][j2] == nullptr) {
						j2--;
					}
					
					//j2 is either 0 or the first tile encountered
					
					if (m_tiles[i][j2] == nullptr) {
						moveTile(Pos(i, j), Pos(i, j2));
						successfulMove = true;
					}
					else if (m_tiles[i][j2]->getPowerOf2() != pow || m_tiles[i][j2]->recentlyFused) {
						if (j2+1 != j) {
							moveTile(Pos(i, j), Pos(i, j2+1));		
							successfulMove = true;
						}
					}
					else {
						removeTile(Pos(i, j2));
						moveTile(Pos(i, j), Pos(i, j2));
						m_tiles[i][j2]->setPowerOf2(pow+1);
						m_tiles[i][j2]->recentlyFused = true;
						successfulMove = true;
					}
				}
			}
		}
	}
	else if (dir == RIGHT) {
		for (int j = 2; j >= 0; j--) {
			for (int i = 0; i < 4; i++) {
				if (m_tiles[i][j] != nullptr) {
					unsigned int pow = m_tiles[i][j]->getPowerOf2();
					int j2 = j+1;
					while (j2 < 3 && m_tiles[i][j2] == nullptr)
						j2++;
					
					if (m_tiles[i][j2] == nullptr) {
						moveTile(Pos(i, j), Pos(i, j2));
						successfulMove = true;
					}
					else if (m_tiles[i][j2]->getPowerOf2() != pow || m_tiles[i][j2]->recentlyFused) {
						if (j2-1 != j) {
							moveTile(Pos(i, j), Pos(i, j2-1));
							successfulMove = true;
						}
					}
					else {
						removeTile(Pos(i, j2));
						moveTile(Pos(i, j), Pos(i, j2));
						m_tiles[i][j2]->setPowerOf2(pow+1);
						m_tiles[i][j2]->recentlyFused = true;
						successfulMove = true;
					}
				}
			}
		}
	}
	else if (dir == UP) {
		for (int i = 1; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (m_tiles[i][j] != nullptr) {
					unsigned int pow = m_tiles[i][j]->getPowerOf2();
					int i2 = i-1;
					while (i2 > 0 && m_tiles[i2][j] == nullptr)
						i2--;
					
					if (m_tiles[i2][j] == nullptr) {
						moveTile(Pos(i, j), Pos(i2, j));
						successfulMove = true;
					}
					else if (m_tiles[i2][j]->getPowerOf2() != pow || m_tiles[i2][j]->recentlyFused) {
						if (i2+1 != i) {
							moveTile(Pos(i, j), Pos(i2+1, j));
							successfulMove = true;
						}
					}
					else {
						removeTile(Pos(i2, j));
						moveTile(Pos(i, j), Pos(i2, j));
						m_tiles[i2][j]->setPowerOf2(pow+1);
						m_tiles[i2][j]->recentlyFused = true;
						successfulMove = true;
					}
				}
			}
		}
	}
	else if (dir == DOWN) {
		for (int i = 2; i >= 0; i--) {
			for (int j = 0; j < 4; j++) {
				if (m_tiles[i][j] != nullptr) {
					unsigned int pow = m_tiles[i][j]->getPowerOf2();
					int i2 = i+1;
					while (i2 < 3 && m_tiles[i2][j] == nullptr)
						i2++;
					
					if (m_tiles[i2][j] == nullptr) {
						moveTile(Pos(i, j), Pos(i2, j));
						successfulMove = true;
					}
					else if (m_tiles[i2][j]->getPowerOf2() != pow || m_tiles[i2][j]->recentlyFused) {
						if (i2-1 != i) {
							moveTile(Pos(i, j), Pos(i2-1, j));
							successfulMove = true;
						}
					}
					else {
						removeTile(Pos(i2, j));
						moveTile(Pos(i, j), Pos(i2, j));
						m_tiles[i2][j]->setPowerOf2(pow+1);
						m_tiles[i2][j]->recentlyFused = true;
						successfulMove = true;
					}
				}
			}
		}
	}
	
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (m_tiles[i][j] != nullptr)
				m_tiles[i][j]->recentlyFused = false;
		}
	}
	
	if (successfulMove) {
		Pos p(rand()%4, rand()%4);
		while (m_tiles[p.i][p.j] != nullptr) {
			p = Pos(rand()%4, rand()%4);
		}
		addTile(p, rand()%2+1);	
	}
	return successfulMove;
}

#include "grid.h"
#include <random>

#include <QApplication>

#include <iostream>

#include <QString>

Grid::Grid(QWidget* parent, Pos arg_gridSize) :  gridSize(arg_gridSize.i > 1 && arg_gridSize.j > 1 ? arg_gridSize : Pos(4, 4)), m_parent(parent) {
    m_scoreLabel = new QLabel(m_parent);
    m_scoreLabel->setText(QString("     Score: ") + QString::number(0));
    m_scoreLabel->setGeometry(0, 0, m_parent->geometry().width(), static_cast<int>(0.1*m_parent->geometry().height()));
    m_scoreLabel->setStyleSheet("QLabel { color : black; font-size: 16px; background-color : #CDC1B4; border-radius: 16px; }");
    m_scoreLabel->show();

    m_tiles = new Tile**[gridSize.i];
	for (int i = 0; i < gridSize.i; i++) {
		m_tiles[i] = new Tile*[gridSize.j];
		for (int j = 0; j < gridSize.j; j++) {
			m_tiles[i][j] = nullptr;
		}
	}
}

Grid::~Grid() {
	clearGrid();
	for (int i = 0; i < gridSize.i; i++) {
		delete[] m_tiles[i];
	}
	delete[] m_tiles;
    delete m_scoreLabel;
}

inline bool within(int i, int min, int max) { return i >= min && i < max; }

void Grid::addTile(Pos pos, unsigned int pow) {
	if (m_tiles[pos.i][pos.j] == nullptr)
  {
		m_tiles[pos.i][pos.j] = new Tile(pos, pow, m_parent, gridSize);
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
	Pos p(rand()%gridSize.i, rand()%gridSize.j);
	addTile(p, rand()%2+1);
    m_tiles[p.i][p.j]->showTile();

    m_score = 0;
    m_scoreLabel->setText(QString("     Score: ") + QString::number(0));
}

void Grid::clearGrid() {
	for (int i = 0; i < gridSize.i; i++) {
		for (int j = 0; j < gridSize.j; j++) {
			removeTile(Pos(i, j));
		}
	}
}

void Grid::move(Grid::Direction dir) {
	bool successfulMove = false;
	
	//Met à jour l'affichage des objets en début du tour
	//Utile en cas de spam de touches
	for (int i = 0; i < gridSize.i; i++) {
		for (int j = 0; j < gridSize.j; j++) {
			if (m_tiles[i][j] != nullptr) {
				m_tiles[i][j]->showTile();
			}
		}
	}
	
	if (dir == LEFT) {
		for (int j = 1; j < gridSize.j; j++) {
			for (int i = 0; i < gridSize.i; i++) {
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
						m_score += std::pow(2, pow+1);
                        m_scoreLabel->setText(QString("     Score: ") + QString::number(m_score));
						m_tiles[i][j2]->recentlyFused = true;
						successfulMove = true;
					}
				}
			}
		}
	}
	else if (dir == RIGHT) {
		for (int j = gridSize.j-2; j >= 0; j--) {
			for (int i = 0; i < gridSize.i; i++) {
				if (m_tiles[i][j] != nullptr) {
					unsigned int pow = m_tiles[i][j]->getPowerOf2();
					int j2 = j+1;
					while (j2 < gridSize.j-1 && m_tiles[i][j2] == nullptr)
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
						m_score += std::pow(2, pow+1);
                        m_scoreLabel->setText(QString("     Score: ") + QString::number(m_score));
						m_tiles[i][j2]->recentlyFused = true;
						successfulMove = true;
					}
				}
			}
		}
	}
	else if (dir == UP) {
		for (int i = 1; i < gridSize.i; i++) {
			for (int j = 0; j < gridSize.j; j++) {
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
						m_score += std::pow(2, pow+1);
                        m_scoreLabel->setText(QString("     Score: ") + QString::number(m_score));
						m_tiles[i2][j]->recentlyFused = true;
						successfulMove = true;
					}
				}
			}
		}
	}
	else if (dir == DOWN) {
		for (int i = gridSize.i-2; i >= 0; i--) {
			for (int j = 0; j < gridSize.j; j++) {
				if (m_tiles[i][j] != nullptr) {
					unsigned int pow = m_tiles[i][j]->getPowerOf2();
					int i2 = i+1;
					while (i2 < gridSize.i-1 && m_tiles[i2][j] == nullptr)
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
						m_score += std::pow(2, pow+1);
                        m_scoreLabel->setText(QString("     Score: ") + QString::number(m_score));
						m_tiles[i2][j]->recentlyFused = true;
						successfulMove = true;
					}
				}
			}
		}
	}
	
	for (int i = 0; i < gridSize.i; i++) {
		for (int j = 0; j < gridSize.j; j++) {
			if (m_tiles[i][j] != nullptr)
				m_tiles[i][j]->recentlyFused = false;
		}
	}
	
	if (successfulMove) {
		Pos p(rand()%gridSize.i, rand()%gridSize.j);
		while (m_tiles[p.i][p.j] != nullptr) {
			p = Pos(rand()%gridSize.i, rand()%gridSize.j);
		}
		addTile(p, rand()%2+1);
		QPropertyAnimation const* anim = Tile::getLastAnimation();
		for (int i = 0; i < gridSize.i; i++) {
			for (int j = 0; j < gridSize.j; j++) {
				if (m_tiles[i][j] != nullptr)
					QObject::connect(anim, SIGNAL(finished()), m_tiles[i][j], SLOT(showTile())); //Met à jour l'affichage des objets à la fin des animations du tour	
			}
		}
	}
}

void Grid::restart() {
	clearGrid();
	initGrid();
}

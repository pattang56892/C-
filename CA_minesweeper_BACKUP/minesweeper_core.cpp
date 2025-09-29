// Game logic implementation

#include "minesweeper_core.h"
#include <iostream>
#include <random>
#include <algorithm>

Minesweeper::Minesweeper(int r, int c, int mines)
	: rows(r), cols(c), totalMines(mines), revealedCells(0),
	flaggedMines(0), gameOver(false), gameWon(false),
	gameStarted(false) {
	initializeGrid();
	placeMines();
	calculateAdjacentMines();
}

// Getters
int Minesweeper::getRows() const { return rows; }
int Minesweeper::getCols() const { return cols; }
int Minesweeper::getTotalMines() const { return totalMines; }
int Minesweeper::getRevealedCells() const { return revealedCells; }
int Minesweeper::getFlaggedMines() const { return flaggedMines; }
int Minesweeper::getRemainingMines() const { return totalMines - flaggedMines; }
bool Minesweeper::isGameOver() const { return gameOver; }
bool Minesweeper::isGameWon() const { return gameWon; }

int Minesweeper::getElapsedTime() const {
	if (!gameStarted || gameOver) return 0;
	return static_cast<int>(difftime(time(nullptr), startTime));
}

// Cell queries
bool Minesweeper::isCellRevealed(int r, int c) const {
	return isValidCell(r, c) && grid[r][c].isRevealed;
}

bool Minesweeper::isCellFlagged(int r, int c) const {
	return isValidCell(r, c) && grid[r][c].isFlagged;
}

bool Minesweeper::isCellMine(int r, int c) const {
	return isValidCell(r, c) && grid[r][c].isMine;
}

int Minesweeper::getCellAdjacentMines(int r, int c) const {
	return isValidCell(r, c) ? grid[r][c].adjacentMines : 0;
}

// Private methods
void Minesweeper::initializeGrid() {
	grid.resize(rows, std::vector<Cell>(cols));
}

void Minesweeper::placeMines() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> rowDist(0, rows - 1);
	std::uniform_int_distribution<> colDist(0, cols - 1);

	int minesPlaced = 0;
	while (minesPlaced < totalMines) {
		int r = rowDist(gen);
		int c = colDist(gen);

		if (!grid[r][c].isMine) {
			grid[r][c].isMine = true;
			minesPlaced++;
		}
	}
}

void Minesweeper::calculateAdjacentMines() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (!grid[i][j].isMine) {
				int count = 0;
				for (int di = -1; di <= 1; di++) {
					for (int dj = -1; dj <= 1; dj++) {
						int ni = i + di;
						int nj = j + dj;
						if (isValidCell(ni, nj) && grid[ni][nj].isMine) {
							count++;
						}
					}
				}
				grid[i][j].adjacentMines = count;
			}
		}
	}
}

bool Minesweeper::isValidCell(int r, int c) const {
	return r >= 0 && r < rows && c >= 0 && c < cols;
}

void Minesweeper::startGame() {
	if (!gameStarted) {
		startTime = time(nullptr);
		gameStarted = true;
	}
}

void Minesweeper::revealCell(int r, int c) {
	if (!isValidCell(r, c) || grid[r][c].isRevealed ||
		grid[r][c].isFlagged || gameOver) {
		return;
	}

	startGame();

	grid[r][c].isRevealed = true;
	revealedCells++;

	if (grid[r][c].isMine) {
		gameOver = true;
		revealAllMines();
		return;
	}

	if (grid[r][c].adjacentMines == 0) {
		for (int di = -1; di <= 1; di++) {
			for (int dj = -1; dj <= 1; dj++) {
				revealCell(r + di, c + dj);
			}
		}
	}

	checkWinCondition();
}

void Minesweeper::toggleFlag(int r, int c) {
	if (!isValidCell(r, c) || grid[r][c].isRevealed || gameOver) {
		return;
	}

	startGame();

	if (grid[r][c].isFlagged) {
		grid[r][c].isFlagged = false;
		flaggedMines--;
	}
	else {
		grid[r][c].isFlagged = true;
		flaggedMines++;
	}
}

void Minesweeper::revealAllMines() {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j].isMine) {
				grid[i][j].isRevealed = true;
			}
		}
	}
}

void Minesweeper::checkWinCondition() {
	int totalCells = rows * cols;
	if (revealedCells == totalCells - totalMines) {
		gameWon = true;
		gameOver = true;
	}
}

void Minesweeper::resetGame() {
	revealedCells = 0;
	flaggedMines = 0;
	gameOver = false;
	gameWon = false;
	gameStarted = false;

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			grid[i][j].isRevealed = false;
			grid[i][j].isFlagged = false;
			grid[i][j].isMine = false;
			grid[i][j].adjacentMines = 0;
		}
	}

	placeMines();
	calculateAdjacentMines();
}

void Minesweeper::showMines() {
	std::cout << "\nMine locations (for debugging):\n";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (grid[i][j].isMine) {
				std::cout << "(" << i << "," << j << ") ";
			}
		}
	}
	std::cout << "\n\n";
}
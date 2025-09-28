// Game class declaration

#ifndef MINESWEEPER_CORE_H
#define MINESWEEPER_CORE_H

#include <vector>
#include <ctime>

class Minesweeper {
private:
	struct Cell {
		bool isMine = false;
		bool isRevealed = false;
		bool isFlagged = false;
		int adjacentMines = 0;
	};

	std::vector<std::vector<Cell>> grid;
	int rows, cols, totalMines;
	int revealedCells, flaggedMines;
	bool gameOver, gameWon;
	time_t startTime;
	bool gameStarted;

public:
	Minesweeper(int r = 10, int c = 10, int mines = 15);

	// Getters
	int getRows() const;
	int getCols() const;
	int getTotalMines() const;
	int getRevealedCells() const;
	int getFlaggedMines() const;
	int getRemainingMines() const;
	bool isGameOver() const;
	bool isGameWon() const;
	int getElapsedTime() const;

	// Cell queries
	bool isCellRevealed(int r, int c) const;
	bool isCellFlagged(int r, int c) const;
	bool isCellMine(int r, int c) const;
	int getCellAdjacentMines(int r, int c) const;

	// Game actions
	void revealCell(int r, int c);
	void toggleFlag(int r, int c);
	void resetGame();
	void showMines();

private:
	void initializeGrid();
	void placeMines();
	void calculateAdjacentMines();
	bool isValidCell(int r, int c) const;
	void startGame();
	void revealAllMines();
	void checkWinCondition();
};

#endif

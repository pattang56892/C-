#include "minesweeper_core.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>

#ifdef _WIN32
#include <cstdlib>
#define CLEAR_SCREEN "cls"
#else
#define CLEAR_SCREEN "clear"
#endif

// Helper functions for chess notation
char getColumnLetter(int col) {
	if (col < 26) return 'A' + col;
	// For grids wider than 26 columns, use AA, AB, AC...
	return 'A' + (col % 26);
}

int parseColumn(char letter) {
	if (letter >= 'A' && letter <= 'Z') {
		return letter - 'A';
	}
	if (letter >= 'a' && letter <= 'z') {
		return letter - 'a';
	}
	return -1; // Invalid
}

bool parseChessNotation(const std::string& input, int& row, int& col, int maxRows, int maxCols) {
	if (input.length() < 2) return false;

	// Parse column (letter)
	col = parseColumn(input[0]);
	if (col < 0 || col >= maxCols) return false;

	// Parse row (number, convert from 1-based to 0-based)
	try {
		int userRow = std::stoi(input.substr(1));
		if (userRow < 1 || userRow > maxRows) return false;
		row = userRow - 1; // Convert to 0-based
		return true;
	}
	catch (...) {
		return false;
	}
}

void showGameRules() {
	std::cout << "\n=== MINESWEEPER RULES ===\n";
	std::cout << "OBJECTIVE: Reveal all cells without hitting mines\n\n";
	std::cout << "SYMBOLS:\n";
	std::cout << "  .  = Unrevealed cell\n";
	std::cout << "  F  = Flagged cell (suspected mine)\n";
	std::cout << "  *  = Mine (shown when game ends)\n";
	std::cout << "  1-8= Number of adjacent mines\n";
	std::cout << "     = Empty cell (no adjacent mines)\n\n";
	std::cout << "COORDINATES (Chess-style):\n";
	std::cout << "- Columns use letters: A, B, C, D...\n";
	std::cout << "- Rows use numbers: 1, 2, 3, 4...\n";
	std::cout << "- A1 = top-left corner\n";
	std::cout << "- Examples: A1, B5, Z10\n\n";
	std::cout << "STRATEGY:\n";
	std::cout << "- Start with corners or edges\n";
	std::cout << "- Use numbers to deduce mine locations\n";
	std::cout << "- Flag suspected mines to avoid accidents\n";
	std::cout << "- If a cell shows '3', exactly 3 adjacent cells have mines\n\n";
	std::cout << "Press Enter to continue...";
	std::cin.ignore();
	std::cin.get();
}

void showCommands() {
	std::cout << "\n=== COMMANDS ===\n";
	std::cout << "r <position>   - Reveal cell (e.g., r A1, r B5)\n";
	std::cout << "f <position>   - Toggle flag (e.g., f C3, f Z10)\n";
	std::cout << "h             - Show this help\n";
	std::cout << "rules         - Show game rules\n";
	std::cout << "status        - Show current game status\n";
	std::cout << "new           - Start new game (same difficulty)\n";
	std::cout << "menu          - Return to main menu\n";
	std::cout << "q             - Quit current game\n\n";

	std::cout << "=== COORDINATE EXAMPLES ===\n";
	std::cout << "r A1          - Reveal top-left corner\n";
	std::cout << "f B5          - Flag cell in column B, row 5\n";
	std::cout << "r C10         - Reveal cell in column C, row 10\n\n";

	std::cout << "COORDINATE SYSTEM:\n";
	std::cout << "- Columns: A, B, C, D... (left to right)\n";
	std::cout << "- Rows: 1, 2, 3, 4... (top to bottom)\n";
	std::cout << "- A1 is always the top-left corner\n\n";

	std::cout << "TIPS:\n";
	std::cout << "- Look at column letters and row numbers on grid edges\n";
	std::cout << "- Start with corners (A1, A[max], [max]1, [max][max])\n";
	std::cout << "- Flag cells you suspect contain mines\n";
	std::cout << "- Use revealed numbers to deduce adjacent mine locations\n\n";
}

void showGameStatus(const Minesweeper& game) {
	std::cout << "\n=== GAME STATUS ===\n";
	std::cout << "Grid Size: " << game.getRows() << "x" << game.getCols()
		<< " (A1 to " << getColumnLetter(game.getCols() - 1) << game.getRows() << ")\n";
	std::cout << "Total Mines: " << game.getTotalMines() << "\n";
	std::cout << "Mines Remaining: " << game.getRemainingMines() << "\n";
	std::cout << "Cells Revealed: " << game.getRevealedCells() << "/"
		<< (game.getRows() * game.getCols() - game.getTotalMines()) << "\n";
	std::cout << "Time Elapsed: " << game.getElapsedTime() << " seconds\n";

	if (game.isGameOver()) {
		if (game.isGameWon()) {
			std::cout << "STATUS: VICTORY! All mines found!\n";
		}
		else {
			std::cout << "STATUS: GAME OVER - Mine exploded!\n";
		}
	}
	else {
		std::cout << "STATUS: Game in progress\n";
	}
	std::cout << "\nPress Enter to continue...";
	std::cin.ignore();
	std::cin.get();
}

void displayGrid(const Minesweeper& game) {
	system(CLEAR_SCREEN);

	std::cout << "\n=== MINESWEEPER ===\n";
	std::cout << "Mines remaining: " << game.getRemainingMines() << " | ";
	std::cout << "Revealed: " << game.getRevealedCells() << "/"
		<< (game.getRows() * game.getCols() - game.getTotalMines()) << " | ";
	std::cout << "Time: " << game.getElapsedTime() << "s\n";

	if (game.isGameOver()) {
		if (game.isGameWon()) {
			std::cout << "*** CONGRATULATIONS! YOU WON! ***\n";
		}
		else {
			std::cout << "*** BOOM! GAME OVER! ***\n";
		}
	}
	std::cout << "\n";

	// Column headers (letters)
	std::cout << "    ";
	for (int j = 0; j < game.getCols(); j++) {
		std::cout << std::setw(3) << getColumnLetter(j);
	}
	std::cout << "\n\n";

	// Print grid with row numbers (1-based)
	for (int i = 0; i < game.getRows(); i++) {
		std::cout << std::setw(3) << (i + 1) << " "; // Display 1-based row numbers
		for (int j = 0; j < game.getCols(); j++) {
			char display = ' ';

			if (game.isCellFlagged(i, j)) {
				display = 'F';
			}
			else if (!game.isCellRevealed(i, j)) {
				display = '.';
			}
			else if (game.isCellMine(i, j)) {
				display = '*';
			}
			else if (game.getCellAdjacentMines(i, j) > 0) {
				display = '0' + game.getCellAdjacentMines(i, j);
			}
			else {
				display = ' ';
			}

			std::cout << std::setw(3) << display;
		}
		std::cout << "\n";
	}
	std::cout << "\nType 'h' for help, 'rules' for game rules\n";
	std::cout << "Example: 'r A1' reveals top-left, 'f B5' flags column B row 5\n";
}

bool playTerminalGame(Minesweeper& game) {
	char showRules;
	std::cout << "Show game rules? (y/n): ";
	std::cin >> showRules;
	if (showRules == 'y' || showRules == 'Y') {
		showGameRules();
	}

	std::cout << "\nStarting game... Good luck!\n";
	std::cout << "Use chess notation: A1, B5, C10, etc.\n";
	std::cout << "Type 'h' at any time for help.\n\n";

	while (!game.isGameOver()) {
		displayGrid(game);

		std::string command;
		std::cout << "Enter command: ";
		std::cin >> command;

		if (command == "q" || command == "quit") {
			char confirm;
			std::cout << "Are you sure you want to quit? (y/n): ";
			std::cin >> confirm;
			if (confirm == 'y' || confirm == 'Y') {
				std::cout << "Thanks for playing!\n";
				return false;
			}
			continue;
		}
		else if (command == "menu") {
			char confirm;
			std::cout << "Return to main menu? Current game will be lost. (y/n): ";
			std::cin >> confirm;
			if (confirm == 'y' || confirm == 'Y') {
				return true;
			}
			continue;
		}
		else if (command == "h" || command == "help") {
			showCommands();
			std::cout << "Press Enter to continue...";
			std::cin.ignore();
			std::cin.get();
		}
		else if (command == "rules") {
			showGameRules();
		}
		else if (command == "status") {
			showGameStatus(game);
		}
		else if (command == "new") {
			char confirm;
			std::cout << "Start new game? Current progress will be lost. (y/n): ";
			std::cin >> confirm;
			if (confirm == 'y' || confirm == 'Y') {
				game.resetGame();
				std::cout << "New game started!\n";
			}
		}
		else if (command == "r" || command == "reveal") {
			std::string position;
			std::cout << "Enter position (e.g., A1, B5): ";
			std::cin >> position;

			int row, col;
			if (parseChessNotation(position, row, col, game.getRows(), game.getCols())) {
				game.revealCell(row, col);
			}
			else {
				std::cout << "Invalid position! Use format like A1, B5, C10\n";
				std::cout << "Valid columns: A-" << getColumnLetter(game.getCols() - 1)
					<< ", Valid rows: 1-" << game.getRows() << "\n";
				std::cout << "Press Enter to continue...";
				std::cin.ignore();
				std::cin.get();
			}
		}
		else if (command == "f" || command == "flag") {
			std::string position;
			std::cout << "Enter position to flag (e.g., A1, B5): ";
			std::cin >> position;

			int row, col;
			if (parseChessNotation(position, row, col, game.getRows(), game.getCols())) {
				game.toggleFlag(row, col);
			}
			else {
				std::cout << "Invalid position! Use format like A1, B5, C10\n";
				std::cout << "Valid columns: A-" << getColumnLetter(game.getCols() - 1)
					<< ", Valid rows: 1-" << game.getRows() << "\n";
				std::cout << "Press Enter to continue...";
				std::cin.ignore();
				std::cin.get();
			}
		}
		else {
			std::cout << "Unknown command: '" << command << "'\n";
			std::cout << "Type 'h' for help or 'q' to quit.\n";
			std::cout << "Press Enter to continue...";
			std::cin.ignore();
			std::cin.get();
		}
	}

	// Game ended
	displayGrid(game);
	if (game.isGameWon()) {
		std::cout << "\nVICTORY!\n";
		std::cout << "Time: " << game.getElapsedTime() << " seconds\n";
		std::cout << "Perfect score - all mines avoided!\n";
	}
	else {
		std::cout << "\nGAME OVER!\n";
		std::cout << "Better luck next time!\n";
		std::cout << "Time survived: " << game.getElapsedTime() << " seconds\n";
	}

	char playAgain;
	std::cout << "\nPlay again with same difficulty? (y/n): ";
	std::cin >> playAgain;
	if (playAgain == 'y' || playAgain == 'Y') {
		game.resetGame();
		return playTerminalGame(game);
	}

	return true;
}
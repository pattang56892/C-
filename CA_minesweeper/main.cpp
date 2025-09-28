// Menu + launches UIs

#include "minesweeper_core.h"
#include <iostream>
#include <tuple>
#include <ctime>
#include <fstream>
#include <string>
#include <filesystem>

// Cross-platform browser opening support
#ifdef _WIN32
#include <windows.h>
#define OPEN_COMMAND "start \"\" \""
#define OPEN_SUFFIX "\""
#elif __APPLE__
#define OPEN_COMMAND "open \""
#define OPEN_SUFFIX "\""
#else
#define OPEN_COMMAND "xdg-open \""
#define OPEN_SUFFIX "\""
#endif

// Forward declarations for terminal functions
void displayGrid(const Minesweeper& game);
bool playTerminalGame(Minesweeper& game);

class MinesweeperMenu {
public:
	static void showMainMenu() {
		std::cout << "\n=== MINESWEEPER - CHOOSE INTERFACE ===\n";
		std::cout << "1. Terminal Version (Classic Text)\n";
		std::cout << "2. Qt GUI (Professional Desktop)\n";
		std::cout << "3. Web Browser (HTML/JavaScript)\n";
		std::cout << "4. SDL2 GUI (Lightweight Graphics)\n";
		std::cout << "5. Dear ImGui (Modern Interface)\n";
		std::cout << "6. Show Project Structure\n";
		std::cout << "7. Exit\n";
		std::cout << "Choose interface: ";
	}

	static void showDifficultyMenu() {
		std::cout << "\n=== MINESWEEPER DIFFICULTY ===\n";
		std::cout << "1. Beginner (9x9, 10 mines)\n";
		std::cout << "2. Intermediate (16x16, 40 mines)\n";
		std::cout << "3. Expert (16x30, 99 mines)\n";
		std::cout << "4. Custom\n";
		std::cout << "5. Back to main menu\n";
		std::cout << "Choose difficulty: ";
	}

	static std::tuple<int, int, int> getDifficultySettings(int choice) {
		switch (choice) {
		case 1: return std::make_tuple(9, 9, 10);
		case 2: return std::make_tuple(16, 16, 40);
		case 3: return std::make_tuple(16, 30, 99);
		case 4: {
			int rows, cols, mines;
			std::cout << "Enter rows: ";
			std::cin >> rows;
			std::cout << "Enter columns: ";
			std::cin >> cols;
			std::cout << "Enter number of mines: ";
			std::cin >> mines;

			if (mines >= rows * cols) {
				std::cout << "Too many mines! Using maximum: " << (rows * cols - 1) << "\n";
				mines = rows * cols - 1;
			}
			return std::make_tuple(rows, cols, mines);
		}
		default: return std::make_tuple(9, 9, 10);
		}
	}

	static void showProjectTree() {
		std::ifstream file("projectTree.txt");

		if (!file.is_open()) {
			std::cout << "\n=== PROJECT STRUCTURE ===\n";
			std::cout << "Error: projectTree.txt not found!\n";
			std::cout << "Make sure projectTree.txt is in the same directory as the executable.\n\n";
			std::cout << "QUICK STRUCTURE:\n";
			std::cout << "- minesweeper_core.h/.cpp (Game logic)\n";
			std::cout << "- minesweeper_terminal.cpp (Terminal UI)\n";
			std::cout << "- main.cpp (Menu system)\n\n";
			std::cout << "Press Enter to continue...";
			std::cin.ignore();
			std::cin.get();
			return;
		}

		std::cout << "\n";
		std::string line;
		while (std::getline(file, line)) {
			std::cout << line << "\n";
		}
		file.close();

		std::cout << "\nPress Enter to continue...";
		std::cin.ignore();
		std::cin.get();
	}

	static void startTerminalGame() {
		int choice;
		while (true) {
			showDifficultyMenu();
			std::cin >> choice;

			if (choice == 5) return;

			std::tuple<int, int, int> settings = getDifficultySettings(choice);
			int rows = std::get<0>(settings);
			int cols = std::get<1>(settings);
			int mines = std::get<2>(settings);

			Minesweeper game(rows, cols, mines);
			bool returnToMenu = playTerminalGame(game);
			if (!returnToMenu) {
				return;
			}
		}
	}

	static void startQtGame() {
		std::cout << "\nStarting Qt GUI Version...\n";
		std::cout << "Note: Requires Qt library to be linked.\n";

		int choice;
		showDifficultyMenu();
		std::cin >> choice;

		if (choice == 5) return;

		std::tuple<int, int, int> settings = getDifficultySettings(choice);
		int rows = std::get<0>(settings);
		int cols = std::get<1>(settings);
		int mines = std::get<2>(settings);

		std::cout << "Qt GUI would start here with " << rows << "x" << cols
			<< " grid and " << mines << " mines.\n";
		std::cout << "Press Enter to continue...";
		std::cin.ignore();
		std::cin.get();
	}

	static void startWebGame() {
		std::cout << "\n=== WEB BROWSER VERSION ===\n";
		std::cout << "Starting Web Interface...\n\n";

		// Check if web file exists
		std::ifstream webFile("Web_Interface/minesweeper.html");
		if (!webFile.is_open()) {
			std::cout << "ERROR: Web Interface file not found!\n";
			std::cout << "Expected location: Web_Interface/minesweeper.html\n";
			std::cout << "Please ensure the Web_Interface folder and HTML file exist.\n\n";
			std::cout << "Press Enter to continue...";
			std::cin.ignore();
			std::cin.get();
			return;
		}
		webFile.close();

		std::cout << "Web interface found! Attempting to open in browser...\n";

		// Cross-platform browser opening
#ifdef _WIN32
		// Windows: Get full path
		wchar_t currentPath[1000];
		if (GetCurrentDirectoryW(1000, currentPath)) {
			// Convert wide string to regular string
			std::wstring wpath(currentPath);
			std::string fullPath(wpath.begin(), wpath.end());
			fullPath += "\\Web_Interface\\minesweeper.html";

			std::cout << "Opening: " << fullPath << "\n\n";

			std::string command = OPEN_COMMAND + fullPath + OPEN_SUFFIX;
			int result = system(command.c_str());

			if (result == 0) {
				std::cout << "Successfully opened web interface in browser!\n";
			}
			else {
				std::cout << "Could not auto-open browser.\n";
				std::cout << "Please manually open: " << fullPath << "\n";
			}
		}
		else {
			std::cout << "Could not determine current directory.\n";
			std::cout << "Please manually navigate to Web_Interface/minesweeper.html\n";
		}
#else
		// macOS/Linux: Use relative path
		std::string relativePath = "Web_Interface/minesweeper.html";
		std::cout << "Opening: " << relativePath << "\n\n";

		std::string command = OPEN_COMMAND + relativePath + OPEN_SUFFIX;
		int result = system(command.c_str());

		if (result == 0) {
			std::cout << "Successfully opened web interface in browser!\n";
		}
		else {
			std::cout << "Could not auto-open browser.\n";
			std::cout << "Please manually open: " << relativePath << "\n";
		}
#endif

		std::cout << "The game should now be running in a new browser tab.\n\n";
		std::cout << "Features available in web version:\n";
		std::cout << "- Beautiful visual interface\n";
		std::cout << "- Left click to reveal cells\n";
		std::cout << "- Right click to flag mines\n";
		std::cout << "- Multiple difficulty levels\n";
		std::cout << "- Timer and mine counter\n";
		std::cout << "- Responsive design for mobile/desktop\n";

		std::cout << "\nPress Enter to return to main menu...";
		std::cin.ignore();
		std::cin.get();
	}

	static void startSDLGame() {
		std::cout << "\nStarting SDL2 GUI Version...\n";
		std::cout << "Note: Requires SDL2 library to be linked.\n";
		std::cout << "Press Enter to continue...";
		std::cin.ignore();
		std::cin.get();
	}

	static void startImGuiGame() {
		std::cout << "\nStarting Dear ImGui Version...\n";
		std::cout << "Note: Requires ImGui and graphics backend.\n";
		std::cout << "Press Enter to continue...";
		std::cin.ignore();
		std::cin.get();
	}

	static void run() {
		int choice;
		while (true) {
			showMainMenu();
			std::cin >> choice;

			switch (choice) {
			case 1:
				startTerminalGame();
				break;
			case 2:
				startQtGame();
				break;
			case 3:
				startWebGame();
				break;
			case 4:
				startSDLGame();
				break;
			case 5:
				startImGuiGame();
				break;
			case 6:
				showProjectTree();
				break;
			case 7:
				std::cout << "Goodbye!\n";
				return;
			default:
				std::cout << "Invalid choice!\n";
			}
		}
	}
};

int main() {
	std::srand(std::time(nullptr));
	MinesweeperMenu::run();
	return 0;
}
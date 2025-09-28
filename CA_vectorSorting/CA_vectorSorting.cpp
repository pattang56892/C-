// CA_vectorSorting.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <sstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <numeric>

// Template function to display vector with label
template<typename T>
void displayVector(const std::vector<T>& vec, const std::string& label = "") {
	if (!label.empty()) {
		std::cout << label << ": ";
	}
	for (const auto& element : vec) {
		std::cout << element << " ";
	}
	std::cout << std::endl;
}

// Function to get user input
std::vector<int> getUserNumbers() {
	std::vector<int> numbers;
	std::string input;

	std::cout << "\n=================== NUMBER INPUT ===================\n";
	std::cout << "Please enter 10-15 integers (whole numbers).\n";
	std::cout << "* You can enter positive or negative numbers\n";
	std::cout << "* Examples: 42, -17, 0, 999, -234\n";
	std::cout << "* Enter all numbers on one line, separated by spaces\n";
	std::cout << "* Press Enter when done\n";
	std::cout << "====================================================\n\n";

	while (true) {
		std::cout << "Enter your numbers: ";
		std::getline(std::cin, input);

		// Parse the input
		std::stringstream ss(input);
		std::string token;
		numbers.clear();
		bool validInput = true;

		while (ss >> token) {
			try {
				int num = std::stoi(token);
				numbers.push_back(num);
			}
			catch (const std::invalid_argument&) {
				std::cout << "ERROR: '" << token << "' is not a valid integer.\n";
				validInput = false;
				break;
			}
			catch (const std::out_of_range&) {
				std::cout << "ERROR: '" << token << "' is too large.\n";
				validInput = false;
				break;
			}
		}

		if (!validInput) {
			std::cout << "Please try again with valid integers only.\n\n";
			continue;
		}

		if (numbers.empty()) {
			std::cout << "ERROR: No numbers entered. Please enter at least 10 numbers.\n\n";
			continue;
		}

		if (numbers.size() < 10) {
			std::cout << "ERROR: You entered " << numbers.size() << " numbers. ";
			std::cout << "Please enter at least 10 numbers.\n\n";
			continue;
		}

		if (numbers.size() > 15) {
			std::cout << "ERROR: You entered " << numbers.size() << " numbers. ";
			std::cout << "Please enter no more than 15 numbers.\n\n";
			continue;
		}

		// Valid input
		std::cout << "SUCCESS: You entered " << numbers.size() << " valid numbers.\n";
		break;
	}

	return numbers;
}

void displayResults(const std::vector<int>& originalNumbers) {
	std::cout << "\n================= SORTING RESULTS =================\n";

	// Display original array
	displayVector(originalNumbers, "Your numbers");

	// Sort in ascending order
	std::vector<int> ascending = originalNumbers;
	std::sort(ascending.begin(), ascending.end());
	displayVector(ascending, "Ascending order");

	// Sort in descending order
	std::vector<int> descending = originalNumbers;
	std::sort(descending.begin(), descending.end(), std::greater<int>());
	displayVector(descending, "Descending order");

	// Sort by absolute value
	std::vector<int> byAbsoluteValue = originalNumbers;
	std::sort(byAbsoluteValue.begin(), byAbsoluteValue.end(),
		[](const int& a, const int& b) {
			return std::abs(a) < std::abs(b);
		});
	displayVector(byAbsoluteValue, "By absolute value");

	std::cout << "\n================== STATISTICS ==================\n";

	// Find min and max elements
	auto minElement = *std::min_element(originalNumbers.begin(), originalNumbers.end());
	auto maxElement = *std::max_element(originalNumbers.begin(), originalNumbers.end());
	std::cout << "Minimum value: " << minElement << std::endl;
	std::cout << "Maximum value: " << maxElement << std::endl;

	// Count positive and negative numbers
	int positiveCount = std::count_if(originalNumbers.begin(), originalNumbers.end(),
		[](int n) { return n > 0; });
	int negativeCount = std::count_if(originalNumbers.begin(), originalNumbers.end(),
		[](int n) { return n < 0; });
	int zeroCount = std::count(originalNumbers.begin(), originalNumbers.end(), 0);

	std::cout << "Positive numbers: " << positiveCount << std::endl;
	std::cout << "Negative numbers: " << negativeCount << std::endl;
	std::cout << "Zero count: " << zeroCount << std::endl;

	// Get top 3 largest elements
	std::vector<int> top3 = originalNumbers;
	std::partial_sort(top3.begin(), top3.begin() + std::min(3, (int)top3.size()),
		top3.end(), std::greater<int>());
	std::cout << "Top 3 largest: ";
	for (int i = 0; i < std::min(3, (int)top3.size()); ++i) {
		std::cout << top3[i] << " ";
	}
	std::cout << std::endl;

	// Calculate average
	double sum = 0;
	for (int num : originalNumbers) {
		sum += num;
	}
	double average = sum / originalNumbers.size();
	std::cout << "Average: " << std::fixed << std::setprecision(2) << average << std::endl;

	std::cout << "==================================================\n";
}

int main() {
	std::cout << "VECTOR SORTING & ANALYSIS PROGRAM\n";
	std::cout << "This program will sort your numbers in different ways\n";
	std::cout << "and provide statistical analysis.\n";

	// Get user input
	std::vector<int> userNumbers = getUserNumbers();

	// Display all results
	displayResults(userNumbers);

	std::cout << "\nThank you for using the program!\n";

	return 0;
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

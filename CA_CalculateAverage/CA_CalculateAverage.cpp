#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
#include <locale>
#include <codecvt>

// Explicitly qualify standard library names to avoid ambiguity
using std::wofstream;
using std::wstring;
using std::fixed;
using std::setprecision;
using std::vector;
using std::cout;
using std::endl;
using std::cin;

int main() {
	vector<int> numbers;
	int x;
	double sum = 0;

	// Create output file with UTF-8 encoding
	wofstream outFile("results.txt");

	// Fixed: Use locale::classic() instead of deprecated locale::empty()
	outFile.imbue(std::locale(std::locale::classic(), new std::codecvt_utf8<wchar_t>));

	// Console output - English only
	cout << "========================================" << endl;
	cout << "     AVERAGE CALCULATOR" << endl;
	cout << "========================================" << endl;
	cout << "Enter numbers one by one, press Enter after each number." << endl;
	cout << "When done, type -1 to calculate results." << endl;
	cout << "Start entering numbers:" << endl;
	cout << ">> ";

	// File output with wide strings for Chinese
	outFile << L"========================================" << endl;
	outFile << L"     AVERAGE CALCULATOR / 平均数计算器" << endl;
	outFile << L"========================================" << endl;
	outFile << L"English: Enter numbers, type -1 to finish" << endl;
	outFile << L"中文：输入数字，输入 -1 结束" << endl;
	outFile << L"Numbers entered / 输入的数字: ";

	// Read numbers until -1 is entered
	while (cin >> x) {
		if (x == -1) {
			break;
		}
		numbers.push_back(x);
		sum += x;
		outFile << x << L" ";
		cout << ">> ";
	}

	cout << endl;
	outFile << endl << endl;

	// Check if any numbers were entered
	if (numbers.empty()) {
		cout << "No numbers entered." << endl;
		outFile << L"No numbers entered." << endl;
		outFile.close();
		return 0;
	}

	// Calculate average
	double average = sum / numbers.size();
	cout << fixed << setprecision(2);
	outFile << fixed << setprecision(2);

	cout << "Average: " << average << endl;
	outFile << L"English: Average = " << average << endl;
	outFile << L"中文：平均数 = " << average << endl;

	// Find and display numbers greater than average
	cout << "Numbers greater than average: ";
	outFile << L"English: Numbers greater than average: ";

	bool found = false;
	for (int num : numbers) {
		if (num > average) {
			cout << num << " ";
			outFile << num << L" ";
			found = true;
		}
	}

	if (!found) {
		cout << "None";
		outFile << L"None";
	}
	cout << endl;
	outFile << endl;

	outFile << L"中文：大于平均数的数字：";
	for (int num : numbers) {
		if (num > average) {
			outFile << num << L" ";
		}
	}
	if (!found) {
		outFile << L"没有";
	}
	outFile << endl << endl;

	cout << endl << "Results saved to 'results.txt'!" << endl;
	cout << "Program complete." << endl;

	outFile << L"========================================" << endl;
	outFile << L"English: Calculation complete!" << endl;
	outFile << L"中文：计算完成！" << endl;
	outFile << L"========================================" << endl;

	outFile.close();
	return 0;
}
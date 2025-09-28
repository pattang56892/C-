// CA_CalculateAverage.cpp : This file contains the 'main' function. Program execution begins and ends there.

/*
================================================================================
BILINGUAL AVERAGE CALCULATOR WITH FILE OUTPUT
================================================================================

This program calculates the average of user-entered numbers and identifies
numbers greater than the average. It provides a dual-output approach:

1. CONSOLE OUTPUT: Clean English interface for user interaction
2. FILE OUTPUT: Complete bilingual results saved to 'results.txt'

This design solves Visual Studio's UTF-8 display limitations by keeping the
console interaction simple while preserving Chinese text in a file where
it displays correctly.

FEATURES:
- Interactive number input with -1 termination
- Average calculation with 2 decimal precision
- Identification of above-average numbers
- Dual-language support (English + Simplified Chinese)
- File export for proper character encoding display

AUTHOR: Learning Project
DATE: September 2025
================================================================================
*/

#include <iostream>
#include <vector>
#include <iomanip>
#include <fstream>
using namespace std;

int main() {
    vector<int> numbers;
    int x;
    double sum = 0;

    // Create output file for proper UTF-8 display
    ofstream outFile("results.txt");

    // Welcome message - console (English) and file (bilingual)
    cout << "========================================" << endl;
    cout << "     AVERAGE CALCULATOR" << endl;
    cout << "========================================" << endl;
    cout << endl;

    outFile << "========================================" << endl;
    outFile << "     AVERAGE CALCULATOR / 平均数计算器" << endl;
    outFile << "========================================" << endl;
    outFile << endl;

    cout << "English: Enter numbers one by one, press Enter after each number." << endl;
    cout << "English: When you're done entering numbers, type -1 to calculate results." << endl;
    cout << endl;

    outFile << "English: Enter numbers one by one, press Enter after each number." << endl;
    outFile << "中文：逐个输入数字，每个数字后按回车键。" << endl;
    outFile << "English: When you're done entering numbers, type -1 to calculate results." << endl;
    outFile << "中文：输入完所有数字后，输入 -1 来计算结果。" << endl;
    outFile << endl;

    cout << "Start entering your numbers:" << endl;
    cout << ">> ";

    // Read numbers until -1 is entered
    while (cin >> x) {
        if (x == -1) {
            break;
        }
        numbers.push_back(x);
        sum += x;
        cout << ">> ";
    }

    cout << endl;

    // Check if any numbers were entered
    if (numbers.empty()) {
        cout << "English: No numbers entered. Please run the program again." << endl;
        outFile << "English: No numbers entered. Please run the program again." << endl;
        outFile << "中文：未输入任何数字。请重新运行程序。" << endl;
        outFile.close();
        return 0;
    }

    // Display entered numbers
    cout << "Numbers you entered: ";
    outFile << "English: Numbers you entered: ";
    outFile << "中文：您输入的数字：";
    for (size_t i = 0; i < numbers.size(); i++) {
        cout << numbers[i];
        outFile << numbers[i];
        if (i < numbers.size() - 1) {
            cout << ", ";
            outFile << ", ";
        }
    }
    cout << endl << endl;
    outFile << endl << endl;

    // Calculate average
    double average = sum / numbers.size();
    cout << fixed << setprecision(2);
    outFile << fixed << setprecision(2);

    cout << "Average = " << average << endl;
    outFile << "English: Average = " << average << endl;
    outFile << "中文：平均数 = " << average << endl;
    cout << endl;
    outFile << endl;

    // Find and display numbers greater than average
    cout << "Numbers greater than average: ";
    outFile << "English: Numbers greater than average: ";
    outFile << "中文：大于平均数的数字：";

    bool found = false;
    for (int num : numbers) {
        if (num > average) {
            cout << num << " ";
            outFile << num << " ";
            found = true;
        }
    }

    if (!found) {
        cout << "None";
        outFile << "None / 没有";
    }
    cout << endl << endl;
    outFile << endl << endl;

    cout << "========================================" << endl;
    cout << "Calculation complete! Check 'results.txt' for bilingual output." << endl;
    cout << "========================================" << endl;

    outFile << "========================================" << endl;
    outFile << "English: Calculation complete!" << endl;
    outFile << "中文：计算完成！" << endl;
    outFile << "========================================" << endl;

    outFile.close();

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

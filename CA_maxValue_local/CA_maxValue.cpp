// CA_maxValue.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Function declaration - finds maximum of three integers
#include <iostream>
using namespace std;  // This line was missing!

// Function declaration - finds maximum of three integers
int findMax(int x, int y, int z);

int main() {
	int a, b, c, result;

	cout << "Enter three integers: ";
	cin >> a >> b >> c;

	result = findMax(a, b, c);
	cout << "The maximum value is: " << result << endl;

	return 0;
}

// Function definition - Method 1: Using conditional statements
int findMax(int x, int y, int z) {
	int maxVal;

	if (x >= y && x >= z) {
		maxVal = x;
	}
	else if (y >= x && y >= z) {
		maxVal = y;
	}
	else {
		maxVal = z;
	}

	return maxVal;
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

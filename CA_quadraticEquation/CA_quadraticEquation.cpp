// CA_quadraticEquation.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

int main() {
	double a, b, c;
	double discriminant, x1, x2;

	// Display instructions and input coefficients
	cout << "=== Quadratic Equation Solver ===" << endl;
	cout << "This program solves equations of the form: ax^2 + bx + c = 0" << endl;
	cout << "Please enter the three coefficients:" << endl;
	cout << "Coefficient a (cannot be 0): ";
	cin >> a;
	cout << "Coefficient b: ";
	cin >> b;
	cout << "Coefficient c: ";
	cin >> c;
	cout << endl;

	// Check if a is zero
	if (a == 0) {
		cout << "Error: Coefficient 'a' cannot be zero for a quadratic equation!" << endl;
		cout << "Please restart the program and enter a non-zero value for 'a'." << endl;
		return 1;
	}

	// Display the equation being solved
	cout << "Solving the equation: ";
	if (a == 1) cout << "x^2";
	else if (a == -1) cout << "-x^2";
	else cout << a << "x^2";

	if (b > 0) cout << " + " << b << "x";
	else if (b < 0) cout << " - " << (-b) << "x";

	if (c > 0) cout << " + " << c;
	else if (c < 0) cout << " - " << (-c);

	cout << " = 0" << endl;
	cout << "----------------------------------------" << endl;

	// Calculate discriminant
	discriminant = b * b - 4 * a * c;

	// Set output precision to 2 decimal places
	cout << fixed << setprecision(2);

	// Determine the nature of roots based on discriminant
	if (discriminant > 0) {
		// Two distinct real roots
		x1 = (-b + sqrt(discriminant)) / (2 * a);
		x2 = (-b - sqrt(discriminant)) / (2 * a);

		cout << "The equation has two distinct real roots:" << endl;
		cout << "x1 = " << x1 << endl;
		cout << "x2 = " << x2 << endl;
	}
	else if (discriminant == 0) {
		// Two equal real roots (one repeated root)
		x1 = -b / (2 * a);

		cout << "The equation has two equal real roots:" << endl;
		cout << "x1 = x2 = " << x1 << endl;
	}
	else {
		// Complex roots (discriminant < 0)
		double realPart = -b / (2 * a);
		double imaginaryPart = sqrt(-discriminant) / (2 * a);

		cout << "The equation has two complex roots:" << endl;
		cout << "x1 = " << realPart << " + " << imaginaryPart << "i" << endl;
		cout << "x2 = " << realPart << " - " << imaginaryPart << "i" << endl;
	}

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

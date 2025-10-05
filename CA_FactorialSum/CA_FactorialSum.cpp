// CA_FactorialSum.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

void clearInput() {
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void printHeader() {
	cout << "\n========================================" << endl;
	cout << "  MATHEMATICAL SERIES CALCULATOR" << endl;
	cout << "========================================\n" << endl;

	cout << "This C++ program is designed to illustrate the calculation of two" << endl;
	cout << "specific mathematical series: a Telescoping Series and a Sum of Factorials.\n" << endl;

	cout << "----------------------------------------" << endl;
	cout << "1) TELESCOPING SERIES" << endl;
	cout << "----------------------------------------" << endl;
	cout << "Formula: Sum from n=1 to N of 1/(n(n+1))" << endl;
	cout << "       = 1/(1*2) + 1/(2*3) + 1/(3*4) + ... + 1/(N*(N+1))\n" << endl;

	cout << "WHY IT'S SPECIAL:" << endl;
	cout << "This type of series is special because each term can be expressed" << endl;
	cout << "as a difference:" << endl;
	cout << "   1/(n(n+1)) = 1/n - 1/(n+1)" << endl;
	cout << "This causes intermediate terms to cancel out (a process called" << endl;
	cout << "\"telescoping\"). The final sum is simply N/(N+1).\n" << endl;

	cout << "Example: For N=2009, the sum ≈ 2009/2010 ≈ 0.9995\n" << endl;

	cout << "ALGORITHM FLOWCHART:" << endl;
	cout << "   +-----------+" << endl;
	cout << "   |   Start   |" << endl;
	cout << "   +-----+-----+" << endl;
	cout << "         |" << endl;
	cout << "         v" << endl;
	cout << "   +-----------+" << endl;
	cout << "   |   n = 1   |  <-- Initialize counter" << endl;
	cout << "   +-----+-----+" << endl;
	cout << "         |" << endl;
	cout << "         v" << endl;
	cout << "   +-----------+" << endl;
	cout << "   |   s = 0   |  <-- Initialize sum" << endl;
	cout << "   +-----+-----+" << endl;
	cout << "         |" << endl;
	cout << "         v" << endl;
	cout << "   +---------------+" << endl;
	cout << "   |  n <= 2009?   |  <-- Loop condition" << endl;
	cout << "   +-------+-------+" << endl;
	cout << "          / \\" << endl;
	cout << "       Yes   No" << endl;
	cout << "        |     |" << endl;
	cout << "        v     v" << endl;
	cout << "  +----------+  +----------+" << endl;
	cout << "  |term = 1/ |  | Output:s |" << endl;
	cout << "  |(n*(n+1))|  +-----+----+" << endl;
	cout << "  +-----+----+        |" << endl;
	cout << "        |             v" << endl;
	cout << "        v       +----------+" << endl;
	cout << "  +----------+  | Result:  |" << endl;
	cout << "  |s = s +   |  |  0.9995  |" << endl;
	cout << "  |   term   |  +-----+----+" << endl;
	cout << "  +-----+----+        |" << endl;
	cout << "        |             v" << endl;
	cout << "        v       +---------+" << endl;
	cout << "  +----------+  |   End   |" << endl;
	cout << "  | n = n+1  |  +---------+" << endl;
	cout << "  +-----+----+" << endl;
	cout << "        |" << endl;
	cout << "        +---------> (Loop back to condition)" << endl;
	cout << endl;

	cout << "----------------------------------------" << endl;
	cout << "2) FACTORIAL SUM (Limited)" << endl;
	cout << "----------------------------------------" << endl;
	cout << "Formula: 1! + 2! + 3! + ... + N!" << endl;
	cout << "       = 1 + 2 + 6 + 24 + 120 + ...\n" << endl;

	cout << "WHY IT'S LIMITED:" << endl;
	cout << "Factorials (n!) grow extremely fast - faster than exponential!" << endl;
	cout << "The code uses 'unsigned long long', which can only handle sums" << endl;
	cout << "up to around 20! before the result overflows and becomes incorrect." << endl;
	cout << "   Example: 20! = 2,432,902,008,176,640,000" << endl;
	cout << "   Note: 21! = 51,090,942,171,709,440,000 (already overflows!)\n" << endl;

	cout << "For larger values, you would need arbitrary precision libraries" << endl;
	cout << "like GMP or Boost.Multiprecision.\n" << endl;
}

void telescopingSum(int n) {
	cout << "\n--- TELESCOPING SERIES CALCULATION ---" << endl;
	cout << "Computing: 1/(1*2) + 1/(2*3) + ... + 1/(" << n << "*" << (n + 1) << ")\n" << endl;

	double s = 0.0;

	// Show first few terms for understanding
	cout << "First few terms:" << endl;
	for (int i = 1; i <= min(5, n); i++) {
		double term = 1.0 / (i * (i + 1));
		cout << "  Term " << i << ": 1/(" << i << "*" << (i + 1) << ") = "
			<< fixed << setprecision(6) << term << endl;
	}
	if (n > 5) {
		cout << "  ... (computing remaining " << (n - 5) << " terms)" << endl;
	}

	// Calculate sum
	for (int i = 1; i <= n; i++) {
		double term = 1.0 / (i * (i + 1));
		s = s + term;
	}

	cout << "\nRESULTS:" << endl;
	cout << "  Iterative sum: " << fixed << setprecision(10) << s << endl;

	// Direct formula
	double direct = static_cast<double>(n) / (n + 1);
	cout << "  Direct formula (n/(n+1)): " << fixed << setprecision(10) << direct << endl;
	cout << "  Simplified: " << n << "/" << (n + 1) << endl;

	// Show the telescoping pattern
	cout << "\nWhy it works (telescoping pattern):" << endl;
	cout << "  1/(k*(k+1)) = 1/k - 1/(k+1)" << endl;
	cout << "  So terms cancel: (1/1 - 1/2) + (1/2 - 1/3) + ... + (1/" << n << " - 1/" << (n + 1) << ")" << endl;
	cout << "  Everything cancels except: 1/1 - 1/" << (n + 1) << " = " << n << "/" << (n + 1) << endl;
}

void factorialSum(int n) {
	cout << "\n--- FACTORIAL SUM CALCULATION ---" << endl;
	cout << "Computing: 1! + 2! + 3! + ... + " << n << "!\n" << endl;

	if (n > 20) {
		cout << "WARNING: n > 20 will cause overflow!" << endl;
		cout << "Limiting calculation to n = 20\n" << endl;
		n = 20;
	}

	unsigned long long s = 0;
	unsigned long long t = 1;

	// Show calculation process
	cout << "Calculation steps:" << endl;
	for (int i = 1; i <= min(10, n); i++) {
		t = t * i;
		s = s + t;
		cout << "  " << i << "! = " << t;
		if (i <= 5) {
			cout << " (sum so far: " << s << ")";
		}
		cout << endl;
	}

	if (n > 10) {
		cout << "  ... (computing remaining factorials)" << endl;
		for (int i = 11; i <= n; i++) {
			t = t * i;
			s = s + t;
		}
	}

	cout << "\nFINAL RESULT:" << endl;
	cout << "  Sum of factorials (1! + 2! + ... + " << n << "!): " << s << endl;

	// Show how fast factorials grow
	cout << "\nFactorial growth illustration:" << endl;
	cout << "  10! = 3,628,800" << endl;
	cout << "  15! = 1,307,674,368,000" << endl;
	cout << "  20! = 2,432,902,008,176,640,000" << endl;
	cout << "  (21! would overflow unsigned long long!)" << endl;
}

int main() {
	printHeader();

	char choice;
	do {
		cout << "\n========================================" << endl;
		cout << "Choose an option:" << endl;
		cout << "  1 - Calculate Telescoping Series" << endl;
		cout << "  2 - Calculate Factorial Sum" << endl;
		cout << "  3 - Show original example (n=2009 & n=20)" << endl;
		cout << "  Q - Quit" << endl;
		cout << "========================================" << endl;
		cout << "Your choice: ";
		cin >> choice;

		if (choice == '1') {
			int n;
			cout << "\nEnter n (recommended: 1-10000): ";
			while (!(cin >> n) || n < 1) {
				cout << "Invalid input! Please enter a positive integer: ";
				clearInput();
			}
			telescopingSum(n);

		}
		else if (choice == '2') {
			int n;
			cout << "\nEnter n (must be 1-20, will auto-limit if larger): ";
			while (!(cin >> n) || n < 1) {
				cout << "Invalid input! Please enter a positive integer: ";
				clearInput();
			}
			factorialSum(n);

		}
		else if (choice == '3') {
			cout << "\n=== ORIGINAL EXAMPLES ===" << endl;
			telescopingSum(2009);
			factorialSum(20);

		}
		else if (choice == 'q' || choice == 'Q') {
			cout << "\nThank you for using the Mathematical Series Calculator!" << endl;
			break;

		}
		else {
			cout << "\nInvalid choice! Please try again." << endl;
		}

		cout << "\nPress Enter to continue...";
		clearInput();
		cin.get();

	} while (true);

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

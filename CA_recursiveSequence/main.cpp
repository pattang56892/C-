// CA_recursiveSequence.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include "chinese_translator.h"  // Add this line after other includes
#include <windows.h>
using namespace std;

// Function to compute GCD for fraction simplification
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a % b);
}

// Function to compute a_n using the recursive formula (for verification)
double computeRecursive(int n) {
	if (n == 1) return 4.0;
	double a = 4.0;
	for (int i = 1; i < n; i++) {
		a = (4 * a - 1) / (a + 2);
	}
	return a;
}

// Function to compute a_n using closed-form formula
void computeClosedForm(int n, int& numerator, int& denominator) {
	numerator = n + 3;
	denominator = n;
	// Simplify the fraction
	int divisor = gcd(numerator, denominator);
	numerator /= divisor;
	denominator /= divisor;
}

void pressEnterToContinue() {
	cout << "\n[Press ENTER to continue...]";
	cin.ignore();
	cin.get();
	cout << "\n";
}

void displayWelcome() {
	cout << "================================================================\n";
	cout << "     RECURSIVE SEQUENCE SOLVER - EDUCATIONAL VERSION            \n";
	cout << "================================================================\n\n";

	cout << "Welcome! This program will teach you how to solve recursive\n";
	cout << "sequences and find shortcuts (closed-form formulas).\n";
	cout << "Don't worry if you're not a math expert - we'll explain\n";
	cout << "everything step by step!\n\n";

	pressEnterToContinue();
}

void explainProblem() {
	cout << "================================================================\n";
	cout << "STEP 1: UNDERSTANDING THE PROBLEM\n";
	cout << "================================================================\n\n";

	cout << "WHAT IS A RECURSIVE SEQUENCE?\n";
	cout << "Think of it like a chain reaction:\n";
	cout << "  - You start with ONE number (the first term)\n";
	cout << "  - You use a RECIPE (formula) to get the next number\n";
	cout << "  - You repeat this process over and over\n\n";

	cout << "OUR SPECIFIC PROBLEM:\n";
	cout << "  Starting point: a(1) = 4\n";
	cout << "  Recipe: a(n+1) = (4 * a(n) - 1) / (a(n) + 2)\n\n";

	cout << "In plain English:\n";
	cout << "  'To get the NEXT term, take the CURRENT term,\n";
	cout << "   multiply it by 4, subtract 1, then divide by\n";
	cout << "   the current term plus 2.'\n\n";

	cout << "THE CHALLENGE:\n";
	cout << "  What if we want to find a(1000)?\n";
	cout << "  Using the recipe, we'd need to calculate 999 terms first!\n";
	cout << "  That's super slow and annoying.\n\n";

	cout << "THE GOAL:\n";
	cout << "  Find a SHORTCUT formula that lets us jump directly to ANY term!\n";
	cout << "  (This is called a 'closed-form formula')\n";

	pressEnterToContinue();
}

void demonstrateRecursive() {
	cout << "================================================================\n";
	cout << "STEP 2: THE SLOW WAY (RECURSIVE CALCULATION)\n";
	cout << "================================================================\n\n";

	cout << "Let's manually calculate the first 5 terms using our recipe:\n\n";

	cout << "Term 1: a(1) = 4 (given)\n";
	cout << "  --> We START here!\n\n";

	cout << "Term 2: a(2) = (4 * a(1) - 1) / (a(1) + 2)\n";
	cout << "             = (4 * 4 - 1) / (4 + 2)\n";
	cout << "             = (16 - 1) / 6\n";
	cout << "             = 15 / 6\n";
	cout << "             = 2.5\n";
	cout << "  --> We used a(1) to get a(2)\n\n";

	cout << "Term 3: a(3) = (4 * a(2) - 1) / (a(2) + 2)\n";
	cout << "             = (4 * 2.5 - 1) / (2.5 + 2)\n";
	cout << "             = (10 - 1) / 4.5\n";
	cout << "             = 9 / 4.5\n";
	cout << "             = 2.0\n";
	cout << "  --> We used a(2) to get a(3)\n\n";

	cout << "Term 4: a(4) = (4 * 2.0 - 1) / (2.0 + 2)\n";
	cout << "             = (8 - 1) / 4\n";
	cout << "             = 7 / 4\n";
	cout << "             = 1.75\n\n";

	cout << "Term 5: a(5) = (4 * 1.75 - 1) / (1.75 + 2)\n";
	cout << "             = (7 - 1) / 3.75\n";
	cout << "             = 6 / 3.75\n";
	cout << "             = 1.6\n\n";

	cout << "NOTICE THE PROBLEM:\n";
	cout << "  - To get a(5), we needed a(4)\n";
	cout << "  - To get a(4), we needed a(3)\n";
	cout << "  - To get a(3), we needed a(2)\n";
	cout << "  - To get a(2), we needed a(1)\n\n";

	cout << "This is like climbing stairs - you MUST step on every stair!\n";
	cout << "For a(100), you'd need to calculate 99 terms first. Ugh!\n";

	pressEnterToContinue();
}

void findPattern() {
	cout << "================================================================\n";
	cout << "STEP 3: DETECTIVE WORK - FINDING THE PATTERN\n";
	cout << "================================================================\n\n";

	cout << "Let's write our calculated terms as fractions:\n\n";

	cout << "  a(1) = 4   = 4/1\n";
	cout << "  a(2) = 2.5 = 5/2\n";
	cout << "  a(3) = 2.0 = 6/3\n";
	cout << "  a(4) = 1.75 = 7/4\n";
	cout << "  a(5) = 1.6 = 8/5\n\n";

	cout << "Hmm... Let's look at the numerators (top numbers):\n";
	cout << "  4, 5, 6, 7, 8...\n";
	cout << "  --> They increase by 1 each time!\n\n";

	cout << "And the denominators (bottom numbers):\n";
	cout << "  1, 2, 3, 4, 5...\n";
	cout << "  --> They're just counting numbers!\n\n";

	cout << "AHA! PATTERN DISCOVERED:\n";
	cout << "  Numerator = n + 3\n";
	cout << "  Denominator = n\n\n";

	cout << "Let's check:\n";
	cout << "  n=1: numerator = 1+3 = 4, denominator = 1  --> 4/1 ✓\n";
	cout << "  n=2: numerator = 2+3 = 5, denominator = 2  --> 5/2 ✓\n";
	cout << "  n=3: numerator = 3+3 = 6, denominator = 3  --> 6/3 ✓\n";
	cout << "  n=4: numerator = 4+3 = 7, denominator = 4  --> 7/4 ✓\n";
	cout << "  n=5: numerator = 5+3 = 8, denominator = 5  --> 8/5 ✓\n\n";

	cout << "EUREKA! We found a shortcut formula:\n\n";
	cout << "       a(n) = (n + 3) / n\n\n";

	pressEnterToContinue();
}

void demonstrateShortcut() {
	cout << "================================================================\n";
	cout << "STEP 4: THE FAST WAY (CLOSED-FORM FORMULA)\n";
	cout << "================================================================\n\n";

	cout << "Now we have our magic formula: a(n) = (n + 3) / n\n\n";

	cout << "Let's test it! We'll calculate a(100):\n\n";

	cout << "THE OLD WAY (Recursive):\n";
	cout << "  a(100) = use a(99)\n";
	cout << "  a(99) = use a(98)\n";
	cout << "  ...\n";
	cout << "  (99 calculations needed!)\n\n";

	cout << "THE NEW WAY (Closed-form):\n";
	cout << "  a(100) = (100 + 3) / 100\n";
	cout << "         = 103 / 100\n";
	cout << "         = 1.03\n";
	cout << "  (Just 1 calculation!)\n\n";

	cout << "Let's try an even bigger number - a(985):\n";
	cout << "  a(985) = (985 + 3) / 985\n";
	cout << "         = 988 / 985\n";
	cout << "         = 1.00304568...\n\n";

	cout << "INSTANT! No need to calculate 984 terms first!\n\n";

	cout << "WHY THIS WORKS:\n";
	cout << "  The recursive formula was hiding a simple pattern.\n";
	cout << "  By calculating several terms and looking for patterns,\n";
	cout << "  we discovered the shortcut!\n\n";

	cout << "BONUS INSIGHT:\n";
	cout << "  Notice: as n gets bigger, a(n) gets closer to 1\n";
	cout << "  a(10) = 13/10 = 1.3\n";
	cout << "  a(100) = 103/100 = 1.03\n";
	cout << "  a(1000) = 1003/1000 = 1.003\n";
	cout << "  a(infinity) approaches 1!\n";

	pressEnterToContinue();
}

void showMathProof() {
	cout << "================================================================\n";
	cout << "STEP 5: WHY IT WORKS (OPTIONAL MATH PROOF)\n";
	cout << "================================================================\n\n";

	cout << "If you want to understand the mathematical proof, read on.\n";
	cout << "Otherwise, just know that our formula IS correct!\n\n";

	cout << "Do you want to see the mathematical proof? (y/n): ";
	char choice;
	cin >> choice;

	if (choice == 'y' || choice == 'Y') {
		cout << "\n--- MATHEMATICAL PROOF ---\n\n";

		cout << "We use a clever substitution trick:\n\n";

		cout << "1. Let b(n) = a(n) - 1\n";
		cout << "   (We're shifting our sequence down by 1)\n\n";

		cout << "2. Then a(n) = b(n) + 1\n\n";

		cout << "3. Substitute into our original formula:\n";
		cout << "   a(n+1) = (4*a(n) - 1) / (a(n) + 2)\n";
		cout << "   b(n+1) + 1 = (4*(b(n) + 1) - 1) / ((b(n) + 1) + 2)\n";
		cout << "   b(n+1) + 1 = (4*b(n) + 3) / (b(n) + 3)\n\n";

		cout << "4. Solve for b(n+1):\n";
		cout << "   b(n+1) = (4*b(n) + 3) / (b(n) + 3) - 1\n";
		cout << "   b(n+1) = (4*b(n) + 3 - b(n) - 3) / (b(n) + 3)\n";
		cout << "   b(n+1) = (3*b(n)) / (b(n) + 3)\n\n";

		cout << "5. Calculate b(1):\n";
		cout << "   b(1) = a(1) - 1 = 4 - 1 = 3\n\n";

		cout << "6. Through pattern recognition (or induction),\n";
		cout << "   we can prove that b(n) = 3/n\n\n";

		cout << "7. Convert back to a(n):\n";
		cout << "   a(n) = b(n) + 1\n";
		cout << "   a(n) = 3/n + 1\n";
		cout << "   a(n) = (3 + n) / n\n";
		cout << "   a(n) = (n + 3) / n  ✓\n\n";

		cout << "That's how we PROVE the formula is correct!\n";
	}
	else {
		cout << "\nNo problem! The important thing is you understand\n";
		cout << "how to USE the formula: a(n) = (n + 3) / n\n";
	}

	pressEnterToContinue();
}

void showSummary() {
	cout << "================================================================\n";
	cout << "SUMMARY - WHAT YOU LEARNED\n";
	cout << "================================================================\n\n";

	cout << "1. RECURSIVE SEQUENCES are like chain reactions:\n";
	cout << "   Each term depends on the previous term(s)\n\n";

	cout << "2. CALCULATING RECURSIVELY is slow:\n";
	cout << "   You must calculate every term in order\n\n";

	cout << "3. FINDING PATTERNS can reveal shortcuts:\n";
	cout << "   Calculate several terms and look for patterns\n\n";

	cout << "4. CLOSED-FORM FORMULAS are instant:\n";
	cout << "   Jump directly to any term without intermediate steps\n\n";

	cout << "5. FOR THIS PROBLEM:\n";
	cout << "   Original: a(1) = 4, a(n+1) = (4*a(n) - 1)/(a(n) + 2)\n";
	cout << "   Shortcut: a(n) = (n + 3) / n\n\n";

	cout << "================================================================\n\n";
}

int main() {
	// Enable UTF-8 console output
	SetConsoleOutputCP(CP_UTF8);

	displayWelcome();

	explainProblem();

	demonstrateRecursive();

	findPattern();

	demonstrateShortcut();

	showMathProof();

	showSummary();

	cout << "Now YOU try it! Let's calculate some terms!\n\n";

	while (true) {
		cout << "================================================================\n";
		cout << "Enter the term number n (positive integer, or 0 to exit): ";
		int n;
		cin >> n;

		// Exit condition
		if (n == 0) {
			cout << "\nGreat job! You now understand recursive sequences!\n";
			cout << "Keep practicing and you'll become a pattern-finding expert!\n\n";

			// Generate Chinese version for non-English speaking team members
			cout << "Generating Simplified Chinese version for your team...\n";
			saveChineseVersion();

			cout << "Goodbye! :)\n";
			break;
		}

		// Input validation
		if (cin.fail() || n < 1) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "\nOops! Please enter a positive whole number.\n\n";
			continue;
		}

		// Compute using closed-form formula
		int numerator, denominator;
		computeClosedForm(n, numerator, denominator);
		double decimalValue = (double)numerator / denominator;

		// Display results with explanation
		cout << "\n================================================================\n";
		cout << "  CALCULATING a(" << n << ") USING OUR SHORTCUT FORMULA\n";
		cout << "================================================================\n\n";

		cout << "Formula: a(n) = (n + 3) / n\n\n";

		cout << "Substituting n = " << n << ":\n";
		cout << "  a(" << n << ") = (" << n << " + 3) / " << n << "\n";
		cout << "        = " << (n + 3) << " / " << n << "\n";

		if (numerator != (n + 3) || denominator != n) {
			cout << "        = " << numerator << " / " << denominator << " (simplified)\n";
		}

		cout << "        = " << fixed << setprecision(10) << decimalValue << "\n\n";

		// Verification for smaller terms
		if (n <= 15) {
			cout << "Let's verify using the SLOW recursive method:\n";
			double recursiveValue = computeRecursive(n);
			cout << "  Recursive result: " << fixed << setprecision(10) << recursiveValue << "\n";
			double error = abs(decimalValue - recursiveValue);

			if (error < 1e-10) {
				cout << "  Perfect match! Our shortcut formula works! ✓\n";
			}
			else {
				cout << "  Difference: " << scientific << setprecision(2) << error << "\n";
			}
			cout << "\n";
		}
		else {
			cout << "IMAGINE if you had to calculate this recursively!\n";
			cout << "You would need to compute " << (n - 1) << " terms first.\n";
			cout << "Our shortcut formula saves SO much time!\n\n";
		}

		cout << "================================================================\n\n";
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

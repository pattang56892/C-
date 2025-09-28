// CA_loanCalculation.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <stdio.h>
#include <math.h>

// Function to calculate number of payments needed to pay off a loan
double calculatePayments(double principal, double monthlyPayment, double monthlyRate) {
	// Formula: n = log(1 + (P * r) / PMT) / log(1 + r)
	// Where: P = principal, r = monthly rate, PMT = monthly payment

	double ratio = (principal * monthlyRate) / monthlyPayment;
	double numerator = log(1 + ratio);
	double denominator = log(1 + monthlyRate);

	return numerator / denominator;
}

// Function to validate inputs
int validateInputs(double principal, double payment, double rate) {
	if (principal <= 0) {
		printf("Error: Principal amount must be positive!\n");
		return 0;
	}
	if (payment <= 0) {
		printf("Error: Monthly payment must be positive!\n");
		return 0;
	}
	if (rate < 0) {
		printf("Error: Interest rate cannot be negative!\n");
		return 0;
	}

	// Check if payment is sufficient to cover interest
	double minPayment = principal * rate;
	if (payment <= minPayment) {
		printf("Error: Monthly payment ($%.2f) is too low!\n", payment);
		printf("Minimum payment needed: $%.2f\n", minPayment + 0.01);
		return 0;
	}

	return 1;
}

int main() {
	double principal, monthlyPayment, annualRate, monthlyRate;
	double numberOfPayments;
	int years, months;

	printf("===============================================================\n");
	printf("|                    LOAN PAYMENT CALCULATOR                  |\n");
	printf("===============================================================\n\n");

	printf("IMPORTANT INPUT INSTRUCTIONS:\n");
	printf("   * Enter numbers WITHOUT commas or special characters\n");
	printf("   * Use decimal point for cents (e.g., 1500.50)\n");
	printf("   * For percentages, enter just the number (e.g., 5.5 for 5.5%%)\n\n");

	printf("CORRECT EXAMPLES:\n");
	printf("   Principal: 50000 (for $50,000)\n");
	printf("   Payment:   850.50 (for $850.50)\n");
	printf("   Rate:      6.25 (for 6.25%% annual)\n\n");
	printf("INCORRECT EXAMPLES:\n");
	printf("   DON'T use: 50,000 or $50000 or 6.25%%\n");
	printf("===============================================================\n\n");

	// Get user input with error checking and helpful prompts
	printf("Enter the loan principal amount:\n");
	printf("   Example: 50000 (for $50,000)\n");
	printf("   Amount: $");
	while (scanf_s("%lf", &principal) != 1) {
		printf("\nInvalid format! Please enter numbers only (no commas, no $).\n");
		printf("   Example: 50000\n");
		printf("   Try again: $");
		// Clear input buffer
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
	}

	printf("\nEnter your monthly payment amount:\n");
	printf("   Example: 850.50 (for $850.50)\n");
	printf("   Amount: $");
	while (scanf_s("%lf", &monthlyPayment) != 1) {
		printf("\nInvalid format! Please enter numbers only (no commas, no $).\n");
		printf("   Example: 850.50\n");
		printf("   Try again: $");
		// Clear input buffer
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
	}

	printf("\nEnter the annual interest rate:\n");
	printf("   Example: 6.25 (for 6.25%% per year)\n");
	printf("   Rate: ");
	while (scanf_s("%lf", &annualRate) != 1) {
		printf("\nInvalid format! Please enter numbers only (no %% symbol).\n");
		printf("   Example: 6.25\n");
		printf("   Try again: ");
		// Clear input buffer
		int c;
		while ((c = getchar()) != '\n' && c != EOF);
	}

	// Convert annual rate to monthly decimal rate
	monthlyRate = (annualRate / 100.0) / 12.0;

	printf("\n===============================================================\n");
	printf("|                      INPUT SUMMARY                         |\n");
	printf("===============================================================\n");
	printf("Principal Amount:        $%.2f\n", principal);
	printf("Monthly Payment:         $%.2f\n", monthlyPayment);
	printf("Annual Interest Rate:    %.2f%%\n", annualRate);
	printf("Monthly Interest Rate:   %.4f%%\n", monthlyRate * 100);
	printf("===============================================================\n");

	// Validate inputs
	if (!validateInputs(principal, monthlyPayment, monthlyRate)) {
		return 1;
	}

	// Calculate number of payments
	numberOfPayments = calculatePayments(principal, monthlyPayment, monthlyRate);

	// Convert to years and months
	years = (int)(numberOfPayments / 12);
	months = (int)(numberOfPayments) % 12;

	// Calculate total amount paid and interest
	double totalPaid = monthlyPayment * numberOfPayments;
	double totalInterest = totalPaid - principal;

	// Display results
	printf("\n===============================================================\n");
	printf("|                    CALCULATION RESULTS                     |\n");
	printf("===============================================================\n");
	printf("Number of payments needed:  %.1f payments\n", numberOfPayments);
	printf("Time to pay off loan:       %d years and %d months\n", years, months);
	printf("Total amount to be paid:    $%.2f\n", totalPaid);
	printf("Total interest paid:        $%.2f\n", totalInterest);
	printf("Interest as %% of principal: %.1f%%\n", (totalInterest / principal) * 100);
	printf("===============================================================\n");
	printf("\nCalculation completed successfully!\n");

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

// CA_removeDigits.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // For atoi, or for malloc/free if you go that route

// To suppress scanf_s warnings if sticking with standard scanf
// #define _CRT_SECURE_NO_WARNINGS // No longer necessary for strcpy_s or scanf_s if used directly

// Function to remove k digits to get the smallest number
void removeKdigits(char* num, int k) {
	size_t len = strlen(num);
	int initial_k = k; // Store initial k for summary

	// --- Output Enhancement 1: Count digits in input ---
	printf("Input Analysis:\n");
	printf("  Original number has %zu digits.\n", len);
	printf("  You want to remove %d digits.\n\n", k);


	// If k is equal to or greater than the length, result is "0"
	if (k >= (int)len) { // Cast len to int for comparison with k
		printf("All digits (%zu) will be removed, resulting in '0'.\n", len);
		printf("\n--- Summary ---\n");
		printf("Final Result: 0\n");
		return;
	}

	char result[260]; // Max size of n_input + 1 for null terminator
	int top = -1;         // Represents the top of our "stack" (index in result)

	// Store removed digits for detailed explanation
	char removed_digits_log[260]; // Buffer to collect removed digits
	int removed_log_count = 0;

	printf("Removal Process (Step-by-step decisions):\n");
	for (size_t i = 0; i < len; i++) {
		// Null-terminate current result for printing
		result[top + 1] = '\0';
		printf("  - Processing digit '%c' from original input (current sequence: '%s'):\n", num[i], (top == -1) ? "" : result);

		// Deep Dive into Core Logic (Greedy Approach with Stack-like behavior):
		while (k > 0 && top >= 0 && result[top] > num[i]) {
			printf("    -> REMOVING '%c' (last digit in current sequence) because '%c' is smaller and will come after it. (k remaining: %d)\n", result[top], num[i], k - 1);
			removed_digits_log[removed_log_count++] = result[top]; // Track removed digit
			top--; // Pop
			k--;   // Decrement k
			// Update for printing
			result[top + 1] = '\0';
			printf("       (Sequence after removal: '%s')\n", (top == -1) ? "" : result);
		}
		top++;
		result[top] = num[i]; // Push
		printf("    -> ADDING '%c' to sequence.\n", num[i]);
	}

	// Deep Dive into Handling Remaining 'k':
	// If 'k' is still greater than 0, it means we must remove digits from the end.
	while (k > 0 && top >= 0) {
		result[top + 1] = '\0'; // Null-terminate current result for printing
		printf("  - Remaining removals needed (k=%d): Removing '%c' from the end of sequence ('%s').\n", k, result[top], result);
		removed_digits_log[removed_log_count++] = result[top]; // Track removed digit
		top--; // Pop
		k--;   // Decrement k
	}

	// Null-terminate the final result string
	result[top + 1] = '\0';

	// Handle leading zeros: Find the index of the first non-zero digit
	int first_digit_idx = 0;
	while (first_digit_idx <= top && result[first_digit_idx] == '0') {
		first_digit_idx++;
	}

	printf("\n--- Summary ---\n");
	char final_result_str[260]; // Buffer to hold the final processed result for printing

	if (first_digit_idx > top) {
		strcpy_s(final_result_str, sizeof(final_result_str), "0");
	}
	else {
		strcpy_s(final_result_str, sizeof(final_result_str), &result[first_digit_idx]);
	}

	printf("Original Number: %s\n", num);
	printf("Number of Digits to Remove: %d\n", initial_k);
	printf("Digits Identified for Removal: ");
	if (removed_log_count > 0) {
		removed_digits_log[removed_log_count] = '\0'; // Null-terminate collected digits
		printf("%s\n", removed_digits_log);
	}
	else {
		printf("None (all removals were implicit through optimal construction, or k was 0)\n");
	}
	printf("Final Smallest Number: %s\n", final_result_str);
	printf("---------------------------------------------------------\n");
}

int main() {
	char n_input[260]; // Assuming max 259 digits + null
	int k_input;

	// --- Introduction ---
	printf("=========================================================\n");
	printf("             Smallest Number Creator Program\n");
	printf("=========================================================\n");
	printf("Welcome! This program helps you find the smallest possible number\n");
	printf("by removing a specified number of digits from a larger number.\n");
	printf("Imagine you have '1432219' and you want to remove 3 digits.\n");
	printf("This program will figure out the best 3 digits to remove\n");
	printf("to make the resulting number as small as possible (in this case, '1219').\n");
	printf("=========================================================\n\n");

	// --- Logic Explanation ---
	printf("--- How This Program Works (The Logic) ---\n");
	printf("The core idea is to build the smallest possible number digit by digit.\n");
	printf("It uses a strategy similar to a 'stack' or a temporary result string:\n");
	printf("1.  It processes the digits of your large number one by one.\n");
	printf("2.  For each digit, it compares it with the last digit added to our\n");
	printf("    temporary result. If the current digit is smaller than the last one\n");
	printf("    in our result, and we still have removals 'k' available, it means\n");
	printf("    we should 'remove' that larger last digit from our result.\n");
	printf("    (e.g., if result is '4' and current digit is '2', we remove '4' and add '2').\n");
	printf("3.  This process continues until all digits are considered.\n");
	printf("4.  Finally, if we still have 'k' removals left (which happens if the remaining\n");
	printf("    digits are already in ascending order, like '12345'), we simply remove\n");
	printf("    the last 'k' digits from our temporary result.\n");
	printf("5.  Any leading zeros (e.g., '00123') are then removed before printing.\n");
	printf("This approach ensures we always try to keep smaller digits towards the left!\n");
	printf("---------------------------------------------------------\n\n");
	printf("Let's try it out!\n\n");

	// --- User Interaction and Testing ---
	while (1) { // Loop indefinitely for multiple tests, user can Ctrl+C to exit
		printf("---------------------------------------------------------\n");
		printf("Enter a large number (digits only, max 259, or type 'exit' to quit): ");
		if (fgets(n_input, sizeof(n_input), stdin) == NULL) {
			fprintf(stderr, "Error reading number.\n");
			return 1;
		}
		// Remove trailing newline character
		n_input[strcspn(n_input, "\n")] = 0;

		if (strcmp(n_input, "exit") == 0) {
			printf("Exiting program. Goodbye!\n");
			break; // Exit the loop
		}

		// Basic validation for number input
		int valid_num = 1;
		for (int i = 0; n_input[i] != '\0'; i++) {
			if (n_input[i] < '0' || n_input[i] > '9') {
				valid_num = 0;
				break;
			}
		}
		if (!valid_num || strlen(n_input) == 0) {
			printf("Invalid input. Please enter digits only.\n");
			continue; // Ask for input again
		}

		printf("Enter the number of digits to remove: ");
		if (scanf_s("%d", &k_input) != 1) { // scanf_s for integers has the same parameters
			fprintf(stderr, "Error reading number of digits to remove. Please enter an integer.\n");
			// Clear input buffer after failed scanf
			while (getchar() != '\n');
			continue; // Ask for input again
		}
		// Consume the newline character left by scanf
		while (getchar() != '\n');

		if (k_input < 0) {
			printf("Number of digits to remove cannot be negative. Please try again.\n");
			continue;
		}

		printf("\nProcessing...\n");
		removeKdigits(n_input, k_input); // Call the function to process and print
		printf("\n"); // Add an extra newline for spacing between tests
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

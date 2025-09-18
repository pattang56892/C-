// CA_findMax.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <stdio.h>
#include <limits.h>
#include <string.h> // Include string.h for strtok

// Function prototype for max()
int max(int arr[], int size);

int main() {
	int numbers[10];
	int count;
	char input[256];

	while (1) {  // Infinite loop to allow multiple inputs
		printf("\nPlease enter up to 10 integers separated by spaces (or 'exit' to quit): ");
		fgets(input, sizeof(input), stdin);

		// Check if the user wants to exit
		if (input[0] == 'e' && input[1] == 'x' && input[2] == 'i' && input[3] == 't' && (input[4] == '\n' || input[4] == '\0')) {
			break;
		}

		// Reset the count and numbers array
		count = 0;
		for (int i = 0; i < 10; i++) {
			numbers[i] = 0;
		}

		// Parse the input string using strtok_s
		char* tokenContext;
		char* token = strtok_s(input, " \n", &tokenContext);
		while (token != NULL && count < 10) {
			if (sscanf_s(token, "%d", &numbers[count]) == 1) {
				count++;
			}
			else {
				printf("Invalid input. Please enter only integers.\n");
				break;
			}
			token = strtok_s(NULL, " \n", &tokenContext);
		}

		// Check if the user entered any valid numbers
		if (count == 0) {
			printf("No valid numbers entered. Please try again.\n");
		}
		else {
			int max_num = max(numbers, count);
			printf("The maximum value among %d numbers is: %d\n", count, max_num);
		}
	}

	return 0;
}

// Function definition for max()
int max(int arr[], int size) {
	if (size <= 0) return INT_MIN; // Return minimum possible integer if no elements

	int max_value = arr[0];
	for (int i = 1; i < size; i++) {
		if (arr[i] > max_value) {
			max_value = arr[i];
		}
	}
	return max_value;
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

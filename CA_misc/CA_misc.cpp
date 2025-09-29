// CA_misc.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <stdio.h>
#include <stdlib.h>

int main() {
	int i, j, k = 0;
	char argc[100];
	char ch;

	printf("Enter characters (press Enter when done): ");

	// Read characters until newline using getchar()
	for (i = 0; i < 100; i++) {
		ch = getchar();  // No scanf warning with getchar()

		if (ch == '\n') {
			break;
		}

		argc[i] = ch;
		k++; // Increment count of characters

		// Check for duplicates against ALL previous characters
		for (j = 0; j < k - 1; j++) {
			if (argc[i] == argc[j]) {
				printf("NO\n");
				return 0;
			}
		}
	}

	// If we reach here, no duplicates found
	printf("YES\n");
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

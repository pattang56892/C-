// ConsoleApplication_UnionTest02.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <stdlib.h>

// Define the missing types locally
typedef struct edge {
    int data;
    struct edge* next;
} edge;

typedef struct Node {
    char type;
    edge* next;
} Node;

// Your functions (now they will compile)
int find_number_of_M_nodes(Node network[], Node* node) {
    int count = 0;
    for (edge* pGuard = node->next->next; pGuard != NULL; pGuard = pGuard->next) {
        // ... loop logic
        if (network[pGuard->data].type == 'M') {
            count++;
        }
    }
    return count;
}

int initialize_zero(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = 0;
    }
    return 0;
}

// Add a main function to test
int main() {
    // Test initialize_zero
    int test_array[5];
    initialize_zero(test_array, 5);

    printf("Array after initialization: ");
    for (int i = 0; i < 5; i++) {
        printf("%d ", test_array[i]);
    }
    printf("\n");

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

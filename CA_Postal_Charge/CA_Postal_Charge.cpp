// CA_Postal_Charge.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main() {
	int zone;           // Destination zone (0-4)
	double weight;      // Package weight in kg
	double baseFee;     // Base weight fee
	double additionalRate; // Additional weight rate per kg
	double totalFee;    // Total shipping fee

	// Display zone options with explanations
	cout << "=== Express Delivery Zone Options ===" << endl;
	cout << "0 - Same region (Base: 10 yuan, Additional: 3 yuan/kg)" << endl;
	cout << "1 - Zone 1: Jiangsu, Zhejiang, Shanghai, Anhui (Base: 10 yuan, Additional: 4 yuan/kg)" << endl;
	cout << "2 - Zone 2: 1500-2500km distance (Base: 15 yuan, Additional: 5 yuan/kg)" << endl;
	cout << "3 - Zone 3: Other provinces (Base: 15 yuan, Additional: 6.5 yuan/kg)" << endl;
	cout << "4 - Zone 4: Xinjiang, Tibet (Base: 15 yuan, Additional: 10 yuan/kg)" << endl;
	cout << "=====================================" << endl;
	cout << endl;

	// Input zone and weight
	cout << "Enter destination zone (0-4): ";
	cin >> zone;
	cout << "Enter package weight (kg): ";
	cin >> weight;

	// Calculate ceiling of weight (round up to nearest kg)
	int actualWeight = (int)ceil(weight);

	// Determine base fee and additional rate based on zone
	switch (zone) {
	case 0: // Same region
		baseFee = 10.0;
		additionalRate = 3.0;
		break;

	case 1: // Zone 1 (Jiangsu, Zhejiang, Shanghai, Anhui)
		baseFee = 10.0;
		additionalRate = 4.0;
		break;

	case 2: // Zone 2
		baseFee = 15.0;
		additionalRate = 5.0;
		break;

	case 3: // Zone 3
		baseFee = 15.0;
		additionalRate = 6.5;
		break;

	case 4: // Zone 4
		baseFee = 15.0;
		additionalRate = 10.0;
		break;

	default:
		cout << "Error: Invalid zone number!" << endl;
		return 1;
	}

	// Calculate total fee
	if (actualWeight <= 1) {
		// Only base weight fee applies
		totalFee = baseFee;
	}
	else {
		// Base fee + additional weight fee
		totalFee = baseFee + (actualWeight - 1) * additionalRate;
	}

	// Output result with 2 decimal places
	cout << endl;
	cout << "=== Calculation Result ===" << endl;
	cout << "Package weight: " << weight << " kg (charged as " << actualWeight << " kg)" << endl;
	cout << "Selected zone: " << zone << endl;
	cout << "Base fee: " << baseFee << " yuan" << endl;
	if (actualWeight > 1) {
		cout << "Additional weight: " << (actualWeight - 1) << " kg × " << additionalRate << " yuan/kg = "
			<< (actualWeight - 1) * additionalRate << " yuan" << endl;
	}
	cout << fixed << setprecision(2);
	cout << "Total shipping fee: " << totalFee << " yuan" << endl;

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

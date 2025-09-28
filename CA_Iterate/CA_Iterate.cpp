// CA_Iterate.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>
#include <vector>
using namespace std;

class Solution {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int i = m - 1;      // Last element in nums1's valid part
		int j = n - 1;      // Last element in nums2
		int k = m + n - 1;  // Last position in nums1

		cout << "\n=== CODE DEMONSTRATION ===" << endl;
		cout << "Starting pointers: i=" << i << ", j=" << j << ", k=" << k << endl;
		printState(nums1, nums2, i, j, k, m);

		int step = 1;

		// Main merge loop
		cout << "\nCODE: while (i >= 0 && j >= 0) {" << endl;
		while (i >= 0 && j >= 0) {
			cout << "\n--- STEP " << step++ << " ---" << endl;

			cout << "CODE: if (nums1[i] > nums2[j]) {" << endl;
			cout << "Compare: nums1[" << i << "]=" << nums1[i] << " vs nums2[" << j << "]=" << nums2[j] << endl;

			if (nums1[i] > nums2[j]) {
				cout << "Result: TRUE (" << nums1[i] << " > " << nums2[j] << ")" << endl;
				cout << "CODE: nums1[k] = nums1[i]; i--;" << endl;
				cout << "Action: Place " << nums1[i] << " at position " << k << ", move i left" << endl;
				nums1[k] = nums1[i];
				i--;
			}
			else {
				cout << "Result: FALSE (" << nums1[i] << " <= " << nums2[j] << ")" << endl;
				cout << "CODE: nums1[k] = nums2[j]; j--;" << endl;
				cout << "Action: Place " << nums2[j] << " at position " << k << ", move j left" << endl;
				nums1[k] = nums2[j];
				j--;
			}
			cout << "CODE: k--;" << endl;
			k--;

			printState(nums1, nums2, i, j, k, m);
		}
		cout << "End of main while loop (one array exhausted)" << endl;

		// Handle remaining elements from nums2
		if (j >= 0) {
			cout << "\nCODE: while (j >= 0) { // Copy remaining nums2 elements" << endl;
			while (j >= 0) {
				cout << "\n--- CLEANUP ---" << endl;
				cout << "Copy remaining nums2[" << j << "]=" << nums2[j] << " to position " << k << endl;
				nums1[k] = nums2[j];
				j--;
				k--;
				printState(nums1, nums2, i, j, k, m);
			}
			cout << "End of cleanup while loop" << endl;
		}

		cout << "\nFINAL RESULT: ";
		printArray(nums1);
		cout << " - Successfully merged!" << endl;
	}

private:
	void printState(const vector<int>& nums1, const vector<int>& nums2, int i, int j, int k, int m) {
		cout << "State: ";

		// Print nums1 with indicators
		cout << "nums1=[";
		for (int idx = 0; idx < nums1.size(); idx++) {
			cout << nums1[idx];
			if (idx < nums1.size() - 1) cout << ",";
		}
		cout << "] ";

		// Print pointer positions
		cout << "(i=" << i << ",k=" << k << ") ";

		// Print nums2 with indicator
		cout << "nums2=[";
		for (int idx = 0; idx < nums2.size(); idx++) {
			cout << nums2[idx];
			if (idx < nums2.size() - 1) cout << ",";
		}
		cout << "] (j=" << j << ")" << endl;
	}

	void printArray(const vector<int>& arr) {
		cout << "[";
		for (int i = 0; i < arr.size(); i++) {
			cout << arr[i];
			if (i < arr.size() - 1) cout << ",";
		}
		cout << "]";
	}
};

int main() {
	cout << "=== PROBLEM EXPLANATION ===" << endl;
	cout << "Question: Merge two sorted arrays in-place" << endl;
	cout << endl;
	cout << "WHAT THE QUESTION ASKS:" << endl;
	cout << "1. You have two sorted arrays: nums1 and nums2" << endl;
	cout << "2. nums1 has extra space at the end (filled with 0s)" << endl;
	cout << "3. Merge nums2 INTO nums1 (don't create new array)" << endl;
	cout << "4. Final result must be sorted" << endl;
	cout << "5. Store the result in nums1" << endl;
	cout << endl;
	cout << "EXAMPLE:" << endl;
	cout << "Input:  nums1 = [1,2,3,0,0,0], m = 3 (valid elements)" << endl;
	cout << "        nums2 = [2,5,6], n = 3" << endl;
	cout << "Output: nums1 = [1,2,2,3,5,6] (merged and sorted)" << endl;
	cout << endl;
	cout << "KEY INSIGHT: Work backwards to avoid overwriting!" << endl;
	cout << "- Start from the end where we have empty space" << endl;
	cout << "- Compare elements and place the larger one first" << endl;
	cout << "- This ensures we never overwrite data we still need" << endl;

	cout << "\n" << string(50, '=') << endl;

	Solution solution;
	vector<int> nums1 = { 1, 2, 3, 0, 0, 0 };
	vector<int> nums2 = { 2, 5, 6 };
	int m = 3, n = 3;

	cout << "DEMONSTRATING WITH: nums1=[1,2,3,0,0,0], nums2=[2,5,6]" << endl;

	solution.merge(nums1, m, nums2, n);

	cout << "\n=== SUMMARY ===" << endl;
	cout << "✓ Successfully merged nums2 into nums1" << endl;
	cout << "✓ Result is sorted in non-decreasing order" << endl;
	cout << "✓ Used in-place algorithm (no extra arrays)" << endl;
	cout << "✓ Time complexity: O(m+n), Space complexity: O(1)" << endl;

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

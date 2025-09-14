// ConsoleApplication_UnitTest03.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <cstdio>

int main()
{
    int T;
    int player1_score = 0;
    int player2_score = 0;

    // User-friendly input prompt
    std::cout << "=== RACE SIMULATOR ===" << std::endl;
    std::cout << "Enter the number of time steps to simulate: ";
    std::cin >> T;
    std::cout << std::endl;

    std::cout << "Starting race simulation..." << std::endl;
    std::cout << "Player 1 gains 3 points per step" << std::endl;
    std::cout << "Player 2 gains 9 points per step" << std::endl;
    std::cout << "Player 1 gets a 90-point bonus every 10th step when behind" << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // Fixed loop - don't modify the loop counter!
    for (int t = 0; t <= T; t++)
    {
        // Regular point gains
        player1_score += 3;
        player2_score += 9;

        // Bonus condition (fixed - no loop counter modification)
        if (t % 10 == 0 && player1_score < player2_score)
        {
            player1_score += 90;  // Bonus points only
            std::cout << "Step " << t << ": Player 1 gets bonus! (90 points)" << std::endl;
        }

        // Show progress every 25 steps
        if (t % 25 == 0)
        {
            std::cout << "Step " << t << " - Player 1: " << player1_score
                << ", Player 2: " << player2_score << std::endl;
        }
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "FINAL RESULTS:" << std::endl;
    std::cout << "Player 1 final score: " << player1_score << std::endl;
    std::cout << "Player 2 final score: " << player2_score << std::endl;
    std::cout << std::endl;

    // Clear winner announcement
    if (player1_score > player2_score)
    {
        std::cout << "*** PLAYER 1 WINS! ***" << std::endl;
        std::cout << "Victory margin: " << (player1_score - player2_score) << " points" << std::endl;
    }
    else if (player2_score > player1_score)
    {
        std::cout << "*** PLAYER 2 WINS! ***" << std::endl;
        std::cout << "Victory margin: " << (player2_score - player1_score) << " points" << std::endl;
    }
    else
    {
        std::cout << "*** IT'S A TIE! ***" << std::endl;
    }

    std::cout << std::endl;
    std::cout << "Press Enter to exit...";
    std::cin.ignore();
    std::cin.get();

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

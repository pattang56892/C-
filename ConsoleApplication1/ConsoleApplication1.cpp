// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>   // For std::string and std::getline
#include <thread>   // For sleep
#include <chrono>   // For sleep duration

int main()
{
    int input = 0;

    std::cout << "========================================" << std::endl;
    std::cout << "    DATA PROCESSING SYSTEM v1.0" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "What is the password? (hint: 12345) ";
    std::cin >> input;

    if (input == 12345)
    {
        std::cout << "\n*** ACCESS GRANTED ***" << std::endl;
        std::cout << "Welcome back, testUser#1!" << std::endl;
        std::cout << "\nThis system simulates processing large datasets." << std::endl;
        std::cout << "The 'Start Counting' command will begin processing" << std::endl;
        std::cout << "20,000 data records with real-time progress updates." << std::endl;
        std::cout << "\nPlease type: 'Start Counting' to begin processing" << std::endl;

        std::string command;
        std::cout << "\nEnter command: ";
        std::cin.ignore();  // Clear the input buffer
        std::getline(std::cin, command);  // Read entire line including spaces

        if (command == "Start Counting")  // Direct string comparison
        {
            std::cout << "\n========================================" << std::endl;
            std::cout << "       STARTING DATA PROCESSING" << std::endl;
            std::cout << "========================================" << std::endl;
            std::cout << "Task: Processing customer database records" << std::endl;
            std::cout << "Total records to process: 20,000" << std::endl;
            std::cout << "Processing method: Sequential validation" << std::endl;
            std::cout << "Updates shown every: 2,000 records" << std::endl;
            std::cout << "----------------------------------------" << std::endl;

            int line = 0;
            int totalRecords = 20000;

            // Loading simulation
            while (line < totalRecords)
            {
                // Show progress every 2000 iterations for better visibility
                if (line % 2000 == 0)
                {
                    double percentage = (double)line / totalRecords * 100;
                    std::cout << "Status: Validating record " << line << " of " << totalRecords;
                    std::cout << " (" << (int)percentage << "% complete)" << std::endl;

                    // Show what's being processed at different stages
                    if (line == 0)
                        std::cout << "  -> Initializing database connection..." << std::endl;
                    else if (line == 4000)
                        std::cout << "  -> Checking data integrity..." << std::endl;
                    else if (line == 8000)
                        std::cout << "  -> Validating customer information..." << std::endl;
                    else if (line == 12000)
                        std::cout << "  -> Processing payment records..." << std::endl;
                    else if (line == 16000)
                        std::cout << "  -> Generating reports..." << std::endl;
                }
                line++;

                // Add small delay to make it visible and realistic
                if (line % 5000 == 0)
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(200));
                }
            }

            std::cout << "========================================" << std::endl;
            if (line >= totalRecords)
            {
                std::cout << "*** PROCESSING COMPLETED SUCCESSFULLY ***" << std::endl;
                std::cout << "\nSUMMARY:" << std::endl;
                std::cout << "- Total records processed: " << totalRecords << std::endl;
                std::cout << "- Validation errors found: 0" << std::endl;
                std::cout << "- Data integrity: 100% verified" << std::endl;
                std::cout << "- Processing time: ~4 seconds" << std::endl;
                std::cout << "- Status: All customer data validated successfully!" << std::endl;
            }
            else
            {
                std::cout << "*** PROCESSING FAILED ***" << std::endl;
                std::cout << "Only " << line << " of " << totalRecords << " records were processed." << std::endl;
            }
        }
        else
        {
            std::cout << "\n*** COMMAND NOT RECOGNIZED ***" << std::endl;
            std::cout << "You entered: '" << command << "'" << std::endl;
            std::cout << "Valid commands:" << std::endl;
            std::cout << "  - 'Start Counting' (begins data processing)" << std::endl;
            std::cout << "Note: Commands are case-sensitive" << std::endl;
        }
    }
    else
    {
        std::cout << "\n*** ACCESS DENIED ***" << std::endl;
        std::cout << "Incorrect password entered: " << input << std::endl;
        std::cout << "Hint: The password is a 5-digit number starting with '1'" << std::endl;
        std::cout << "Please contact your system administrator for assistance." << std::endl;
    }

    std::cout << "\n========================================" << std::endl;
    std::cout << "Press Enter to close the application...";
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

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <chrono>
#include <thread>

int displayChoices();
void createFile();
void modifyFile();
void listFiles();

int main() {
    int choice;
    do {
        choice = displayChoices();
        switch (choice) {
            case 1:
                createFile();
                break;
            case 2:
                modifyFile();
                break;
            case 3:
                listFiles();
                break;
            case 4:
                std::cout << "Exiting program...\n";
                std::this_thread::sleep_for(std::chrono::milliseconds(1000));
                break;
            default:
                std::cerr << "Invalid option!\n";
        }
    } while (choice != 4);
    return 0;
}

// Displays the menu and gets the user's choice
int displayChoices() {
    int input{};
    do {
        std::cout << "*******************" << "\n";
        std::cout << "*      NOTES      *" << "\n";
        std::cout << "*******************" << "\n";
        std::cout << "1. To write a note" << "\n";
        std::cout << "2. To modify a note" << "\n";
        std::cout << "3. To read the existing notes" << "\n";
        std::cout << "4. Exit" << "\n\n";
        std::cout << "Choose the option: ";
        std::cin >> input;

        // Handle invalid input
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (input < 1 || input > 4) {
            std::cerr << "Error: Invalid Option!\n\n";
        }
    } while (input < 1 || input > 4);
    return input;
}

// Creates a new text file and writes user input into it
void createFile() {
    std::cout << "Give the name to the note: ";
    std::string textName;
    std::getline(std::cin, textName);

    std::ofstream myFile(textName + ".txt", std::ios::out | std::ios::trunc);
    if (!myFile) {
        std::cerr << "Error: Could not create the file!\n";
        return;
    }

    std::cout << "Write your text (type 'END' on a new line to finish):\n";
    std::string line;
    while (true) {
        std::getline(std::cin, line);
        if (line == "END" || line == "end") break;
        myFile << line << "\n";
    }

    myFile.close();
    std::cout << "Note saved as " << textName << ".txt\n\n";
}

// Appends new text to an existing file
void modifyFile() {
    std::cout << "Enter the name of the note to rewrite: ";
    std::string fileName;
    std::cin >> fileName;

    std::ofstream rewriteFile(fileName + ".txt", std::ios::app);
    if (rewriteFile.is_open()) {
        std::cout << "Write your new text (type 'END' on a new line to finish):\n";
        std::string line;
        std::cin.ignore();
        while (true) {
            std::getline(std::cin, line);
            if (line == "END" || line == "end") break;
            rewriteFile << line << "\n";
        }
        rewriteFile.close();
    } else {
        std::cerr << "Error: Cannot open the file for rewriting!\n";
    }
    std::cout << "\n";
}

// Lists all .txt files in the current directory
void listFiles() {
    std::cout << "Listing .txt files in the current directory:\n";
    for (const auto& entry : std::filesystem::directory_iterator(".")) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            std::cout << "- " << entry.path().filename().string() << "\n";
        }
    }
    std::cout << "\n";
}


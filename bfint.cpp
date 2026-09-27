// ---FOR THE INPUT TO THE BF PROGRAM---
// If you want to input the backslash character (\) you must enter two like this: \\
// For newlines, instead type backslash + n like this: \n

#include <iostream>
#include <string>
#include <vector>

std::string rmNonBfChars(std::string dirtyString);

int main() {
    // Initializing and getting variables START

    // For these const variables, add one to get the true size since they start at index 0
    // So if you want 1000 cells, type 999 below
    const int cellNum = 999; // Number of cells on the tape
    const int cellSize = 255; // How many values each cell has before overflowing; standard is 8 bits of info, or 256 potential values
    std::string programInput;

    std::vector<int> cellTape(cellNum, 0);
    std::string program = "";
    char instruction = ' ';

    std::cout << "Input some bf programming text" << std::endl;
    std::getline(std::cin, program);
    program = rmNonBfChars(program);

    std::cout << "Now give the console input the program takes (If any)" << std::endl; // Go to top of program to see how to input newlines
    std::getline(std::cin, programInput);
    // Initializing and getting variables END
    // Clean up the program so it only contains the 8 bf characters
    

    // Run the program
    for (int i = 0; i < program.size(); i++) {
        // Set the current instruction
        instruction = program.at(i);

    }
    return 0;
}

std::string rmNonBfChars(std::string dirtyString) {
    std::string cleanString = "";
    char currentChar;
    for (int i = 0; i < dirtyString.size(); i++) {
        currentChar = dirtyString.at(i);
        // There is absolutely no way this is the best way to check for if a char is in a string but it works
        if (currentChar == '<' || currentChar == '>' || currentChar == ',' || currentChar == '.' || currentChar == '[' || currentChar == ']' || currentChar == '-' || currentChar == '+') {
            cleanString.push_back(currentChar);
        }
    }
    return cleanString;
}
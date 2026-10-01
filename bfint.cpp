// ---FOR THE INPUT TO THE BF PROGRAM---
// If you want to input the backslash character (\) you must enter two like this: \\
// For newlines, instead type backslash + n like this: \n

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// Initialize constant variables
// For these const variables, add one to get the true size since they start at index 0
// So if you want 1000 cells, type 999 below
const int cellNum = 999; // Number of cells on the tape
const int cellSize = 255; // How many values each cell has before overflowing; standard is 8 bits of info, or 256 potential values. Bad things can happen if you make this number bigger than 255

// Declare functions
std::string rmNonBfChars(std::string dirtyString);
bool validBrackets(std::string program);
std::string cleanProgInput(std::string dirtyInput);
char fetchNextInput(std::string &progInput);
void runBfCode(std::string prog, std::string progInp);
// Functions for executing bf instructions
void incrementCell(std::vector<int> &cellStrip, int cellPointer);
void decreaseCell(std::vector<int> &cellStrip, int cellPointer);
void moveRight(int &cellPointer);
void moveLeft(int &cellPointer);
void storeInput(std::vector<int> &cellStrip, int cellPointer);
void printCell(std::vector<int> cellStrip, int cellPointer);


int main() {
    // Initializing and getting variables START ~~~~~~~~~~
    std::string program = "";
    std::string programInput = "";

    std::cout << "Input some bf programming text" << std::endl;
    std::getline(std::cin, program);
    // Clean up the program so it only contains the 8 bf characters
    program = rmNonBfChars(program);
    // Then check if the brackets make sense. Check readme for more info
    if (!validBrackets(program)) {
        std::cout << "Those brackets didn't make sense. Look at the ReadMe.md file for more information." << std::endl;
        return 0;
    }
    std::cout << "Now give the console input the program takes (If any)" << std::endl; // Go to top of this file to see how to input newlines
    std::getline(std::cin, programInput);
    // Initializing and getting variables END ~~~~~~~~~~~~
    // Convert the user newlines into actual newline characters
    programInput = cleanProgInput(programInput);

    // Run the program
    
    return 0;
}
// Initialize functions
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

bool validBrackets(std::string program) {
    int bracketVal = 0;
    for (int i = 0; i < program.size(); i++) {
        char currentChar = program.at(i);
        if (currentChar == '[') {
            bracketVal++;
        }
        else if (currentChar == ']') {
            bracketVal--;
        }
        
        // Check if bracketVal is less than 0. If it is less than 0, it doesn't make sense
        if (bracketVal < 0) {
            return false;
        }
    }
    if (bracketVal != 0) {
        return false;
    }
    return true;
}

std::string cleanProgInput(std::string dirtyInput) {
    std::string cleanInput = "";
    char currentChar = ' ';
    char nextChar = ' ';
    for (int i = 0; i < dirtyInput.size(); i++) {
        currentChar = dirtyInput.at(i);
        // Basically I am safely seeing if this is the last character in the string. 
        // If it is, make the nextChar variable a space (or any character other than \ or n) which will make it return the right string back
        if (i + 1 >= dirtyInput.size()) {
            nextChar = ' ';
        }
        // If there IS a next character then set it as the next character
        else {
            nextChar = dirtyInput.at(i + 1);
        }

        // This next bit is to deal with backslashes and newlines. 

        // If current character isn't a backslash, just add it to the clean program input
        if (currentChar != '\\') {
            cleanInput.push_back(currentChar);
        }
        // If the current character is a backslash AND the next character is n, add a newline character to the clean program input and increment i because it doesn't need to check the next char
        else if (currentChar == '\\' && nextChar == 'n') {
            cleanInput.push_back('\n');
            ++i;
        }
        // Similar thing with the backslash character
        else if (currentChar == '\\' && nextChar == '\\') {
            cleanInput.push_back('\\');
            ++i;
        }
        // The only way this block is reached is if the current character is \ and the next character isn't \ or n
        // I have decided that when this happens (Which the user shouldn't be doing) just add the backslash as given
        else {
            cleanInput.push_back('\\');
        }
    }
    return cleanInput;
}

char fetchNextInput(std::string &progInput) {
    // If there is nothing left in the program input, return ascii value 0
    if (progInput.empty()) {
        return '\0';
    }
    char charReturn = progInput.at(0);
    progInput.erase(0);
    return charReturn;
}

void runBfCode(std::string prog, std::string progInp) {
    std::vector<int> cellTape(cellNum, 0);
    int currentPosition = 0; // Current position on the tape of cells
    // Double check the program brackets make sense
    if (!validBrackets(prog)) {
        std::cout << "Fatal error; Invalid brackets. This message shouldn't be appearing, please report this bug to Jorttle." << std::endl;
        std::exit(0);
    }

}

// Functions for executing bf instructions

void incrementCell(std::vector<int> &cellStrip, int cellPointer) {
    cellStrip[cellPointer]++;
    if (cellStrip.at(cellPointer) > cellSize) {
        cellStrip[cellPointer] = 0;
    }
}

void decreaseCell(std::vector<int> &cellStrip, int cellPointer) {
    cellStrip[cellPointer]--;
    if (cellStrip.at(cellPointer) < 0) {
        cellStrip[cellPointer] = cellSize;
    }
}

void moveRight(int &cellPointer) {
    cellPointer++;
    if (cellPointer > cellNum) {
        cellPointer = 0;
    }
}

void moveLeft(int &cellPointer) {
    cellPointer--;
    if (cellPointer < 0) {
        cellPointer = cellNum;
    }
}

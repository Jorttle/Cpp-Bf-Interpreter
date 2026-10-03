// ---FOR THE INPUT TO THE BF PROGRAM---
// If you want to input the backslash character (\) you must enter two like this: \\
// For newlines, instead type backslash + n like this: \n

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <algorithm>

// Initialize constant variables
// For these const variables, add one to get the true size since they start at index 0
// So if you want 1000 cells, type 999 below
const int cellNum = 999; // Number of cells on the tape
const int cellSize = 255;   /* How many values each cell has before overflowing; standard is 8 bits of info, or 256 potential values.
                            Bad things can happen if you make this number bigger than 255 */

// Declare functions
bool isBfChar(char c);
std::string rmNonBfChars(std::string dirtyString);  /* Obviously removes non-BF characters, but not always. If the user's program has \i, \b, or \a, 
                                                    it will turn it into their respective letters (i, b, or a).
                                                    This is because the I want the user to be able to print out the current cell tape in integer, binary, or ascii 
                                                    If the user puts multiple backslashes in a row before i, b, or a, it will still include the i, b, or a. 
                                                    Example: "\\i" will add "I"
                                                    Case does not matter, so \i and \I both add "I" to the output
                                                    */
bool validBrackets(std::string program);
std::string cleanProgInput(std::string dirtyInput);
char fetchNextInput(std::string &progInput);
std::string runBfCode(std::string prog, std::string progInp);
std::string retFormattedTape(std::vector<int> cellStrip, char formatType, int cellPointer, std::string separator = " ", std::string emphasizer = "***"); // Format type must be 'A', 'B', or 'I'
std::string toBinary(int n);
// Functions for executing bf instructions
void incrementCell(std::vector<int> &cellStrip, int cellPointer);
void decreaseCell(std::vector<int> &cellStrip, int cellPointer);
void moveRight(int &cellPointer);
void moveLeft(int &cellPointer);
void storeInput(std::vector<int> &cellStrip, int cellPointer);
void printCell(std::vector<int> cellStrip, int cellPointer);

int main() {
    // TEMPORARY MESSAGE WARNING THAT PROJECT ISN'T COMPLETE
    std::cout << "This project is not yet finished!" << std::endl;
    // TESTING -----------------------------------------
    // std::vector<int> v = {40, 41, 45, 50, 55};

    // std::cout << retFormattedTape(v, 'B', 3) << std::endl;
    // END TESTING -------------------------------------
    return 0;
    // END TEMP MESSAGE

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
    std::cout << runBfCode(program, programInput) << std::endl;
    return 0;
}
// Initialize functions
bool isBfChar(char c) {
    if (c == '<' || c == '>' || c == ',' || c == '.' || c == '[' || c == ']' || c == '-' || c == '+') {
        return true;
    }
    return false;
}

std::string rmNonBfChars(std::string dirtyString) {
    // I copied some code from cleanProgInput()
    std::string cleanString = "";
    char currentChar = ' ';
    char nextChar = ' ';
    // Loop through every character in the given string
    for (int i = 0; i < dirtyString.size(); i++) {
        currentChar = dirtyString.at(i);
        if (i + 1 >= dirtyString.size()) {nextChar = ' ';} // If we are at the last character, then set the "nextChar" variable to a space to not break anything
        else {nextChar = dirtyString.at(i + 1);}
        // next part
        // If current character isn't a backslash, check if it is a bf character TODO
        if (isBfChar(currentChar)) {
            cleanString.push_back(currentChar);
        }
        else if (currentChar != '\\') {} // Program shouldn't do anything if current char isn't a bf char or backslash
        // Convert \i \b and \a. ++i is used because the program doesn't have to read the next character. Even if it did, it wouldn't make a difference.
        else if (currentChar == '\\' && (nextChar == 'i' || nextChar == 'I')) {
            cleanString.push_back('I');
            ++i;
        }
        else if (currentChar == '\\' && (nextChar == 'b' || nextChar == 'B')) {
            cleanString.push_back('B');
            ++i;
        }
        else if (currentChar == '\\' && (nextChar == 'a' || nextChar == 'A')) {
            cleanString.push_back('A');
            ++i;
        }
        // If none of the above conditions are true that means that the current character is backslash and the next character is unexpected.
        // Example: \1, \q, \[
        // In this case we don't do anything
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

std::string runBfCode(std::string prog, std::string progInp) {
    std::vector<int> cellTape(cellNum, 0);
    int currentPosition = 0; // Current position on the tape of cells
    // Double check the program brackets make sense
    if (!validBrackets(prog)) {
        std::cout << "Fatal error; Invalid brackets. This message shouldn't be appearing, please report this bug to Jorttle with code 3nly5hb888" << std::endl;
        std::exit(1);
    }
    // TODO: add bf code running functionality
    return "";
}

std::string retFormattedTape(std::vector<int> cellStrip, char formatType, int cellPointer, std::string separator, std::string emphasizer) { 
                            // |Cell Strip|             |I, A, or B|     |Pos on cell tape| |WhatSeparatesCellsOnPrint| | what to put around cell pointer
    std::string retStr = 
    "\n@@@@@@@@@@@@@@@@@@@"
    "\n@ Debug Interrupt @"
    "\n@@@@@@@@@@@@@@@@@@@"
    "\nBegin Printing Cell Tape:"
    "\n";
    if (formatType != 'A' && formatType != 'B' && formatType != 'I') {
        std::cout << "\nSomething has gone horribly wrong. Please report this bug to Jorttle with code 1lgzezvg0a" << std::endl;
        exit(1);
    }
    // I don't like how much copying and pasting I had to do, but otherwise I would have to constantly see if formatType == 'A' or 'B' or 'I'
    // Return Ascii
    if (formatType == 'A') {
        for (int i = 0; i < cellStrip.size(); ++i) {
            int currentVal = cellStrip.at(i);
            if (i + 1 == cellStrip.size()) {separator = "";} // If this is the last loop in the for loop, no need for a final separator
            if (cellPointer == i) {retStr += emphasizer + static_cast<char>(currentVal) + emphasizer + separator;} // If we are at the cell pointer value on the tape,
            else {retStr += static_cast<char>(currentVal) + separator;}                                            // then put emphasizers around it
        }
    }
    // Return binary
    else if (formatType == 'B') {
        for (int i = 0; i < cellStrip.size(); ++i) {
            int currentVal = cellStrip.at(i);
            if (i + 1 == cellStrip.size()) {separator = "";} // If this is the last loop in the for loop, no need for a final separator
            if (cellPointer == i) {retStr += emphasizer + toBinary(currentVal) + emphasizer + separator;} // If we are at the cell pointer value on the tape,
            else {retStr += toBinary(currentVal) + separator;}                                            // then put emphasizers around it
        }
    }
    // Return int
    else if (formatType == 'I') {
        for (int i = 0; i < cellStrip.size(); ++i) {
            int currentVal = cellStrip.at(i);
            if (i + 1 == cellStrip.size()) {separator = "";} // If this is the last loop in the for loop, no need for a final separator
            if (cellPointer == i) {retStr += emphasizer + std::to_string(currentVal) + emphasizer + separator;} // If we are at the cell pointer value on the tape,
            else {retStr += std::to_string(currentVal) + separator;}                                            // then put emphasizers around it
        }
    }
    retStr +=
    "\n@@@@@@@@@@@@@"
    "\n@ End Debug @"
    "\n@@@@@@@@@@@@@"
    "\n";
    return retStr;
}

std::string toBinary(int n) {
    if (n == 0) return "0";

    std::string s;
    while (n > 0) {
        s += '0' + (n & 1);
        n >>= 1;
    }
    std::reverse(s.begin(), s.end());
    return s;
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

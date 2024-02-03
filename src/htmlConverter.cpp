#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "../inc/htmlConverter.h"
using namespace std;

//CLion recommended making the parameters const and references, working fine,
//researched it a bit, somewhat understand why, more research needed
void demoOpenCloseStreams(const string& inputFile, const string& outputFile) {
    cout << "Files Open" << endl;

    // Declare stream objects
    ifstream inStream;
    ofstream outStream;

    // Connect files to stream objects
    inStream.open(inputFile);
    outStream.open(outputFile);

    string line;
    string stringConversion;  // Assuming you have a string to store the entire content

    // ... Read the entire content into stringConversion ...

    // Replace "<" with "&lt;" and ">" with "&gt;" in each line
    while (getline(inStream, line)) {
        stringConversion += line + "\n";
    }

    // Replace "<" with "&lt;" and ">" with "&gt;" in each line
    for (int i = 0; i < stringConversion.length(); ++i) {
        if (stringConversion[i] == '<') {
            stringConversion.replace(i, 1, "&lt;");
            // add 3 to i to go over what we just replaced
            i += 3;
        } else if (stringConversion[i] == '>') {
            stringConversion.replace(i, 1, "&gt;");
            i += 3;
        }
    }

    // Insert "<PRE>\n" at the beginning
    stringConversion.insert(0, "<PRE>\n");

    // Append "\n</PRE>" at the end
    stringConversion += "\n</PRE>";

    // Write the modified content to the output file
    outStream << stringConversion << endl;

    inStream.close();
    outStream.close();
}

//https://stackoverflow.com/questions/24702677/regular-expression-to-match-a-valid-absolute-windows-directory-containing-spaces
//https://regex101.com/
bool isValidInput(const string& input) {
    // Define the regex pattern
    regex pattern(R"(^[a-zA-Z]:\\.*\.(cpp|html)$)");
    // Test the input against the regex pattern
    return regex_match(input, pattern);
}
// Function to get user input for file name
string getFileName() {
    string fileName;
    //do while loop continues to execute until a proper name is enter or the person quits
    do {
        cout << "What .cpp file would you like to turn into an html file? ";
        getline(cin, fileName);
        if (fileName == "quit") {
            cout << "Exiting the program.\n";
            exit(0);
        }
        if (!isValidInput(fileName)) {
            cout << "Invalid file name. Please enter a valid .cpp or .html file path.\n";
        }
    } while (!isValidInput(fileName));
    return fileName;
}
//function to save file
string getSaveLocation() {
    string saveLocation;
    do {
        cout << "Where would you like to save the html file? ";
        getline(cin, saveLocation);
        if (saveLocation == "quit") {
            cout << "Exiting the program.\n";
            exit(0);
        }
        if (!isValidInput(saveLocation)) {
            cout << "Invalid save location. Please enter a valid directory path.\n";
        }
    } while (!isValidInput(saveLocation));
    return saveLocation;
}

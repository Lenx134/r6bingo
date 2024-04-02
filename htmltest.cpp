#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream> // to enable the use of string streams
#include "fixgets.h" // To read the txt file

using namespace std;

int countLines(void); // Function prototype

int main() {
    // Get the number of lines in the file
    int lineCount = countLines();

    // Open file
    FILE *data_file;
    if ((data_file = fopen("r6bingo.txt","r")) == NULL) {
        cout << "Error reading file." << endl;
        return 1;
    }

    // Create an array to hold bingo entries
    char charHolder[25];
    string bingoSquare[lineCount];
    for (int i = 0; i < lineCount; i++) {
        fixgets(charHolder, 25, data_file);
        bingoSquare[i] = (string) charHolder;
    }
	
	fclose(data_file);
	
	//creates the array that will become the bingo square
	string randomSquare[25];
	//a seperate array that will be used to make sure entries are not repeated
	int numbersUsed[25];
	int randomNumber;
	int counter = 0;
	bool isUnique = false;
	
	for (int i = 0; i < 25; i++) {
		do {
			randomNumber = rand() % lineCount;
			for (int b = 0; b < 25; b++)
				if (numbersUsed[b] == randomNumber) {
					isUnique = false;
					break;
				}
				else
					isUnique = true;
		} while (isUnique == false);
		
		numbersUsed[i] = randomNumber;
	}
	
	for (int i = 0; i < 25; i++) {
		randomSquare[i] = bingoSquare[numbersUsed[i]];
	}
	
	randomSquare[12] = "Womp Womp"; //sets the center square to a free space

    // Create HTML string for the bingo card
	string html = "<!DOCTYPE html>\n";
	html += "<html>\n";
	html += "<head>\n";
	html += "<title>Rainbow 6 Bingo Card</title>\n";
	html += "<style>\n";
	html += "table {\n";
	html += "    border-collapse: collapse;\n";
	html += "}\n";
	html += "td {\n";
	html += "    border: 1px solid black;\n"; // Add border style here
	html += "    padding: 8px;\n"; // Add padding for better appearance
	html += "}\n";
	html += "</style>\n";
	html += "</head>\n";
	html += "<body>\n";
	html += "<table>\n";

	stringstream ss; //a stream is like a dynamic variable that changes over time

	// Generate HTML for the bingo card
	counter = 0; //reusing this from earlier
	for (int b = 0; b < 5; ++b) {
		html += "<tr>\n";
		for (int i = 0; i < 5; ++i) {
			ss.str(""); //the ss is cleared then set to the value of counter, this keeps the htm clean
			ss.clear();
			ss << counter;
			html += "<td><input type=\"checkbox\" id=\"checkbox" + ss.str() + "\" name=\"checkbox" + ss.str() + "\"><label for=\"checkbox" + ss.str() + "\">" + randomSquare[counter] + "</label></td>\n";
			++counter;
		}
		html += "</tr>\n";
	}

	html += "</table>\n";
	html += "</body>\n";
	html += "</html>\n";

    // Write HTML string to file
    ofstream htmlFile("bingo_card.html");
    if (htmlFile.is_open()) {
        htmlFile << html;
        cout << "Bingo card HTML file generated successfully." << endl;
    } else {
        cerr << "Unable to create HTML file." << endl;
        return 1;
    }
	
	htmlFile.close();
	
	system("start bingo_card.html");
	
    return 0;
}

// Function to count the number of lines in the text file
int countLines() {
    FILE *data_file;
    if ((data_file = fopen("r6bingo.txt","r")) == NULL) {
        cout << "Error reading file." << endl;
        exit(1);
    }

    int lineCount = 0;
    char buffer[26]; // Buffer to read lines
    while (fgets(buffer, sizeof(buffer), data_file) != NULL) {
        lineCount++;
    }

    fclose(data_file);
    return lineCount;
}
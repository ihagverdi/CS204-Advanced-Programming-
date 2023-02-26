#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

/*
Written by Hagverdi Ibrahimli for CS204 COURSE IN 09/03/2022
ihagverdi -> SU username
30014 -> SU id
*/

struct cell { // constructing cell struct for each matrix entity
	char letter;
	char color;
};

// Total of 11 functions, bodies below int main();
void intro(int , int);
void readFile(ifstream&, int&, string&);
void setMatrix(vector<vector<cell>> &);
void printMatrix(vector<vector<cell>>const);
int lengthCheck(string , string);
int lowerCheck(string);
int dupCheck(string);
int wordCheck(vector <string> , string);
int greenCheck(vector<vector<cell>> , int , string);
int totalChecks(vector<vector<cell>> , vector <string> , string , string , int);
void writeMatrix(vector<vector<cell>> &, string , string , int , int );

int main() {
	ifstream infile;
	string word, guess; // Correct word and the user's guess as strings
	int attempts, cols;
	readFile(infile, attempts, word); // Reading user files -> getting # of attempts and correct word for SWordle
	cols = word.length(); // # of Columns in the matrix is rep. as length of correct word

	vector<vector<cell>> mat(attempts, vector<cell>(cols)); // Creating SWordle matrix <-> rows = attempts, cols = word length

	setMatrix(mat); // Initializing all matrix entities to "-"
	
	vector <string> prevWords; // vector to store prev. tried words <-> for input check

	intro(attempts, cols); // Welcoming & making into. to the SWordle!

	int currAttempt = 0; // attempt counter
	bool loseCheck = true; // win check
	while (currAttempt < attempts && loseCheck) {
		cout << "What's your guess? ";
		cin >> guess;
		if(totalChecks(mat, prevWords,  word,  guess, currAttempt)) { // Function containing all input check functions
			writeMatrix(mat, word, guess, cols, currAttempt); // filling matrix with corresponding correctness color
			printMatrix(mat); // printing in a template form
			prevWords.push_back(guess); 
			currAttempt++;

			if(guess == word) { // Winning if -> true
				cout << "You win!\n";
				loseCheck = false;
			}
		}
	}
	if(guess != word) { 
		cout << "You lose!\n";
	}
	return 0;
}


void readFile(ifstream &infile, int & numAttempts, string & word) { // Opening the file until process successful
																	// & reading into variables.
	string filename, line; 
	cout << "Please enter the file name: ";
	cin >> filename;
	infile.open(filename.c_str());

	while(infile.fail()) {
		cout << "Couldn't find the file!" << endl;
		cout << "Please enter the file name: ";
		cin >> filename;
		infile.open(filename.c_str());
	}

	while(!infile.eof()) {
		infile >> numAttempts >> word;
	}

}

void intro(int attempts, int wordLength) {
	cout << "Welcome to SWordle!" << endl;
	cout << "The word that you will guess has " << wordLength << " letters and you have " << attempts << " attempts." << endl;
}

void setMatrix(vector<vector<cell>> &mat) { // Inititalizing matrix cells to all entities = "-"
	for(int i = 0; i < mat.size(); i++) {
		for(int c = 0; c < mat[0].size(); c++) {
			mat[i][c].color = '-';
			mat[i][c].letter = '-';		
		}
	}
}

void printMatrix(vector<vector<cell>> const mat) { // Printing in || cell || form
	for(int i = 0; i < mat.size(); i++) {
		cout << "|";
		for(int c = 0; c < mat[0].size(); c++) {
			cout << "| " << mat[i][c].letter << " , "<< mat[i][c].color << " |";
		}
		cout << "|" << endl;
	}
}

int lengthCheck(string word, string guess) { // check if userGuess length equal to that of correct Word 
	if(guess.length() != word.length()) {
		return 0;
	}
	return 1;
}

int lowerCheck(string guess) { // Check if non-alphabetical characters are used in userGuess
	for(int a = 0; a < guess.length(); a++) {
		if(guess[a] < 'a' || guess[a] > 'z') {
			return 0;
		}
	}
	return 1;
}

int dupCheck(string guess) { // Check for instance of a duplicate character in userGuess
	int length =  guess.length();
	for(int a = 0; a < length-1; a++) {
		for(int b = a+1; b < length; b++) {
			if(guess[a] == guess[b]) {
				return 0;
			}
		}
}
	return 1;
}

int wordCheck(vector <string> prevWords, string guess) { // Check if the userGuess is previously used 
	for(int o = 0; o < prevWords.size(); o++) {
		if(prevWords[o] == guess) {
			return 0;
		}
	}
	return 1;
}

int greenCheck(vector<vector<cell>> mat, int currAttempt, string guess) { // Check if prev letter in the matrix with .color = green
																		// has the same letter for the current try
																		// ! No check for the first attempt since no word in prev position.
	int size = guess.length();
	if(currAttempt != 0) {
		for(int a = 0; a < size; a++) {
			if( mat[currAttempt-1][a].color == 'G') {
				if( guess[a] != mat[currAttempt-1][a].letter ) {
					return 0;
				}
			}
		}
	}
	return 1;
}



int totalChecks(vector<vector<cell>> mat, vector <string> prevWords, string word, string guess, int currAttempt) {
	if(lengthCheck(word,guess)) { // Combining all checks together with corresponding else statements 
		if(lowerCheck(guess)) {
			if(dupCheck(guess)) {
				if(wordCheck(prevWords,guess)) {
					if(greenCheck(mat,currAttempt,guess)) {
						return 1;
					}
					else {
						cout << "You did not use the green letter in your word!\n";
						return 0;
					}
				}
				else {
					cout << "You've already tried this word!\n";
					return 0;
				}
			}
			else {
				cout << "Your input has a duplicate letter!\n";
				return 0;
			}
		}
		else {
			cout << "Your input has illegal letters!\n";
			return 0;
		}
	}
	else {
		if(guess.length() > word.length()) {
			cout << "The Word is too long!\n";
			return 0;
		}		
		else {
			cout << "The Word is too short!\n";
			return 0;
		}	
	}

}

void writeMatrix(vector<vector<cell>> &mat, string word, string guess, int cols, int currAttempt) {
	for(int a = 0; a < cols; a++) { // input checks are successful -> fill the matrix cell with userGuess chars and corr. colors
		mat[currAttempt][a].letter = guess[a];
		if(guess[a] == word[a]) {
			mat[currAttempt][a].color = 'G';
		}
		else if(word.find(guess[a]) != string::npos) {
			mat[currAttempt][a].color = 'Y';
		}
		else {
			mat[currAttempt][a].color = 'B';
		}
	}
}

/* Written by: (Name, SU_name, SU_id)
Hagverdi Ibrahimli
ihagverdi
30014
*/

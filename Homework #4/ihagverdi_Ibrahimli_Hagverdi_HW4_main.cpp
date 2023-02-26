#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "ihagverdi_Ibrahimli_Hagverdi_HW4.h";
using namespace std;

/*
Written by Hagverdi Ibrahimli (ID 30014) in 9/4/22 for Advanced Programming Course (CS204) of Sabanci University.
Program is used to detect whether (if any) there are unclosed and/or wrongly balanced {}, (), and []
with using an stack object.

*/
void openFile(fstream & infile, string &fileName);
void processFile(fstream &infile, DynStack &stack);
bool processStack(istringstream &line, DynStack &stack, int lineNum);
void End(DynStack& stack);

int main() {
	fstream infile;
	string fileName;
	openFile(infile,fileName);
	DynStack stack;
	processFile(infile, stack);
	return 0;
}
/*
This function prompts user to enter a file name until successfully opened.
*/
void openFile(fstream & infile, string &fileName) {
	do {
		cout << "Please enter the file name: ";
		cin >> fileName;
		infile.open(fileName.c_str());
		if(infile.fail()) {
			cout << "File not found." << endl;
		}
	} while(infile.fail());
}

/*
This function procces the file to search for any wrongly balanced 
openings of the mentioned structures.
*/
void processFile(fstream & infile, DynStack & stack) {
	int lineNum = 1;
	string line;
	bool noError = true; // checks whether an error inside processStack function is found.
	while(noError && getline(infile,line)){
		istringstream ss(line);
		noError = processStack(ss, stack, lineNum);
		lineNum ++;
	}
	if(noError) { // checks whether faced an error inside the processStack func.
		End(stack); // gives info. about the last status of input file.
	}
}

bool processStack(istringstream &line, DynStack & stack, int lineNum) {
	char symbol;
	char openSym;
	int openNum;
	bool status = true; // return status after each operation.

	while(line >> symbol) {
		if ( symbol == '{' || symbol == '[' || symbol == '(' ) { // if the token is an opening
			cout << "Found the opening symbol " << symbol << " at line " << lineNum;
			cout << endl;
			stack.push(symbol,lineNum);
		}
		else if (symbol == '}' || symbol == ']' || symbol == ')') { // if the token is a closing
			if(stack.isEmpty()) { // if we have no opening left in stack we can not have a closing.
				cout << "ERROR!!! Found the closing symbol " << symbol <<
			            " but there are no unclosed opening symbols!";
				cout << endl;
				status = false; 
			}
			else {
				stack.pop(openSym,openNum); // extract the top element from stack
				if(symbol == '}') { // check current symbol
					if(openSym == '{') { // match it to the opening
						cout << "Found the closing symbol " << symbol << " at line " << lineNum << " which closes"
						<< " the opening symbol " << openSym << " at line " << openNum << endl;
					}
					else {
						cout << "ERROR!!! Found the closing symbol " << symbol <<
						" at line " << lineNum << " but the last unclosed opening symbol is " << openSym
						<< " at line " << openNum;
						cout << endl;
						status = false;
					}
				}
				else if (symbol == ']') {
					if(openSym == '[') {
						cout << "Found the closing symbol " << symbol << " at line " << lineNum << " which closes"
						<< " the opening symbol " << openSym << " at line " << openNum << endl;
					}
					else {
						cout << "ERROR!!! Found the closing symbol " << symbol <<
						"at line " << lineNum << " but the last unclosed opening symbol is " << openSym
						<< " at line " << openNum;
						cout << endl;
						status = false;
					}
				}
				else if (symbol == ')') {
					if(openSym == '(') {
						cout << "Found the closing symbol " << symbol << " at line " << lineNum << " which closes"
						<< " the opening symbol " << openSym << " at line " << openNum << endl;
					}
					else {
						cout << "ERROR!!! Found the closing symbol " << symbol <<
						"at line " << lineNum << " but the last unclosed opening symbol is " << openSym
						<< " at line " << openNum;
						cout << endl;
						status = false;
					}
				}
			}
		}

	}
	return status;
}
/*
Function checks and gives info. about the last status of file reading process.
*/
void End(DynStack& stack) {
	int lineNum;
	char openSym;
	if(stack.isEmpty()) { // if faced no error inside processStack and finally stack obj. is empty -> Correct.
		cout << "File processed successfully. No errors were found.";
		cout << endl;
	}
	else { // No error occurred in processStack but stack is not empty yet (i.e. unclosed outer openings)
		cout << "ERROR!!! The following opening symbols were not closed:";
		cout << endl;
		while(!stack.isEmpty()) {
			stack.pop(openSym, lineNum);
			cout << "   Symbol " << openSym << " at line " << lineNum;
			cout << endl;
		}
	}
}
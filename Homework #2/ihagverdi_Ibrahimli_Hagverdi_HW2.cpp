#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;

/*

This program reads two files input from the user and creates corresponding linked lists for them 
with different heads. Then, the user is prompted to enter certain comments and linked lists get modified
accordingly while the user does not enter command "exit".

Written by Hagverdi Ibrahimli (30014) for CS204 course HomeWork #2

Date: 2/22/22;

*/

struct node { 
	char ch; 
	node * next; 
};

int checkArg(char ch);
void readFiles(node* &head1, node* &head2);
void sim(node* head1, node* head2);
void printList(node* head);
int takeCommand(node* head1, node* head2);
void del1(node* &head1, char delChar);
void del2(node* &head2, char delChar);
void insert1(node* &head1, char charInserted , char charSearched );
void insert2(node* &head2, char charInserted , char charSearched );
int checkOccurrence(node* head1, char arg2);
void deleteList(node* head);
void makeList(ifstream &file, node* &head);
void deleteChar(node* &head, char delChar);
void insertChar(node* &head, char charInserted, char charSearched);

int main() {
	node* head1;
	node*head2;
	readFiles(head1, head2); 
	takeCommand(head1, head2);
	return 0;
}

void readFiles(node* &head1, node* &head2) { //Prompt open files until process successful
	ifstream file1, file2;
	string file1name, file2name;

	cout << "Please enter the file 1 name: ";
	cin >> file1name;
	file1.open(file1name.c_str());
	while(file1.fail()) {
		cout << "Please enter the file 1 name: ";
		cin >> file1name;
		file1.open(file1name.c_str());
	}
	cout << "Please enter the file 2 name: ";
	cin >> file2name;
	file2.open(file2name.c_str());
	while(file2.fail()) {
		cout << "Please enter the file 2 name: ";
		cin >> file2name;
		file2.open(file2name.c_str());
	}
	makeList(file1, head1); // After opening the files create corresponding link lists for both with diff. heads.
	makeList(file2, head2);
}

void del1(node* &head1, char delChar) { //func. to delete all the occurrences of the given char. for list1
	if(!checkOccurrence(head1,delChar)) { // check if the character exists in the list to be deleted
		cout << "Deleting all occurrences of " << delChar << " in List1." << endl;
		deleteChar(head1, delChar);
		cout << "The current content of List1 is: ";
		printList(head1);
		cout << endl;
	}
	else{
		cout << "No deletion as the value " << delChar <<" was not found in the list."<< endl;
	}
}

void del2(node* &head2, char delChar) { // deleting func. for list2
	if(!checkOccurrence(head2,delChar)) {
		cout << "Deleting all occurrences of " << delChar << " in List2." << endl;
		deleteChar(head2, delChar);
		cout << "The current content of List2 is: ";
		printList(head2);
		cout << endl;
	}
	else{
		cout << "No deletion as the value " << delChar <<" was not found in the list."<< endl;
	}
}



void insert1(node* &head1, char charInserted , char charSearched ) { //func. to insert a char. into list1
	cout << "Inserting " <<charInserted <<" after " << charSearched << " in List1." << endl;
	insertChar(head1,charInserted,charSearched ); 
}


void insert2(node* &head2, char charInserted , char charSearched ) {//inserting function for list2
	cout << "Inserting " <<charInserted <<" after " << charSearched << " in List2." << endl;
	insertChar(head2,charInserted,charSearched );
}

void sim(node* head1, node* head2) { // function displaying #of characters occuring at the same pos. in both lists
	node* pnt1, *pnt2;
	int counter = 0;
	pnt1 = head1;
	pnt2 = head2;
	while(pnt1 != NULL && pnt2 != NULL) { // while reaching end of the list
		if(pnt1->ch == pnt2->ch) {
			counter ++;
		}
		pnt1 = pnt1 ->next;
		pnt2 = pnt2 -> next;
	}
	cout << "There is/are " << counter << " letter(s) matched in the same positions in both lists." << endl;
}


void printList(node* head) { // func. to print the  linked list of given head pointer
	node* ptr = head;
	while(ptr != NULL) {
		cout << ptr->ch;
		ptr = ptr->next;
	}
}

int checkArg(char ch) { // func. to check if a char. is lowercase and valid letter.
	int check = 1;
	if(ch > 'z' || ch < 'a') {
		 check = 0;
	}
	return check;
}

int checkOccurrence(node* head1, char arg2) {	//func to check if given char. has occurred in the linked list
												//returns true if leter not prev. occurred in linked list
	int cntr = 0;
	int  check = 0;
	node* ptr = head1;
	while(ptr != NULL) {
		if(ptr->ch == arg2) {
			cntr ++;
		}
		ptr = ptr->next;
	}
	if(cntr == 0) {
		check = 1;
	}
	return check;
}

void deleteList(node* head) { // func. to delete linked list with the given head pointer
	node* temp = head;
	while(head != NULL) {
		temp = head->next;
		delete head;
		head = temp;
	}
}

void makeList(ifstream &file, node* &head) { // func. to make a linked list from the input file 											
	char c;
	head = new node; 
	node * temp1 = head;
	while(file >> c) {
		temp1 -> ch = c;
		temp1->next = new node;
		temp1 = temp1->next; // add new node to the end
	}
	temp1 -> next = NULL;
	node* ptr = head;
	while(ptr->next != temp1) { // to delete the last empty node and linking tail to NULL
		ptr = ptr->next;
	}
	ptr->next = NULL;
	delete temp1;
}

void deleteChar(node* &head, char delChar) { // func. to delete all of the occurences of given char. in given linked list head pointer.
	node*ptr = head;
	node*temp;
	while(ptr != NULL) {
			if(head->ch == delChar) { // check if char to be deleted is at head
				temp = head;
				head = head->next;
				delete temp;
				ptr = head;
			}
			else if (ptr->ch == delChar){ // check if anywhere else - delete
				temp->next = ptr->next;
				delete ptr;
				ptr = temp;
				ptr = ptr->next;
			}
			else {
				temp = ptr;
				ptr = ptr->next;
			}

		}
}

void insertChar(node* &head, char charInserted, char charSearched) { // func. to insert char. into given linked list
	node* ptr = head;
	node* temp;
	if(head == NULL || checkOccurrence(head,charSearched)) { // check if list is empty or there is no occurrence of searched char.
		temp = new node;
		temp->ch = charInserted;
		temp ->next = head;
		head = temp;
		cout << "The node with " << charSearched << " value does not exist. Therefore, Inserting " << charInserted << " at the beginning of the list." << endl;
	}
	else {
		while(ptr->ch != charSearched) { // if list is not empty, find charSearched and insert new char after it.
			ptr = ptr->next;
		}
		temp = new node;
		temp->ch = charInserted;
		temp->next = ptr -> next;
		ptr->next = temp;
		cout << "The node with "  << charInserted << " has been inserted after the first occurrence of a node with " << charSearched << " value." << endl;
	}
}


int takeCommand(node* head1, node* head2) { // main prompt of the program and a func. to apply ordered functions until
											// user enters "exit" command.
	cout << "List1: "; printList(head1); cout << endl;
	cout << "List2: "; printList(head2); cout << endl;
	cout << endl;
	string argument; // command of the user to switch to a specific func.
	char arg1, arg2; // arguments for the main command (if any.)
	cout << "Enter a command and its corresponding argument(s), if any: ";
	while(cin >> argument) {
		if(argument == "insert1") {
			cin >> arg1 >> arg2;
			if(checkArg(arg1) && checkArg(arg2)) {
				insert1(head1,arg1,arg2);
				cout << "The current content of List1 is: ";
				printList(head1);
				cout << endl;
			}
			else {
				cout << "Invalid arguments." << endl;
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
			}
		}
		else if (argument == "insert2") {
			cin >> arg1 >> arg2;
			if(checkArg(arg1) && checkArg(arg2)) {
				insert2(head2,arg1,arg2);
				cout << "The current content of List2 is: ";
				printList(head2);
				cout << endl;
			}
			else {
				cout << "Invalid arguments." << endl;
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
			}
		}
		else if (argument == "del1") {
			cin >> arg1;
			if(checkArg(arg1)) {
				del1(head1, arg1);
			}
			else {
				cout << "Invalid argument." << endl;
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
			}
		}
		else if (argument == "del2") {
			cin >> arg1;
			if(checkArg(arg1)) {
				del2(head2, arg1);
			}
			else {
				cout << "Invalid argument." << endl;
				cin.ignore(numeric_limits<streamsize>::max(),'\n');
			}
		}
		else if (argument == "sim") {
			cout << "Displaying the contents of the two lists:" << endl;
			cout << "List1: "; printList(head1); cout << endl;
			cout << "List2: "; printList(head2); cout << endl;
			sim(head1,head2);
		}
		else if (argument == "exit") {
			cout << "Clearing the two lists and saying Goodbye!" << endl;
			deleteList(head1);
			deleteList(head2);
			return 0;
		}
		else{
			cout << "Invalid command." << endl;
			cin.ignore(numeric_limits<streamsize>::max(),'\n'); 
		}
		cout << endl;
		cout << "Enter a command and its corresponding argument(s), if any: ";

	}
}


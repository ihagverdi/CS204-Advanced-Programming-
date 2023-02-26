#include <iostream>
#include "ihagverdi_Ibrahimli_Hagverdi_HW3_linkedList.h"
#include <string>
/*
Written by Hagverdi Ibrahimli (30014) with username ihagverdi on SuCourse+
File contains implementations for the functions to utilize for 2D linked list manipulations.
1/3/22
*/
LinkedListTwoD::LinkedListTwoD() { //constructor
	head = NULL;
};

 node* LinkedListTwoD::makeRow(string line){ // read a line from the file, turns it into a linked list.
	 node* head2;
	 head2 = new node;
	 node * temp1 = head2;
	 for(unsigned int a = 0; a < line.length(); a++) {
		temp1 -> data = line[a];
		temp1->right = new node;
		if(a == (line.length()-1)) {
			temp1->right = NULL;
		}
		else {
		temp1 = temp1->right; 
		} 
	}
	return head2;
 }

void LinkedListTwoD::add_row_sorted(string line) { // adds the created linked list containing
													//the word from the file to
													// create (if empty) or add (if not emp.) to the 2D structure.
	node* head2 = makeRow(line);
	if(head == NULL) {// initially list is empty
		head = head2;
	}
	else {
		if((head2->data) <= (head->data)) { // switch head and new head2 if head2 is smaller in first char.
			node* ptr = head;
			head = head2;
			head2 = ptr;
		}
		node* temp;
		temp = head;
		if(temp->down == NULL) {
				while (temp != NULL) {
				head->down = head2;
				head = head->right;
				head2 = head2->right;
				}
			}
		else {
		while(temp -> down != NULL && temp->down->data < line[0]) { // finding the point of insertion
			temp = temp->down;
		}
		while(temp != NULL) { // merge the linked list to the one after the deleted one
			head2->down = temp->down;
			temp->down = head2;
			temp = temp->right;
			head2 = head2 ->right;
		}
		}
	}
}

void LinkedListTwoD::displayFullMatrix() { // displaying the whole 2D structure
	
	node* ptr = head;
	while(ptr != NULL) {
		node*temp = ptr;
		while(temp != NULL) {
			cout << temp->data;
			temp = temp->right;
		}
		cout << endl;
		ptr = ptr->down;
	}
}

void LinkedListTwoD::displayFullMatrixReversed() { // helper func. for public version
	displayFullMatrixReversed(head);
}

void LinkedListTwoD::displayFullMatrixReversed(node*n) { // recursive method to print 2D structure 
														// Recursively
	if(n!= NULL) {
		displayFullMatrixReversed(n->down);
		node* ptr = n;
		while(ptr!= NULL) {
			cout << ptr->data;
			ptr = ptr->right;
		}
		cout << endl;
	}
	
	
}


void LinkedListTwoD::display_rows_starting_with(char ch) { // displaying rows of 2D structure starting 
															// with user input character
	node* ptr = head;
	while(ptr!= NULL) {
		if(ptr->data == ch) {
			node* temp = ptr;
			while(temp!=NULL) {
				cout << temp->data;
				temp = temp->right;
			}
			cout << endl;
		}
		ptr = ptr->down;
	}
	
}

void LinkedListTwoD::display_cols_starting_with(char ch) { // displaying columns starting with char. input
															// by user.
	node* ptr = head;
	while(ptr!= NULL) {
		if(ptr->data == ch) {
			node* temp = ptr;
			while(temp!=NULL) {
				cout << temp->data;
				cout << endl;
				temp = temp->down;
			}
			cout << endl;
		}
		ptr = ptr->right;
	}
	
}

bool LinkedListTwoD::charFoundRow(char ch) { // func. to check if still exists a char. in 2D structure
											// to be deleted.
	node* ptr = head;
	while(ptr!= NULL) {
		if(ptr->data == ch) {
			return true;
	}
	ptr = ptr->down;
	}
	return false;
}

void LinkedListTwoD::deleteList_row(node* del) { // func. to delete linked list with the given head pointer
	node* temp = del;
	while(del != NULL) {
		temp = del->right;
		delete del;
		del = temp;
	}
}

void LinkedListTwoD::deleteList_col(node* del) { // func. to delete linked list with the given head pointer
	node* temp = del; 
	while(del != NULL) {
		temp = del->down;
		delete del;
		del = temp;
	}
}

bool LinkedListTwoD::charFoundCol(char ch) { // searching cols. for deleted char whether it exists
	node* ptr = head;
	while(ptr!=NULL) {
		if(ptr->data == ch) {
			return true;
		}
		ptr = ptr->right;
	}
	return false;
}

int LinkedListTwoD::delete_rows_starting_with(char ch) { // deleting rows starting with char. input by USER
	int numDeleted= 0;
	while(head != NULL && charFoundRow(ch)) {
		node* ptr = head;
		if(head->data == ch) {
			head = head->down;
			deleteList_row(ptr);
			numDeleted++;
		}
		else{
			while(ptr != NULL) { // ptr is head of row to be deleted
				if(ptr->data == ch) { 
					node*temp = head;
					while(temp->down != ptr) {
						temp = temp->down;
					}
					node* ptr2 = temp;
					while(temp != NULL) { // merging lists
						temp->down = ptr->down;
						temp = temp->right;
						ptr = ptr->right;
					}
					deleteList_row(ptr); // deleting list with char. in head
					ptr = ptr2;
					numDeleted++;
				}
				ptr = ptr->down;
			}
		}
		
	}
	return numDeleted;
}





int LinkedListTwoD::delete_cols_starting_with(char ch) { // deleting cols. starting with char input by user.
	int numDeleted= 0;
	while(head != NULL && charFoundCol(ch)) {
		node* ptr = head;
		if(head->data == ch) {
			head = head->right;
			deleteList_col(ptr);
			numDeleted++;
		}
		else{
			while(ptr != NULL) { // ptr is head of row to be deleted
				if(ptr->data == ch) { 
					node*temp = head;
					while(temp->right != ptr) {
						temp = temp->right;
					}
					node* ptr2 = temp;
					while(temp != NULL) {
						temp->right = ptr->right;
						temp = temp->down;
						ptr = ptr->down;
					}
					deleteList_col(ptr);
					ptr = ptr2;
					numDeleted++;
				}
				ptr = ptr->right;
			}
		}
		
	}
	return numDeleted;
}

void LinkedListTwoD::clear() { // hel[er func. for public recursive clear func.
	clear(head);
}

void LinkedListTwoD::clear(node* n) {  // clearing 2D structure
	if(n!= NULL) {
		clear(n->down);
		node* ptr = n;
		while(ptr!= NULL) {
			node* ptr2 = ptr->right;
			delete ptr;	
			ptr = ptr2;
		}
	}
	head = NULL;
}





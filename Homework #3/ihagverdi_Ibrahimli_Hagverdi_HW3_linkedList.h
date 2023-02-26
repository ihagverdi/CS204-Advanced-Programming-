#ifndef _IHAGVERDI_IBRAHIMLI_HAGVERDI_HW3_LINKEDLIST_H
#define _IHAGVERDI_IBRAHIMLI_HAGVERDI_HW3_LINKEDLIST_H
using namespace std;

/*
Written by Hagverdi Ibrahimli (30014) with username ihagverdi on SuCourse+
Header file contains the functions to utilize for 2D linked list manipulations.
1/3/22
*/
struct node {
	char data;
	node *right;
	node *down;
	node() {
		right = NULL;
		down = NULL;
	}
};

class LinkedListTwoD {
	private:
		node* head;
		void displayFullMatrixReversed(node*);
		void clear(node*);
	public: 
		LinkedListTwoD(); 
		node* makeRow(string line);
		void add_row_sorted(string line);
		void displayFullMatrix();
		bool charFoundRow(char ch);
		bool charFoundCol(char ch);
		void deleteList_col(node* del);
		void deleteList_row(node* del);
		void displayFullMatrixReversed();
		void display_rows_starting_with(char ch);
		void display_cols_starting_with(char ch);
		int delete_rows_starting_with(char ch); //return # of deleted rows
		int delete_cols_starting_with(char ch); // return # of deleted cols
		void clear(); // delete 2d Matrix
		
};

#endif

#include <iostream>
using namespace std;

/*
Written by Hagverdi Ibrahimli in 5.18.2022 for CS204 course.
Provides implementation for the templated Board class which aims to
construct a row x columns size of matrix and operate certain
functions on it.
Username: ihagverdi
Id: 30014
*/


template<class T>
Board<T>:: Board() { //def. constructor
	matrix = NULL;
	cell_rows = 0;
	cell_cols = 0;
}
template <class T>
Board<T>:: Board(const int &rows, const int &cols) { //par. constructor
	cell_rows = rows;
	cell_cols = cols;
	//creating a dynamic 2d matrix
	matrix = new cell<T>* [cell_rows];
	for(int i = 0; i < cell_rows; i++) {
		matrix[i] = new cell<T>[cell_cols]; 
	}
	//initializing owners to 0
	for(int i = 0; i < cell_rows; i++){
		for(int b = 0; b < cell_cols; b++){
			matrix[i][b].cell_owner = 0;
		}
	}
}
template <class T>
Board<T>:: Board(const Board<T> &copy) {// deep-copy construct.
	cell_rows = copy.cell_rows;
	cell_cols = copy.cell_cols;
	matrix = new cell<T>* [cell_rows];
	for(int i = 0; i < cell_rows; i++) {
		matrix[i] = new cell<T>[cell_cols]; 
	}
	for(int i = 0; i < cell_rows; i++){
		for(int b = 0; b < cell_cols; b++){
			matrix[i][b].cell_owner = copy.matrix[i][b].cell_owner;
			matrix[i][b].cell_value = copy.matrix[i][b].cell_value;
		}
	}
}
template <class T>
void Board<T>:: displayBoard() const {  //displaying board in a tuple manner
	cout << "Displaying the board: Each cell is shown as tuple (CURRENT OWNER ID, VALUE):";
	cout << endl;
	cout << endl;
	for(int i = 0; i < cell_cols; i++){
		cout << '\t' << i;
	}
	cout << endl;
	for(int i = 0; i < cell_rows; i++){
		cout << i  << '\t';
		for(int b = 0; b < cell_cols; b++){
			cout << '(' << matrix[i][b].cell_owner << ',' << matrix[i][b].cell_value << ')';
			cout << '\t';
		}
		cout << endl;
	}
}
template <class T>
void Board<T>:: updateBoardCells(const int &id, const T &value){
	for(int i = 0; i < cell_rows; i++){
		for(int b = 0; b < cell_cols; b++){
			if(knowTheOwner(i,b) == id) { //Updating all of the cell owned by the player.
				matrix[i][b].cell_value = value;
			}
		}
	}
}
template <class T>
int Board<T>:: getPlayerCellsCount(const int &id) const {
	int player_cells = 0;
	for(int i = 0; i < cell_rows; i++){
		for(int b = 0; b < cell_cols; b++){
			if(knowTheOwner(i,b) == id) {
				player_cells++;
			}
		}
	}
	return player_cells;
}
template <class T>
int Board<T>:: knowTheOwner(const int &row, const int &col) const {
	return (matrix[row][col].cell_owner);
}
template <class T>
void Board<T>:: updateCell(const int &row, const int &col, const T &value){
	matrix[row][col].cell_value = value;
}
template <class T>
void Board<T>:: setOwner(const int &row, const int &col, const int &id){
	matrix[row][col].cell_owner = id;
}
template <class T>
void Board<T>:: unAll(const int &id){
	for(int i = 0; i < cell_rows; i++){
		for(int b = 0; b < cell_cols; b++){
			if(knowTheOwner(i,b) == id) { //removing ownership of the cells owned by the user keeping the value.
				matrix[i][b].cell_owner = 0;
			}
		}
	}
}
template <class T>
void Board<T>:: unOne(const int &row, const int &col){ //removing ownership of a single cell
	matrix[row][col].cell_owner = 0;
}
template <class T>
Board<T>:: ~Board() {
	for(int i = 0; i < cell_rows; i++){
		delete [] matrix[i]; //deleting columns
	}
	delete [] matrix; //deleting rows
	cell_rows, cell_cols = 0;
	matrix = NULL;
}




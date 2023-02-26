#ifndef _ihagverdi_Ibrahimli_Hagverdi_HW6_board_H
#define _ihagverdi_Ibrahimli_Hagverdi_HW6_board_H
#endif

/*
Written by Hagverdi Ibrahimli in 5.18.2022 for CS204 course.
Username: ihagverdi
Id: 30014
*/

template <class T>
struct cell{
	int cell_owner;
	T cell_value;

};
template <class T>
class Board{
public:
	Board();
	Board(const Board<T> &copy);
	Board(const int &rows, const int &cols); 
	~Board();
	void displayBoard() const;
	void updateBoardCells(const int &id, const T &value);
	void updateCell(const int &row, const int &col, const T &value);
	void setOwner(const int &row, const int &col, const int &id);
	int getPlayerCellsCount(const int &id) const;
	int knowTheOwner(const int &row, const int &col) const ;
	void unAll(const int &id);
	void unOne(const int &row, const int &col);
	
private:
	cell<T>** matrix;
	int cell_rows;
	int cell_cols;
};

#include "ihagverdi_Ibrahimli_Hagverdi_HW6_board_imp.cpp"
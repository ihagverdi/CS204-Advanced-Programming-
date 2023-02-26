#ifndef _ihagverdi_Ibrahimli_Hagverdi_HW6_player_H
#define _ihagverdi_Ibrahimli_Hagverdi_HW6_player_H
#endif

/*
Written by Hagverdi Ibrahimli in 5.18.2022 for CS204 course.
Username: ihagverdi
Id: 30014
*/

template <class T>
class Player{
public:
	Player(Board<T> &board);
	bool updateCell(const int &row, const int &col, const T &value);
	void updateMyCells(const T &value);
	bool unclaimOwnership(const int &row, const int &col);
	void unclaimOwnerships();
private:
	int my_id;
	static int next_id;
	Board<T> &myBoard;
};

template <class T>
int Player<T>::next_id = 1;

#include "ihagverdi_Ibrahimli_Hagverdi_HW6_player_imp.cpp"
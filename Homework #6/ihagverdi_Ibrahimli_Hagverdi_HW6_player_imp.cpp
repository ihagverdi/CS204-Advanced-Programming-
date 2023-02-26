
/*
Written by Hagverdi Ibrahimli in 5.18.2022 for CS204 course.
Provides implementation for the Templated Player class which aims to create
players ready to operate certain commands/functions on a again templated board class.
Username: ihagverdi
Id: 30014
*/

template <class T>
Player<T>:: Player(Board<T> &board): myBoard(board) //parametric constructor
{
	my_id = next_id;
	next_id++;
}
template <class T>
bool Player<T>:: updateCell(const int &row, const int &col, const T &value){ //updating the cell value either owned by the player or free as of calling.
	bool updated = true;													//returning true if value change has happened for the cell.
	if( myBoard.knowTheOwner(row,col) == my_id || myBoard.knowTheOwner(row,col) == 0 ){
		myBoard.setOwner(row,col,my_id);
		myBoard.updateCell(row,col,value);
	}
	
	else{
		updated = false;
	}
	return updated;
}
template <class T>
void Player<T>:: updateMyCells(const T &value){ //updating all the cells owned by the player with given value.
	myBoard.updateBoardCells(my_id,value);
}
template <class T>
bool Player<T>:: unclaimOwnership(const int &row, const int &col){//unclaiming ownerships of the given cell previously owned by the player
																 //returning true if unclaiming op. has been carried out.
	bool changed = true;
	if(myBoard.knowTheOwner(row,col) == my_id){
		myBoard.unOne(row,col);
	}
	else{
		changed = false;
	}
	return changed;
}

template <class T>
void Player<T>:: unclaimOwnerships(){ //unclaiming ownerships of all the cells owned by the player.
	myBoard.unAll(my_id);
}
#pragma once
#include <iostream>
#include <utility>
#include <vector>
#include "Board.h"
#include "square.h"
class Board;


class Tool 
{

protected:
	square _location;

	char _type;

	bool _isWhite;


public:
	Tool(square loc, char type, bool white);

	virtual ~Tool();
	
	void setLocation(square newLoc);
	
	square getLocation();
	
	bool isWhite();
	
	char getType();
	
	virtual std::vector <square>& getPossibleMoves(Board& b)  = 0;
};

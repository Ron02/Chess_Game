#pragma once
#include <iostream>
#include <utility>
#include "Tool.h"
#include "Board.h"
#include "square.h"




class Rook : public Tool 
{

public:
	Rook(square loc, char type, bool white); //  Rook parameters.

	~Rook();

	virtual std::vector <square>& getPossibleMoves(Board& b) ; //  getting the possible moves for the Rook.
};


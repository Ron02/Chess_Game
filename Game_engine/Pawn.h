#pragma once
#include <iostream>
#include <utility>
#include "Tool.h"
#include "Board.h"
#include "square.h"

class Pawn : public Tool 
{
	bool firstMove;

public:
	Pawn(square loc, char type, bool white); //  Pawn parameters.

	~Pawn();

	virtual std::vector <square>& getPossibleMoves(Board& b) ; //  getting the possible moves for the Pawn.
};


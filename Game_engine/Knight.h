#pragma once
#include <iostream>
#include <utility>
#include "Tool.h"
#include "Board.h"
#include "square.h"

class Knight : public Tool
{

public:
	Knight(square loc, char type, bool white); // Knight parameters.

	~Knight();

	virtual std::vector <square>& getPossibleMoves(Board& b); //  getting the possible moves for the Knight.
};


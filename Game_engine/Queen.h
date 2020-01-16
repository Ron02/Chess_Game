#pragma once
#include <iostream>
#include <utility>
#include "Tool.h"
#include "Board.h"
#include "square.h"


class Queen : public Tool
{

public:
	Queen(square loc, char type, bool white); //  Queen parameters.

	~Queen();

	virtual std::vector <square>& getPossibleMoves(Board& b) ; //  getting the possible moves for the Queen.
};



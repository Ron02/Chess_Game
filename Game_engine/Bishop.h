#pragma once
#include <iostream>
#include <utility>
#include "Tool.h"
#include "Board.h"
#include "square.h"



class Bishop : public Tool
{

public:
	Bishop(square loc, char type, bool white); //  Bishop parameters.

	~Bishop();

	virtual std::vector <square>& getPossibleMoves(Board& b) ; // getting the possible moves for the Bishop.
};




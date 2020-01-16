#pragma once
#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include "square.h"
#include "Board.h"
#include "Tool.h"

typedef std::map <std::pair <char, int>, Tool*> Bstruct;

class chessChecker 
{
	square findKing(Board& b , bool white);

public:
	bool possibleMat(square src, square dst, Board& b , bool white);

	bool playerMadeChess(Board& b, bool white);
};
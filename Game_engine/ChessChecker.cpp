#include "ChessChecker.h"
#include <iostream>

/*
  This function is looking on the board to find the location of the King.
*/
square chessChecker :: findKing (Board& b , bool white) 
{
	square kingLoc;

	for (int i = 1; i < 9; i++)
	{
		for (char j = 'a'; j < 'i'; j++)
		{
			if (b.getToolAtPos({ j , i }) != nullptr && b.getToolAtPos({ j , i })->getType() == 'k' && b.getToolAtPos({ j , i })->isWhite() == white) 
			{
				kingLoc = b.getToolAtPos({ j , i })->getLocation();

				break;
			}
		}
	}

	return kingLoc;
}

/*
  This function is checking if chess will accure.
*/
bool chessChecker :: possibleMat(square src, square dst, Board& b, bool white) 
{
	Board locB = Board();

	bool chess = false;

	std::vector<square> posMove;

	Tool* tempTool = b.getToolAtPos(dst);

	b.move(src, dst);

	square king = findKing(b, white);

	for (int i = 1 ; i < 9 ; i++) 
	{
		for (char j = 'a' ; j < 'i' ; j++) 
		{
			if (b.getToolAtPos({j , i}) != nullptr && b.getToolAtPos({ j , i })->isWhite() != white) 
			{
				posMove = b.getToolAtPos({ j , i })->getPossibleMoves(b);

				if (std::count(posMove.begin(), posMove.end(), king)) 
				{
					b.move(dst, src);
					return true;
				}
			}
		}
	}

	b.move(dst, src);
	b.setTool(dst, tempTool);

	return false;
}


/*
  This function is checking if chess accured.
*/
bool chessChecker :: playerMadeChess(Board& b, bool white) 
{
	square king = findKing(b, !white);
	std::vector <square> posMov;

	for (int i = 1  ; i < 9 ; i++) 
	{
		for (char j = 'a' ; j < 'i' ; j++) 
		{
			if (b.getToolAtPos({ j , i }) != nullptr && b.getToolAtPos({ j , i })->isWhite() == white) 
			{
				posMov = b.getToolAtPos({ j , i })->getPossibleMoves(b);

				if (std::count(posMov.begin(), posMov.end(), king)) 
				{
					return true;
				}
			}
		}
	}

	return false;
}
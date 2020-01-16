#include <iostream>
#include <utility>

#include "Board.h"
#include "Rook.h"
#include "Tool.h"
#include "Bishop.h"
#include "Queen.h"
#include "Pawn.h"
#include "King.h"
#include "Knight.h"


Board :: Board () 
{
	//nothing
}


Board :: ~Board () 
{
	//nothing
}

/*
  This function creating tools on the board.
*/
void Board :: initBoard () 
{
	Tool* currTool;
	bool isWhite;
	for (int i = 1 ; i < 9 ; i++) 
	{
		for (char c = 'a' ; c < 'i' ; c++) 
		{
			isWhite = i <= 2 ? true : false;

			square p = { c , i };

			if (i == 2 || i == 7) 
			{
				currTool = new Pawn(p, 'p', isWhite);
			}

			else if (i == 1 || i == 8)
			{
				if (c == 'a' || c == 'h')
				{
					currTool = new Rook(p, 'r', isWhite);
				}

				if (c == 'b' || c == 'g')
				{
					currTool = new Knight(p, 'n', isWhite);
				}

				if (c == 'c' || c == 'f')
				{
					currTool = new Bishop(p, 'b', isWhite);
				}

				if (c == 'd')
				{
					currTool = new King(p, 'k', isWhite);
				}

				if (c == 'e')
				{
					currTool = new Queen(p, 'q', isWhite);
				}
			}
			else
			{
				currTool = nullptr;
			}

			board.insert({ p , currTool });
		}
	}
}

/*
  This function getting the tool that is on the possition.
*/
Tool* Board :: getToolAtPos (square p) 
{
	return board[p];
}

/*
  This function is the move function , move the tool from src point to the dst point.
*/
void Board ::move (square src , square dst) 
{
	board[src]->setLocation(dst);
	board[dst] = board[src];
	board[src] = nullptr;
}

void Board :: setTool(square p, Tool* tool) 
{
	board[p] = tool;
}


#include "./Protocol/Pipe.h"

#include <iostream>
#include <utility>
#include <vector>
#include <vector>

#include "Board.h"
#include "Tool.h"
#include "Rook.h"
#include "Bishop.h"
#include "Settings.h"
#include "square.h"
#include "Exceptions.h"
#include "ChessChecker.h"

// the main function.
int main()
{
	Pipe p = Pipe();
	std::string msg;

	square src;
	square dst;

	std::vector <square> posMov;
	Tool* currTool;
	chessChecker checker = chessChecker();
	bool whiteTurn = true;

	Board board = Board();
	board.initBoard();
	//connectiong.
	bool connected = p.connect();
	//check if can't connect.
	if (!connected)
	{
		std::cout << "\n\n\n\n                   can not connect!\n\n\n\n";
		exit(1);
	}

	p.sendMessageToGraphics(bSit);

	while (1)
	{
		try 
		{
			msg = p.getMessageFromGraphics();

			if (msg == "quit")
			{
				exit(0);
			}

			src = { msg[0] , msg[1] - '0' };
			dst = { msg[2] , msg[3] - '0' };

			currTool = board.getToolAtPos(src);

			if (!currTool)
			{
				throw (emptySquare());
			}

			if (currTool->isWhite() != whiteTurn)
			{
				throw (notTurn());
			}

			if (src == dst)
			{
				throw (sameSquare());
			}

			if (board.getToolAtPos(dst)) if (currTool->isWhite() == board.getToolAtPos(dst)->isWhite())
			{
				throw (playerInDst());
			}

			posMov = currTool->getPossibleMoves(board);

			if (std::count(posMov.begin(), posMov.end(), dst))
			{
				if (checker.possibleMat(src, dst, board, whiteTurn))
				{
					throw (PosMat());
				}

				board.move(src, dst);

				checker.playerMadeChess(board , whiteTurn) ? p.sendMessageToGraphics(codes[ok_chess]) : p.sendMessageToGraphics(codes[ok]);
				
				whiteTurn = !whiteTurn;
			}
			else
			{
				throw (iliigleMove());
			}
		}

		catch (emptySquare) 
		{
			p.sendMessageToGraphics(codes[no_player]);
		}

		catch (sameSquare) 
		{
			p.sendMessageToGraphics(codes[same_square]);
		}

		catch (PosMat) 
		{
			p.sendMessageToGraphics(codes[move_chess]);
		}

		catch (playerInDst) 
		{
			p.sendMessageToGraphics(codes[player_dst]);
		}

		catch (iliigleMove)
		{
			p.sendMessageToGraphics(codes[illigle_move]);
		}

		catch (notTurn) 
		{
			p.sendMessageToGraphics(codes[no_player]);
		}
	}

	getchar();
}

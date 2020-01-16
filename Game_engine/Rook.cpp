#include "Rook.h"
#include <vector>

/*
  Rook parameters.
*/
Rook :: Rook (square loc, char type, bool white) : Tool (loc , type , white)
{
	_location = loc;
	_type = type;
	_isWhite = white;
}


Rook :: ~Rook () 
{
	//nothing
}

/*
  getting the possible moves for the Rook.
*/
std::vector <square>& Rook :: getPossibleMoves (Board& b) 
{
	std::vector<square>* posMov = new std::vector<square>();

	int itr = 1;
	bool cont = true;
	bool isTool = false;
	square p;

	for (int i = _location.second + 1 ; cont ; i += itr) 
	{
		p = { _location.first , i };

		if (!isTool && i < 9 && i > 0) 
		{
			posMov->push_back(p);

			if (b.getToolAtPos(p) != nullptr) 
			{
				isTool = true;
				if (b.getToolAtPos(p)->isWhite() == _isWhite) posMov->pop_back();
			}
		}
		else 
		{
			itr == -1 ? cont = false : itr = -1, i = _location.second;
			isTool = false;
		}
	}

	itr = 1;
	cont = true;
	isTool = false;

	for (int i = _location.first + 1; cont; i += itr)
	{
		p = { i , _location.second };

		if (!isTool && i < 'i' && i >= 'a') 
		{
			posMov->push_back(p);

			if (b.getToolAtPos(p) != nullptr) 
			{
				isTool = true;
				if (b.getToolAtPos(p)->isWhite() == _isWhite) posMov->pop_back();
			}
		}
		else 
		{
			itr == -1 ? cont = false : itr = -1, i = _location.first;
			isTool = false;
		}
	}

	return *posMov;
}
#include "Queen.h"
#include <vector>

/*
  Queen parameters.
*/
Queen :: Queen (square loc, char type, bool white) : Tool(loc, type, white)
{
	_location = loc;
	_type = type;
	_isWhite = white;
}


Queen :: ~Queen()
{
	//nothing
}

/*
  getting the possible moves for the Queen.
*/
std::vector <square>& Queen ::getPossibleMoves(Board& b) 
{
	std::vector<square>* posMov = new std::vector<square>();

	int itr = 1;
	bool cont = true;
	bool isTool = false;

	square p;

	for (int i = _location.second + 1; cont; i += itr)
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

	itr = 1;
	cont = true;
	isTool = false; 

	for (int i = _location.second + 1, j = _location.first + 1; cont; i += itr, j += itr)
	{
		p = { j , i };

		if (!isTool && i < 9 && i > 0 && j < 'i' && j >= 'a') 
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
			itr == -1 ? cont = false : itr = -1, i = _location.second, j = _location.first;
			isTool = false;
		}
	}

	itr = 1;
	cont = true;
	isTool = false;

	for (int i = _location.first + 1, j = _location.second - 1; cont; i += itr, j -= itr)
	{
		p = { i , j };

		if (!isTool && i < 'i' && i >= 'a' && j < 9 && j >= 0) 
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
			itr == -1 ? cont = false : itr = -1, i = _location.first, j = _location.second;
			isTool = false;
		}
	}

	return *posMov;
}
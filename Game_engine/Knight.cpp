#include "Knight.h"
#include <vector>

/*
  Knight parameters.
*/
Knight::Knight(square loc, char type, bool white) : Tool(loc, type, white)
{
	_location = loc;
	_type = type;
	_isWhite = white;
}


Knight :: ~Knight()
{
	//nothing
}

/*
  getting the possible moves for the Knight.
*/
std::vector<square>& Knight::getPossibleMoves(Board& b)
{
	std::vector <square>* posMov = new std::vector<square>();
	int itr = 1;
	square p;
	p = { _location.first + 2 , _location.second + 1 };
	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first + 2 , _location.second - 1 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first - 2 , _location.second + 1 };
	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first - 2 , _location.second - 1};

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first + 1 , _location.second + 2 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first - 1 , _location.second + 2 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first + 1 , _location.second - 2 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first - 1 , _location.second - 2 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}

	return *posMov;
}
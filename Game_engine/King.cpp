#include "King.h"
#include <vector>

/*
  King parameters.
*/
King::King(square loc, char type, bool white) : Tool(loc, type, white)
{
	_location = loc;
	_type = type;
	_isWhite = white;
}


King :: ~King()
{
	//nothing
}

/*
  getting the possible moves for the King.
*/
std::vector<square>& King :: getPossibleMoves (Board& b) 
{
	std::vector <square>* posMov = new std::vector<square>();

	int itr = 1;
	square p;

	p = { _location.first , _location.second + 1 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first + 1 , _location.second  };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first , _location.second - 1 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first - 1 , _location.second  };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first + 1 , _location.second + 1 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first - 1 , _location.second + 1 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first + 1 , _location.second - 1 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}
	p = { _location.first - 1 , _location.second - 1 };

	if (b.getToolAtPos(p) == nullptr || b.getToolAtPos(p)->isWhite() != _isWhite)
	{
		posMov->push_back(p);
	}

	return *posMov;
}
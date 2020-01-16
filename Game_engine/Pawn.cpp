#include "Pawn.h"
#include <vector>

/*
  Pawn parameters.
*/
Pawn :: Pawn(square loc, char type, bool white) : Tool(loc, type, white)
{
	firstMove = true;
	_location = loc;
	_type = type;
	_isWhite = white;
}


Pawn :: ~Pawn()
{
	//nothing
}

/*
  getting the possible moves for the Pawn.
*/
std::vector <square>& Pawn::getPossibleMoves(Board& b)  
{
	std::vector <square>* posMov = new std::vector<square>;
	square p; 

	int itr = _isWhite ? 1 : -1;

	if (_location.second + itr < 9 && b.getToolAtPos({_location.first , _location.second + itr }) == nullptr) 
	{
		p = { _location.first  , _location.second + itr };
		posMov->push_back(p);
	}

	if ((_location.second == 2 || _location.second == 7) && _location.second + itr*2 < 9 && b.getToolAtPos({ _location.first , _location.second + itr*2 }) == nullptr && b.getToolAtPos({ _location.first , _location.second + itr}) == nullptr)
	{
		p = { _location.first  , _location.second + itr*2 };
		posMov->push_back(p);
	}
	
	if (b.getToolAtPos({ _location.first + itr , _location.second + itr }) != nullptr && b.getToolAtPos({ _location.first + itr , _location.second + itr })->isWhite() != _isWhite)
	{
		posMov->push_back({ _location.first + itr , _location.second + itr });
	}
	
	if (b.getToolAtPos({ _location.first - itr , _location.second + itr }) != nullptr && b.getToolAtPos({ _location.first - itr , _location.second + itr })->isWhite() != _isWhite)
	{
		posMov->push_back({ _location.first - itr , _location.second + itr });
	}

	return *posMov;
}
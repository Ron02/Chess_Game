#include "Tool.h"
#include <iostream>

/*
  Tool parameters.
*/
Tool :: Tool (square loc, char type, bool white) 
{
	_location = loc;
	_type = type;
	_isWhite = white;
}


Tool ::~Tool () 
{
	//nothing
}

/*
  the locatin of the Tool.
*/
square Tool :: getLocation () 
{
	return _location;
}

/*
  setting the location.
*/
void Tool :: setLocation (square newLoc) 
{
	_location = newLoc;
}

/*
  check if the Tool is White.
*/
bool Tool ::isWhite () 
{
	return _isWhite;
}

/*
  get the type of the Tool.
*/
char Tool ::getType () 
{
	return _type;
}


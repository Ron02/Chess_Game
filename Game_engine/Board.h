#pragma once
#include <iostream>
#include <map>
#include <utility>
#include "Tool.h";
#include "square.h"

class Tool;

typedef std::map <square, Tool*> Bstruct;


class Board 
{
	Bstruct board;

public:
	Board();

	~Board();

	void initBoard();

	Tool* getToolAtPos(square p);

	void move(square src, square dest);

	void setTool(square p, Tool* tool);
};

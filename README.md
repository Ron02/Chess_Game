# Chess_Game
a simple chess game allowing 2 players to play against each other or singal player to play against AI.
contains "Game Engine" and "Game graphics" communicate with each other in named pipes.
also contains AI algorithem in "minMax.py". 
# Game Engine
a game engine , written in C++ 17 , gets a move from the graphics and return code '0' if move is valid
or other status code if not.
# Chess graphics
a graphic module , written in C# at .NET 3.6 framework , get a move from player and send it to Game engine
if move is valid change the piece position on board , if not display error (illigle move , not your turn etc...).
# Chess AI
a simple chess AI , get board current state and return optimal move , called by the graphics.
written in python 3.7, using minMax algorithem.

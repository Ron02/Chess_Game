#pragma once
#include <iostream>
#include <utility>
#include <map>



char bSit[1000] = "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1";

char codes[9][2] = { {"0"} , {"1"} , {"2"} , {"3"} , {"4"} ,{"5"} , {"6"} , {"7"} , {"8"} };

enum code {ok  , ok_chess , no_player , player_dst , move_chess , illigle_index ,
illigle_move , same_square ,chess_met};


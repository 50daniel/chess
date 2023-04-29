#pragma once


#include"Player.h"
#include"Viewer.h"
#include"AI.h"
class GameManager
{
public:

	Player players[2];
	int current_player;
	Board board;
	Viewer viewer;
	AIplayer AI;
	int undo;
	bool canRedo;
	bool gameOver(Board b);
	GameManager();
	~GameManager();

private:

};


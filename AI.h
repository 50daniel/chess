#pragma once
#include"Player.h"
class AIplayer :public Player
{
public:
	Position  AIfrom[10000], AIto[10000];
	int AIcount;
	AIplayer();
	~AIplayer();
	void randenMove(Board& b);
private:

};



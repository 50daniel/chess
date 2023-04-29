#pragma once
#include<iostream>
#include<string>
#include"board.h"
#include"Pos.h"
using namespace std;

class Player
{
public:
	bool canMove;
	//	bool checkmate;

	Player();
	~Player();
	void onMove(int curr, Board& b, Position fromPos, Position toPos);
	bool isKingEaten(int curr, Board& b);
	void Move(Board& b, Position fromPos, Position toPos);
private:

};


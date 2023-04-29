#pragma once
#include<iostream>
#include<string>
#include"Pos.h"
using namespace std;

class Board
{
public:
	int board[8][8];
	int reBoard[8][8];
	int undo[1000][8][8];
	int rePlay[1000][8][8];
	int passCount;
	bool canPassant;
	bool pawnChange;
	bool kingMoveB;
	bool kingMoveW;
	bool rookMove00;
	bool rookMove07;
	bool rookMove70;
	bool rookMove77;
	bool Castling;
	Position passant;
	Board();
	~Board();
	void reboToBo(int re[][8]);

private:

};


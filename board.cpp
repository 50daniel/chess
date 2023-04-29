#include"board.h"



void Board::reboToBo(int re[][8])
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			this->board[i][j] = re[i][j];
		}
	}
}

Board::Board()
{
	passCount = 0;
	canPassant = false;
	passant.x = 0;
	passant.y = 0;
	pawnChange = true;
	bool kingMoveB = false;
	bool kingMoveW = false;
	bool rookMove00 = false;
	bool rookMove07 = false;
	bool rookMove70 = false;
	bool rookMove77 = false;
	bool Castling = false;

	board[0][0] = 1;
	board[1][0] = 2;
	board[2][0] = 3;
	board[3][0] = 4;
	board[4][0] = 5;
	board[5][0] = 3;
	board[6][0] = 2;
	board[7][0] = 1;

	board[0][1] = 6;
	board[1][1] = 6;
	board[2][1] = 6;
	board[3][1] = 6;
	board[4][1] = 6;
	board[5][1] = 6;
	board[6][1] = 6;
	board[7][1] = 6;
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			board[j][i] = 0;
		}

	}
	board[0][6] = -6;
	board[1][6] = -6;
	board[2][6] = -6;
	board[3][6] = -6;
	board[4][6] = -6;
	board[5][6] = -6;
	board[6][6] = -6;
	board[7][6] = -6;

	board[0][7] = -1;
	board[1][7] = -2;
	board[2][7] = -3;
	board[3][7] = -4;
	board[4][7] = -5;
	board[5][7] = -3;
	board[6][7] = -2;
	board[7][7] = -1;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			reBoard[i][j] == board[i][j];
			rePlay[0][i][j] == board[i][j];
		}

	}

}

Board::~Board()
{
}

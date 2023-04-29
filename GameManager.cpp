#include"GameManager.h"

bool GameManager::gameOver(Board b)
{
	b.pawnChange = false;
	int nextPlayer = (current_player + 1) % 2;
	for (int m = 0; m < 8; m++)
	{
		for (int n = 0; n < 8; n++)
		{
			Position from, to;
			from.x = m;
			from.y = n;
			if (nextPlayer == 0 && b.board[m][n] > 0)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						to.x = j;
						to.y = i;
						players[nextPlayer].onMove(nextPlayer, b, from, to);
						if (players[nextPlayer].canMove)
						{
							players[nextPlayer].Move(b, from, to);
							if (!players[nextPlayer].isKingEaten(nextPlayer, b))
							{
								b.pawnChange = true;
								return false;
							}
							b.reboToBo(b.reBoard);

						}

					}
				}
			}

			if (nextPlayer == 1 && b.board[m][n] < 0)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						to.x = j;
						to.y = i;
						players[nextPlayer].onMove(nextPlayer, b, from, to);
						if (players[nextPlayer].canMove)
						{
							players[nextPlayer].Move(b, from, to);
							if (!players[nextPlayer].isKingEaten(nextPlayer, b))
							{
								b.pawnChange = true;
								return false;
							}
							b.reboToBo(b.reBoard);

						}

					}
				}
			}

		}

	}
	b.pawnChange = true;
	return true;
}

GameManager::GameManager()
{
	current_player = 0;
	undo = 0;

}

GameManager::~GameManager()
{
}
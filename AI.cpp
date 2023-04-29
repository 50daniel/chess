#include"AI.h"
#include"board.h"

AIplayer::AIplayer()
{
	for (int i = 0; i < 1000; i++)
	{
		AIfrom[i].x = 0;
		AIfrom[i].y = 0;
		AIto[i].x = 0;
		AIto[i].y = 0;
	}
	AIcount = 0;
}

AIplayer::~AIplayer()
{
}

void AIplayer::randenMove(Board& b)
{

	for (int i = 0; i < 1000; i++)
	{
		AIfrom[i].x = 9;
		AIfrom[i].y = 9;
		AIto[i].x = 9;
		AIto[i].y = 9;
	}
	AIcount = 0;
	//b.pawnChange = false;
	//int nextPlayer = (current_player + 1) % 2;
	for (int m = 0; m < 8; m++)
	{
		for (int n = 0; n < 8; n++)
		{
			Position from, to;
			from.x = m;
			from.y = n;

			if (b.board[m][n] < 0)
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						to.x = j;
						to.y = i;
						onMove(1, b, from, to);
						if (canMove)
						{
							AIfrom[AIcount] = from;
							AIto[AIcount++] = to;

						}

					}
				}
			}

		}
	}
	if (!isKingEaten(1, b))
	{
		srand(time(NULL));
		int x = rand() % AIcount;
		Move(b, AIfrom[x], AIto[x]);
	}
	else
	{
		while (isKingEaten(1, b))
		{
			srand(time(NULL));
			int x = rand() % AIcount;
			Move(b, AIfrom[x], AIto[x]);
			if (isKingEaten(1, b))
			{
				b.reboToBo(b.reBoard);
			}

		}
	}
	//b.pawnChange = true;

}

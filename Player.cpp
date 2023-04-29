#include"Player.h"
#include"Pos.h"
#include<string>
Player::Player()
{
	canMove = 1;

}

void Player::onMove(int curr, Board& b, Position fromPos, Position toPos)
{
	canMove = 1;

	if (fromPos.x < 0 || fromPos.x > 7 || fromPos.y < 0 || fromPos.y >7 || toPos.x < 0 || toPos.x>7 || toPos.y < 0 || toPos.y>7)
	{
		canMove = false;
		//cout << "cannot move\n";
		return;
	}
	if (fromPos.x == toPos.x && fromPos.y == toPos.y)
	{
		canMove = false;
		//cout << "cannot move\n";
		return;
	}

	if (curr == 0) //玩家1 使用正數棋子
	{

		if (b.board[fromPos.x][fromPos.y] > 0 && b.board[toPos.x][toPos.y] <= 0)//原始座標是正數，終點座標不是正數，可移動
		{
			int tmp_x;
			int tmp_y;
			switch (b.board[fromPos.x][fromPos.y])//判斷棋種
			{
			case 1://城堡

				if (fromPos.x == toPos.x)//x軸一樣
				{
					int min = toPos.y, max = fromPos.y;
					if (fromPos.y < toPos.y)
					{
						min = fromPos.y;
						max = toPos.y;
					}
					for (int i = min + 1; i < max; i++)
					{
						if (b.board[fromPos.x][i] != 0)
						{
							canMove = false;
						}
					}
				}
				else if (fromPos.y == toPos.y) //y軸一樣
				{
					int min = toPos.x, max = fromPos.x;
					if (fromPos.x < toPos.x)
					{
						min = fromPos.x;
						max = toPos.x;
					}
					for (int i = min + 1; i < max; i++)
					{

						if (b.board[i][fromPos.y] != 0)
						{
							canMove = false;
						}
					}
				}
				else
				{
					canMove = false;
				}
				if (canMove)
				{

					if (fromPos.x == 0)
					{
						b.rookMove00 = true;
					}
					else if (fromPos.x == 7)
					{
						b.rookMove70 = true;
					}
				}
				break;
			case 2://馬
				tmp_x = abs(fromPos.x - toPos.x);
				tmp_y = abs(fromPos.y - toPos.y);
				if ((tmp_x == 2 && tmp_y == 1) || (tmp_x == 1 && tmp_y == 2)) {
					break;
				}
				else {
					canMove = false;
					break;
				}
			case 3://主教
				if (abs(fromPos.x - toPos.x) == abs(fromPos.y - toPos.y))
				{
					if ((toPos.x - fromPos.x) * (toPos.y - fromPos.y) < 0) //斜率為負
					{
						if (toPos.x > fromPos.x) //from左上 to右下
						{
							for (int i = 1; i < toPos.x - fromPos.x; i++)
							{
								if (b.board[fromPos.x + i][fromPos.y - i] != 0)
								{
									canMove = false;
								}
							}
						}
						else   //from右下 to左上
						{
							for (int i = 1; i < toPos.y - fromPos.y; i++)
							{

								if (b.board[fromPos.x - i][fromPos.y + i] != 0)
								{
									canMove = false;
								}
							}

						}
					}
					else  //斜率為正
					{
						if (toPos.x > fromPos.x) //from左下 to右上
						{

							for (int i = 1; i < toPos.x - fromPos.x; i++)
							{

								if (b.board[fromPos.x + i][fromPos.y + i] != 0)
								{
									canMove = false;
								}
							}
						}
						else   //from右上  to左下
						{
							for (int i = 1; i < fromPos.y - toPos.y; i++)
							{

								if (b.board[fromPos.x - i][fromPos.y - i] != 0)
								{
									canMove = false;
								}
							}

						}
					}
				}
				else
				{
					canMove = false;
				}
				break;
			case 4://皇后

				if (fromPos.x == toPos.x)//x軸一樣
				{
					int min = toPos.y, max = fromPos.y;
					if (fromPos.y < toPos.y)
					{
						min = fromPos.y;
						max = toPos.y;
					}
					for (int i = min + 1; i < max; i++)
					{
						if (b.board[fromPos.x][i] != 0)
						{
							canMove = false;
						}
					}
					if (b.board[toPos.x][toPos.y] > 0)
					{
						canMove = false;
					}
				}
				else if (fromPos.y == toPos.y) //y軸一樣
				{
					int min = toPos.x, max = fromPos.x;
					if (fromPos.x < toPos.x)
					{
						min = fromPos.x;
						max = toPos.x;
					}
					for (int i = min + 1; i < max; i++)
					{

						if (b.board[i][fromPos.y] != 0)
						{
							canMove = false;
						}
					}
					if (b.board[toPos.x][toPos.y] > 0)
					{
						canMove = false;
					}
				}
				//					以上是跟城堡一樣，以下是跟主教一樣

				else if (abs(fromPos.x - toPos.x) == abs(fromPos.y - toPos.y))
				{
					if ((toPos.x - fromPos.x) * (toPos.y - fromPos.y) < 0) //斜率為負
					{
						if (toPos.x > fromPos.x) //from左上 to右下
						{

							for (int i = 1; i < toPos.x - fromPos.x; i++)
							{

								if (b.board[fromPos.x + i][fromPos.y - i] != 0)
								{
									canMove = false;
								}
							}
						}
						else   //from右下 to左上
						{
							for (int i = 1; i < toPos.y - fromPos.y; i++)
							{

								if (b.board[fromPos.x - i][fromPos.y + i] != 0)
								{
									canMove = false;
								}
							}

						}

					}
					else  //斜率為正
					{
						if (toPos.x > fromPos.x) //from左下 to右上
						{

							for (int i = 1; i < toPos.x - fromPos.x; i++)
							{

								if (b.board[fromPos.x + i][fromPos.y + i] != 0)
								{
									canMove = false;
								}
							}
						}
						else   //from右上  to左下
						{
							for (int i = 1; i < fromPos.y - toPos.y; i++)
							{

								if (b.board[fromPos.x - i][fromPos.y - i] != 0)
								{
									canMove = false;
								}
							}

						}
					}

				}
				else
				{
					canMove = false;

				}
				break;
			case 5://國王
				tmp_x = abs(fromPos.x - toPos.x);
				tmp_y = abs(fromPos.y - toPos.y);
				if ((tmp_x == 0 && tmp_y == 1) || (tmp_x == 1 && tmp_y == 0) || (tmp_x == 1 && tmp_y == 1)) {
					if (b.kingMoveB)
					{

					}
					b.kingMoveB = true;
					break;
				}
				else {
					if (!b.rookMove70 && !b.kingMoveB && b.board[fromPos.x + 1][fromPos.y] == 0 && b.board[fromPos.x + 2][fromPos.y] == 0 && !isKingEaten(curr, b))
					{
						if (fromPos.x + 2 == toPos.x && fromPos.y == toPos.y)
						{
							Position tmpPos;

							for (int k = 1; k <= 2; k++)
							{
								tmpPos.x = fromPos.x + k;
								tmpPos.y = fromPos.y;
								Move(b, fromPos, tmpPos);
								if (isKingEaten(curr, b))
								{
									canMove = false;
									break;
								}
								b.reboToBo(b.reBoard);
							}
							b.Castling = true;
							break;
						}
					}

					if (!b.rookMove00 && !b.kingMoveB && b.board[fromPos.x - 1][fromPos.y] == 0 && b.board[fromPos.x - 2][fromPos.y] == 0 && !isKingEaten(curr, b))
					{
						if (fromPos.x - 2 == toPos.x && fromPos.y == toPos.y)
						{
							Position tmpPos;

							for (int k = 1; k <= 2; k++)
							{
								tmpPos.x = fromPos.x - k;
								tmpPos.y = fromPos.y;
								Move(b, fromPos, tmpPos);
								if (isKingEaten(curr, b))
								{
									canMove = false;
									break;
								}
								b.reboToBo(b.reBoard);
							}
							b.Castling = true;
							break;
						}
					}

					canMove = false;
					break;
				}
			case 6://小兵
				tmp_y = abs(fromPos.y - toPos.y);
				tmp_x = abs(fromPos.x - toPos.x);
				{bool canTwo = false;
				if (fromPos.x == toPos.x && fromPos.y + 1 == toPos.y && b.board[toPos.x][toPos.y] < 0)
				{
					canMove = false;
					break;
				}
				if (b.canPassant && b.passant.x == toPos.x && b.passant.y == toPos.y && tmp_x == 1 && (toPos.y - fromPos.y) == 1)
				{
					b.board[toPos.x][toPos.y - 1] = 0;
					break;
				}
				if (tmp_x == 1 && (toPos.y - fromPos.y) == 1 && b.board[toPos.x][toPos.y] < 0)
				{
					break;
				}
				for (int i = 0; i < 8; i++)
				{
					if (fromPos.x == i && fromPos.y == 1)
						canTwo = true;
				}
				if (canTwo)
				{
					if (fromPos.x == toPos.x && toPos.y - fromPos.y == 2 && b.board[fromPos.x][fromPos.y + 1] == 0 && b.board[fromPos.x][fromPos.y + 2] == 0)
					{
						b.canPassant = true;
						b.passant.x = toPos.x;
						b.passant.y = toPos.y - 1;
						b.passCount = 0;
						break;
					}
					if (fromPos.x == toPos.x && toPos.y - fromPos.y == 1 && b.board[toPos.x][toPos.y] == 0)
					{
						break;
					}
					else {
						canMove = false;
						break;
					}
				}
				else
				{
					if (fromPos.x == toPos.x && (toPos.y - fromPos.y) == 1)
					{
						break;
					}
					else
					{
						canMove = false;
						break;
					}
				}}
				break;
			default:
				canMove = false;
				break;
			}
		}
		else
		{
			canMove = false;
		}
	}

	if (curr == 1)
	{
		if (b.board[fromPos.x][fromPos.y] < 0 && b.board[toPos.x][toPos.y] >= 0)//原始座標是負數，終點座標不是負數，可移動
		{
			int tmp_x;
			int tmp_y;
			switch (b.board[fromPos.x][fromPos.y])//判斷棋種
			{
			case -1://城堡

				if (fromPos.x == toPos.x)//x軸一樣
				{
					int min = toPos.y, max = fromPos.y;
					if (fromPos.y < toPos.y)
					{
						min = fromPos.y;
						max = toPos.y;
					}
					for (int i = min + 1; i < max; i++)
					{
						if (b.board[fromPos.x][i] != 0)
						{
							canMove = false;
						}
					}
				}
				else if (fromPos.y == toPos.y) //y軸一樣
				{
					int min = toPos.x, max = fromPos.x;
					if (fromPos.x < toPos.x)
					{
						min = fromPos.x;
						max = toPos.x;
					}
					for (int i = min + 1; i < max; i++)
					{

						if (b.board[i][fromPos.y] != 0)
						{
							canMove = false;
						}
					}
				}
				else
				{
					canMove = false;
				}
				if (canMove)
				{

					if (fromPos.x == 0)
					{
						b.rookMove07 = true;
					}
					else if (fromPos.x == 7)
					{
						b.rookMove77 = true;
					}
				}

				break;
			case -2://馬
				tmp_x = abs(fromPos.x - toPos.x);
				tmp_y = abs(fromPos.y - toPos.y);
				if ((tmp_x == 2 && tmp_y == 1) || (tmp_x == 1 && tmp_y == 2)) {
					break;
				}
				else {
					canMove = false;
					break;
				}
			case -3://主教
				if (abs(fromPos.x - toPos.x) == abs(fromPos.y - toPos.y))
				{
					if ((toPos.x - fromPos.x) * (toPos.y - fromPos.y) < 0) //斜率為負
					{
						if (toPos.x > fromPos.x) //from左上 to右下
						{

							for (int i = 1; i < toPos.x - fromPos.x; i++)
							{

								if (b.board[fromPos.x + i][fromPos.y - i] != 0)
								{
									canMove = false;
								}
							}
						}
						else   //from右下 to左上
						{
							for (int i = 1; i < toPos.y - fromPos.y; i++)
							{

								if (b.board[fromPos.x - i][fromPos.y + i] != 0)
								{
									canMove = false;
								}
							}

						}
					}
					else  //斜率為正
					{
						if (toPos.x > fromPos.x) //from左下 to右上
						{

							for (int i = 1; i < toPos.x - fromPos.x; i++)
							{

								if (b.board[fromPos.x + i][fromPos.y + i] != 0)
								{
									canMove = false;
								}
							}
						}
						else   //from右上  to左下
						{
							for (int i = 1; i < fromPos.y - toPos.y; i++)
							{

								if (b.board[fromPos.x - i][fromPos.y - i] != 0)
								{
									canMove = false;
								}
							}

						}
					}
				}
				else
				{
					canMove = false;
				}
				break;
			case -4://皇后

				if (fromPos.x == toPos.x)//x軸一樣
				{
					int min = toPos.y, max = fromPos.y;
					if (fromPos.y < toPos.y)
					{
						min = fromPos.y;
						max = toPos.y;
					}
					for (int i = min + 1; i < max; i++)
					{
						if (b.board[fromPos.x][i] != 0)
						{
							canMove = false;
						}
					}
				}
				else if (fromPos.y == toPos.y) //y軸一樣
				{
					int min = toPos.x, max = fromPos.x;
					if (fromPos.x < toPos.x)
					{
						min = fromPos.x;
						max = toPos.x;
					}
					for (int i = min + 1; i < max; i++)
					{

						if (b.board[i][fromPos.y] != 0)
						{
							canMove = false;
						}
					}
				}
				//					以上是跟城堡一樣，以下是跟主教一樣

				else if (abs(fromPos.x - toPos.x) == abs(fromPos.y - toPos.y))
				{
					if ((toPos.x - fromPos.x) * (toPos.y - fromPos.y) < 0) //斜率為負
					{
						if (toPos.x > fromPos.x) //from左上 to右下
						{

							for (int i = 1; i < toPos.x - fromPos.x; i++)
							{

								if (b.board[fromPos.x + i][fromPos.y - i] != 0)
								{
									canMove = false;
								}
							}
						}
						else   //from右下 to左上
						{
							for (int i = 1; i < toPos.y - fromPos.y; i++)
							{

								if (b.board[fromPos.x - i][fromPos.y + i] != 0)
								{
									canMove = false;
								}
							}

						}

					}
					else  //斜率為正
					{
						if (toPos.x > fromPos.x) //from左下 to右上
						{

							for (int i = 1; i < toPos.x - fromPos.x; i++)
							{

								if (b.board[fromPos.x + i][fromPos.y + i] != 0)
								{
									canMove = false;
								}
							}
						}
						else   //from右上  to左下
						{
							for (int i = 1; i < fromPos.y - toPos.y; i++)
							{

								if (b.board[fromPos.x - i][fromPos.y - i] != 0)
								{
									canMove = false;
								}
							}

						}
					}

				}
				else
				{
					canMove = false;

				}
				break;
			case -5://國王
				tmp_x = abs(fromPos.x - toPos.x);
				tmp_y = abs(fromPos.y - toPos.y);
				if ((tmp_x == 0 && tmp_y == 1) || (tmp_x == 1 && tmp_y == 0) || (tmp_x == 1 && tmp_y == 1)) {
					b.kingMoveW = true;
					break;
				}
				else {
					if (!b.rookMove77 && !b.kingMoveW && b.board[fromPos.x + 1][fromPos.y] == 0 && b.board[fromPos.x + 2][fromPos.y] == 0 && !isKingEaten(curr, b))
					{
						if (fromPos.x + 2 == toPos.x && fromPos.y == toPos.y)
						{
							Position tmpPos;

							for (int k = 1; k <= 2; k++)
							{
								tmpPos.x = fromPos.x + k;
								tmpPos.y = fromPos.y;
								Move(b, fromPos, tmpPos);
								if (isKingEaten(curr, b))
								{
									canMove = false;
									break;
								}
								b.reboToBo(b.reBoard);
							}
							b.Castling = true;
							break;
						}
					}

					if (!b.rookMove07 && !b.kingMoveW && b.board[fromPos.x - 1][fromPos.y] == 0 && b.board[fromPos.x - 2][fromPos.y] == 0 && !isKingEaten(curr, b))
					{
						if (fromPos.x - 2 == toPos.x && fromPos.y == toPos.y)
						{
							Position tmpPos;

							for (int k = 1; k <= 2; k++)
							{
								tmpPos.x = fromPos.x - k;
								tmpPos.y = fromPos.y;
								Move(b, fromPos, tmpPos);
								if (isKingEaten(curr, b))
								{
									canMove = false;
									break;
								}
								b.reboToBo(b.reBoard);
							}
							b.Castling = true;
							break;
						}
					}


					canMove = false;
					break;
				}
			case -6://小兵
				tmp_y = abs(fromPos.y - toPos.y);
				tmp_x = abs(fromPos.x - toPos.x);
				{bool canTwo = false;
				if (fromPos.x == toPos.x && fromPos.y - 1 == toPos.y && b.board[toPos.x][toPos.y] != 0)
				{
					canMove = false;
					break;
				}
				if (b.canPassant && b.passant.x == toPos.x && b.passant.y == toPos.y && tmp_x == 1 && (fromPos.y - toPos.y) == 1)
				{
					b.board[toPos.x][toPos.y + 1] = 0;
					break;
				}
				if (tmp_x == 1 && (fromPos.y - toPos.y) == 1 && b.board[toPos.x][toPos.y] > 0)
				{
					break;
				}

				for (int i = 0; i < 8; i++)
				{
					if (fromPos.x == i && fromPos.y == 6)
						canTwo = true;
				}
				if (canTwo)
				{
					if (fromPos.x == toPos.x && fromPos.y - toPos.y == 2 && b.board[fromPos.x][fromPos.y - 1] == 0 && b.board[fromPos.x][fromPos.y - 2] == 0)
					{

						b.canPassant = true;
						b.passant.x = toPos.x;
						b.passant.y = toPos.y + 1;
						b.passCount = 0;
						break;
					}
					if (fromPos.x == toPos.x && (fromPos.y - toPos.y) == 1 && b.board[toPos.x][toPos.y] == 0)
					{
						break;
					}
					else {
						canMove = false;
						break;
					}
				}
				else
				{
					if (fromPos.x == toPos.x && (fromPos.y - toPos.y) == 1)
					{
						break;
					}
					else
					{
						canMove = false;
						break;
					}
				}}
				break;
			default:
				canMove = false;
				break;
			}
		}
		else
		{
			canMove = false;
		}
	}

	//	if (canMove)
	//	{
	//		for (int i = 0; i < 8; i++)
	//		{
	//			for (int j = 0; j < 8; j++)
	//			{
	//				b.reBoard[i][j] = b.board[i][j];
	//			}
	//		}
	//		
	//		cout << "can move" << endl;
	//		b.board[toPos.x][toPos.y] = b.board[fromPos.x][fromPos.y];
	//		b.board[fromPos.x][fromPos.y] = 0;
	//	}
}

bool Player::isKingEaten(int curr, Board& b)
{
	Position kingPos;

	if (curr == 0)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (b.board[i][j] == 5)
				{
					kingPos.x = i;
					kingPos.y = j;
				}
			}

		}

		for (int i = kingPos.x + 1; i < 8; i++) //x正方向
		{
			if (b.board[i][kingPos.y] == 0)
			{
				continue;
			}
			else if (b.board[i][kingPos.y] != -1 && b.board[i][kingPos.y] != -4)
			{
				break;
			}
			else
				return true;
		}
		for (int i = kingPos.x - 1; i >= 0; i--)	//x負方向
		{
			if (b.board[i][kingPos.y] == 0)
			{
				continue;
			}
			if (b.board[i][kingPos.y] != -1 && b.board[i][kingPos.y] != -4)
			{
				break;
			}
			else
				return true;
		}
		for (int i = kingPos.y + 1; i < 8; i++)		//y正方向
		{
			if (b.board[kingPos.x][i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x][i] != -1 && b.board[kingPos.x][i] != -4)
			{
				break;
			}
			else
				return true;
		}
		for (int i = kingPos.y - 1; i >= 0; i--)		//y負方向
		{
			if (b.board[kingPos.x][i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x][i] != -1 && b.board[kingPos.x][i] != -4)
			{
				break;
			}
			else
				return true;

		}

		for (int i = 1; i < 8; i++)		//右上方向
		{
			if (b.board[kingPos.x + i][kingPos.y + i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x + i][kingPos.y + i] != -3 && b.board[kingPos.x + i][kingPos.y + i] != -4 || kingPos.x + i > 7 || kingPos.y + i > 7)
			{
				break;
			}
			else if (b.board[kingPos.x + i][kingPos.y + i] == -3 || b.board[kingPos.x + i][kingPos.y + i] == -4)
			{
				return true;
			}
		}
		if (b.board[kingPos.x + 1][kingPos.y + 1] == -6)
		{
			return true;
		}
		for (int i = 1; i < 8; i++)		//左上方向
		{
			if (b.board[kingPos.x - i][kingPos.y + i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x - i][kingPos.y + i] != -3 && b.board[kingPos.x - i][kingPos.y + i] != -4 || kingPos.x - i < 0 || kingPos.y + i > 7)
			{
				break;
			}
			else if (b.board[kingPos.x - i][kingPos.y + i] == -3 || b.board[kingPos.x - i][kingPos.y + i] == -4)
			{
				return true;
			}
		}
		if (b.board[kingPos.x - 1][kingPos.y + 1] == -6)
		{
			return true;
		}
		for (int i = 1; i < 8; i++)		//右下方向
		{
			if (b.board[kingPos.x + i][kingPos.y - i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x + i][kingPos.y - i] != -3 && b.board[kingPos.x + i][kingPos.y - i] != -4 || kingPos.x + i > 7 || kingPos.y - i < 0)
			{
				break;
			}
			else if (b.board[kingPos.x + i][kingPos.y - i] == -3 || b.board[kingPos.x + i][kingPos.y - i] == -4)
			{
				return true;
			}
		}
		for (int i = 1; i < 8; i++)		//左下方向
		{
			if (b.board[kingPos.x - i][kingPos.y - i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x - i][kingPos.y - i] != -3 && b.board[kingPos.x - i][kingPos.y - i] != -4 || kingPos.x - i < 0 || kingPos.y - i < 0)
			{
				break;
			}
			else if (b.board[kingPos.x - i][kingPos.y - i] == -3 || b.board[kingPos.x - i][kingPos.y - i] == -4)
			{
				return true;
			}
		}
		Position tmp;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{

				if (abs(kingPos.x - j) == 2 && abs(kingPos.y - i) == 1 || abs(kingPos.x - j) == 1 && abs(kingPos.y - i) == 2)
				{
					if (b.board[j][i] == -2)
					{
						return true;
					}
				}
				if (abs(kingPos.x - j) <= 1 && abs(kingPos.y - i) <= 1)
				{
					if (b.board[j][i] == -5)
					{
						return true;
					}
				}
			}
		}


	}
	if (curr == 1)
	{
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (b.board[i][j] == -5)
				{
					kingPos.x = i;
					kingPos.y = j;
				}
			}

		}

		for (int i = kingPos.x + 1; i < 8; i++) //x正方向
		{
			if (b.board[i][kingPos.y] == 0)
			{
				continue;
			}
			else if (b.board[i][kingPos.y] != 1 && b.board[i][kingPos.y] != 4)
			{
				break;
			}
			else
				return true;
		}
		for (int i = kingPos.x - 1; i >= 0; i--)	//x負方向
		{
			if (b.board[i][kingPos.y] == 0)
			{
				continue;
			}
			if (b.board[i][kingPos.y] != 1 && b.board[i][kingPos.y] != 4)
			{
				break;
			}
			else
				return true;
		}
		for (int i = kingPos.y + 1; i < 8; i++)		//y正方向
		{
			if (b.board[kingPos.x][i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x][i] != 1 && b.board[kingPos.x][i] != 4)
			{
				break;
			}
			else
				return true;
		}
		for (int i = kingPos.y - 1; i >= 0; i--)		//y負方向
		{
			if (b.board[kingPos.x][i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x][i] != 1 && b.board[kingPos.x][i] != 4)
			{
				break;
			}
			else
				return true;

		}

		for (int i = 1; i < 8; i++)		//右上方向
		{
			if (b.board[kingPos.x + i][kingPos.y + i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x + i][kingPos.y + i] != 3 && b.board[kingPos.x + i][kingPos.y + i] != 4 || kingPos.x + i > 7 || kingPos.y + i > 7)
			{
				break;
			}
			else if (b.board[kingPos.x + i][kingPos.y + i] == 3 || b.board[kingPos.x + i][kingPos.y + i] == 4)
			{
				return true;
			}
		}
		if (b.board[kingPos.x + 1][kingPos.y - 1] == 6)
		{
			return true;
		}
		for (int i = 1; i < 8; i++)		//左上方向
		{
			if (b.board[kingPos.x - i][kingPos.y + i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x - i][kingPos.y + i] != 3 && b.board[kingPos.x - i][kingPos.y + i] != 4 || kingPos.x - i < 0 || kingPos.y + i > 7)
			{
				break;
			}
			else if (b.board[kingPos.x - i][kingPos.y + i] == 3 || b.board[kingPos.x - i][kingPos.y + i] == 4)
			{
				return true;
			}
		}
		if (b.board[kingPos.x - 1][kingPos.y - 1] == 6)
		{
			return true;
		}
		for (int i = 1; i < 8; i++)		//右下方向
		{
			if (b.board[kingPos.x + i][kingPos.y - i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x + i][kingPos.y - i] != 3 && b.board[kingPos.x + i][kingPos.y - i] != 4 || kingPos.x + i > 7 || kingPos.y - i < 0)
			{
				break;
			}
			else if (b.board[kingPos.x + i][kingPos.y - i] == 3 || b.board[kingPos.x + i][kingPos.y - i] == 4)
			{
				return true;
			}
		}
		for (int i = 1; i < 8; i++)		//左下方向
		{
			if (b.board[kingPos.x - i][kingPos.y - i] == 0)
			{
				continue;
			}
			else if (b.board[kingPos.x - i][kingPos.y - i] != 3 && b.board[kingPos.x - i][kingPos.y - i] != 4 || kingPos.x - i < 0 || kingPos.y - i < 0)
			{
				break;
			}
			else if (b.board[kingPos.x - i][kingPos.y - i] == 3 || b.board[kingPos.x - i][kingPos.y - i] == 4)
			{
				return true;
			}
		}
		Position tmp;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{

				if (abs(kingPos.x - j) == 2 && abs(kingPos.y - i) == 1 || abs(kingPos.x - j) == 1 && abs(kingPos.y - i) == 2)
				{
					if (b.board[j][i] == 2)
					{
						return true;
					}
				}
				if (abs(kingPos.x - j) <= 1 && abs(kingPos.y - i) <= 1)
				{
					if (b.board[j][i] == 5)
					{
						return true;
					}
				}
			}
		}

	}
	return false;
}

void Player::Move(Board& b, Position fromPos, Position toPos)
{

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			b.reBoard[i][j] = b.board[i][j];
		}
	}
	//cout << "can move" << endl;
	b.board[toPos.x][toPos.y] = b.board[fromPos.x][fromPos.y];
	b.board[fromPos.x][fromPos.y] = 0;

	if (b.Castling)
	{
		b.Castling = false;
		Position tmpPos1, tmpPos2;
		if (toPos.x == 6)
		{
			tmpPos1.x = toPos.x + 1;
			tmpPos1.y = toPos.y;
			tmpPos2.x = toPos.x - 1;
			tmpPos2.y = toPos.y;
			Move(b, tmpPos1, tmpPos2);
		}
		if (toPos.x == 2)
		{
			tmpPos1.x = toPos.x - 2;
			tmpPos1.y = toPos.y;
			tmpPos2.x = toPos.x + 1;
			tmpPos2.y = toPos.y;
			Move(b, tmpPos1, tmpPos2);
		}
	}

	if ((b.board[toPos.x][toPos.y] == 6 && toPos.y == 7) && b.pawnChange)
	{
		string str;
		int ch = 0;
		cout << "Choose what you want to change : Queen 、Bishop、Rook 、Knight\n";
		cout << "input 1:Rook、2:Knight、3:Bishop、4:Queen";
		while (cin >> ch)
		{
			getline(cin, str);
			if (ch == 1)
			{
				b.board[toPos.x][toPos.y] = 1;
				break;
			}
			else if (ch == 2)
			{
				b.board[toPos.x][toPos.y] = 2;
				break;
			}
			else if (ch == 3)
			{
				b.board[toPos.x][toPos.y] = 3;
				break;
			}
			else if (ch == 4)
			{
				b.board[toPos.x][toPos.y] = 4;
				break;
			}
			else
			{
				cout << "輸入錯誤 請重新輸入:";
			}

		}

	}
	else if (b.board[toPos.x][toPos.y] == -6 && toPos.y == 0 && b.pawnChange)
	{
		string str;
		int ch = 0;
		cout << "Choose what you want to change : Queen 、Bishop、Rook 、Knight\n";
		cout << "input 1:Rook、2:Knight、3:Bishop、4:Queen";
		while (cin >> ch)
		{
			getline(cin, str);
			if (ch == 1)
			{
				b.board[toPos.x][toPos.y] = -1;
				break;
			}
			else if (ch == 2)
			{
				b.board[toPos.x][toPos.y] = -2;
				break;
			}
			else if (ch == 3)
			{
				b.board[toPos.x][toPos.y] = -3;
				break;
			}
			else if (ch == 4)
			{
				b.board[toPos.x][toPos.y] = -4;
				break;
			}
			else
			{
				cout << "輸入錯誤 請重新輸入:";
			}

		}
	}


}

Player::~Player()
{
}
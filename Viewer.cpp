#include"Viewer.h"
#include <ctime>
#include <conio.h>
#include<iostream>

using   namespace   std;

#include <ctime> 

void   Delay(int   time)//time*1000為秒數 
{
	clock_t   now = clock();

	while (clock() - now < time);
}



Viewer::Viewer()
{
	is_time_zero = false;
	Player1_time = 100;
	Player2_time = 100;
}

Viewer::~Viewer()
{
}

void Viewer::print(int curr, const Board& b)
{
	string output[8][8];
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (b.board[i][j] == -1) {
				output[i][j] = "RW";
			}
			else if (b.board[i][j] == -2) {
				output[i][j] = "NW";
			}
			else if (b.board[i][j] == -3) {
				output[i][j] = "BW";
			}
			else if (b.board[i][j] == -4) {
				output[i][j] = "QW";
			}
			else if (b.board[i][j] == -5) {
				output[i][j] = "KW";
			}
			else if (b.board[i][j] == -6) {
				output[i][j] = "PW";
			}
			else if (b.board[i][j] == 0) {
				output[i][j] = "  ";
			}
			else if (b.board[i][j] == 1) {
				output[i][j] = "RB";
			}
			else if (b.board[i][j] == 2) {
				output[i][j] = "NB";
			}
			else if (b.board[i][j] == 3) {
				output[i][j] = "BB";
			}
			else if (b.board[i][j] == 4) {
				output[i][j] = "QB";
			}
			else if (b.board[i][j] == 5) {
				output[i][j] = "KB";
			}
			else if (b.board[i][j] == 6) {
				output[i][j] = "PB";
			}
		}
	}


	cout << "  ";
	for (int i = 0; i < 8; i++)
		cout << "|  " << char(i + 97) << " ";
	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		cout << 8 - i << " ";
		for (int j = 0; j < 8; j++)
		{

			cout << "| " << output[j][7 - i] << " ";

		}
		cout << "| " << 8 - i << endl;
		cout << "---------------------------------------------" << endl;
	}
	cout << "  ";
	for (int i = 0; i < 8; i++)
		cout << "|  " << char(i + 97) << " ";
	cout << endl;

	if (curr % 2 == 1)
	{
		cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
		cout << "輪到玩家2(上面):\n";
	}
	if (curr % 2 == 0)
	{
		cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
		cout << "輪到玩家1(下面):\n";
	}
}

void Viewer::print_time(int curr, const Board& b)
{
	clock_t startT, endT;
	startT = clock();
	endT = clock();

	while (!_kbhit()) {
		double timeFrame = (double)(endT - startT) / CLOCKS_PER_SEC;
		// Execute the game loop
		if (timeFrame >= 1) {
			if (curr % 2 == 1)
				Player2_time--;
			else
				Player1_time--;
			startT = clock();
			system("cls");
			print(curr, b);
			std::cout << "Player1's time : " << Player1_time << "  Player2's time : " << Player2_time << endl;
			if (Player1_time <= 0) {
				system("cls");
				print_GG(1, b, curr);
				break;
			}
			else if (Player2_time <= 0) {
				system("cls");
				print_GG(0, b, curr);
				break;
			}
		}
		endT = clock();
	}

}

void Viewer::view(Board& b)
{

}

void Viewer::print_GGAI(const Board& b, int curr)
{
}

void Viewer::print_GG(int winIs, const Board& b, int repl)
{
	cout << " _____  _____" << endl <<
		"/ ____|/ ____|" << endl <<
		"| |  __| |  __" << endl <<
		"| | |_ | | |_ |" << endl <<
		"| |__| | |__| |" << endl <<
		"|_____ | \_____|" << endl;
	is_time_zero = true;
	if (winIs == 1)
	{
		cout << "玩家2勝利!!" << endl;
	}
	if (winIs == 0)
	{
		cout << "玩家1勝利!!" << endl;;
	}
	cout << "輸入 1 遊戲結束，輸入 2 進行回放" << endl;
	int over = 0;
	cin >> over;
	if (over == 1)
	{
		exit(0);
	}
	if (over == 2)
	{
		system("cls");
		for (int k = 0; k < repl; k++)
		{
			string output[8][8];
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					if (b.rePlay[k][i][j] == -1) {
						output[i][j] = "RW";
					}
					else if (b.rePlay[k][i][j] == -2) {
						output[i][j] = "NW";
					}
					else if (b.rePlay[k][i][j] == -3) {
						output[i][j] = "BW";
					}
					else if (b.rePlay[k][i][j] == -4) {
						output[i][j] = "QW";
					}
					else if (b.rePlay[k][i][j] == -5) {
						output[i][j] = "KW";
					}
					else if (b.rePlay[k][i][j] == -6) {
						output[i][j] = "PW";
					}
					else if (b.rePlay[k][i][j] == 0) {
						output[i][j] = "  ";
					}
					else if (b.rePlay[k][i][j] == 1) {
						output[i][j] = "RB";
					}
					else if (b.rePlay[k][i][j] == 2) {
						output[i][j] = "NB";
					}
					else if (b.rePlay[k][i][j] == 3) {
						output[i][j] = "BB";
					}
					else if (b.rePlay[k][i][j] == 4) {
						output[i][j] = "QB";
					}
					else if (b.rePlay[k][i][j] == 5) {
						output[i][j] = "KB";
					}
					else if (b.rePlay[k][i][j] == 6) {
						output[i][j] = "PB";
					}
				}
			}

			cout << "  ";
			for (int i = 0; i < 8; i++)
				cout << "|  " << char(i + 97) << " ";
			cout << endl;
			for (int i = 0; i < 8; i++)
			{
				cout << 8 - i << " ";
				for (int j = 0; j < 8; j++)
				{

					cout << "| " << output[j][7 - i] << " ";

				}
				cout << "| " << 8 - i << endl;
				cout << "---------------------------------------------" << endl;
			}
			cout << "  ";
			for (int i = 0; i < 8; i++)
				cout << "|  " << char(i + 97) << " ";
			cout << endl;

			Delay(1000);   //延時1秒
			system("cls");
		}
		cout << "遊戲結束";
		/*for (int k = 0; k < curr ; k++)
		{
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					b.undo[curr][i][j];
				}

			}
		}*/

	}
}

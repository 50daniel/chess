#include<iostream>
#include<string>
#include <fstream>
#include <ctime>
#include <conio.h>
#include"GameManager.h"
#include"Pos.h"
using namespace std;

int curr = -1, repl = 0, cou = -1;
GameManager game;
string from, to;
string s;
bool validateFileName(string name) {
	if (name.size() > 10) {
		return false;
	}
	return true;
}

void playAI() {
	cou++;
	curr++;
	while (getline(cin, from))
	{

		if (from == "Save" || from == "save") {
			cout << "Enter file name" << endl;
			string fileName;
			getline(cin, fileName);
			while (validateFileName(fileName) == false) {
				cout << "Invalid format. Please re-enter." << endl;
				getline(cin, fileName);
			}

			fileName = fileName + ".txt";
			ofstream fout(fileName);
			if (fout.is_open()) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						fout << game.board.board[i][j] << " ";
					}
				}
				fout << cou << " " << game.viewer.Player1_time << " " << game.viewer.Player2_time;
				fout.close();
			}
			else {
				cout << "Unable to open file";
			}
			system("cls");
			cout << "Saved!" << endl;
			game.viewer.print(curr, game.board);
			//		game.viewer.print_time(curr, game.board);

		}

		else if (from == "Surrender" || from == "surrender") {
			system("cls");
			cou++;
			//	game.current_player = curr % 2;
			game.viewer.print_GG(game.current_player, game.board, repl);

			break;
		}
		else if (from == "undo" || from == "Undo")
		{
			if (cou >= 1)
			{
				game.canRedo = true;
				game.undo++;
				cou = cou - 1;
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						game.board.board[i][j] = game.board.undo[cou][i][j];
						game.board.reBoard[i][j] = game.board.undo[cou - 1][i][j];
						game.board.rePlay[repl][i][j] = game.board.board[i][j];
					}

				}
				repl++;
				system("cls");
				game.viewer.print(curr, game.board);
				//game.viewer.print_time(curr, game.board);
				//if (game.current_player == 1)
				//{
				//	cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
				//	cout << "輪到玩家2(上面):";
				//}
				if (game.current_player == 0)
				{
					cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
					cout << "輪到玩家1(下面):";
				}
			}
			else
			{
				cout << "不能undo 請重新輸入\n";
			}

		}
		else if (from == "redo" || from == "Redo")
		{
			if (game.undo > 0 && game.canRedo)
			{
				game.undo--;
				cou = cou + 1;
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						game.board.board[i][j] = game.board.undo[cou][i][j];
						game.board.reBoard[i][j] = game.board.undo[cou - 1][i][j];
						game.board.rePlay[repl][i][j] = game.board.board[i][j];
					}

				}
				repl++;
				system("cls");
				game.viewer.print(curr, game.board);
				//				game.viewer.print_time(curr, game.board);
								//if (game.current_player == 1)
								//{
								//	cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
								//	cout << "輪到玩家2(上面):";
								//}
				if (game.current_player == 0)
				{
					cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
					cout << "輪到玩家1(下面):";
				}
			}
			else
			{
				cout << "不能redo 請重新輸入";
			}
		}
		else {
			Position fromPos, toPos;
			fromPos.x = from[0] - 97;
			fromPos.y = from[1] - 49;
			toPos.x = from[3] - 97;
			toPos.y = from[4] - 49;
			if (fromPos.x < 0 || fromPos.x>7 || fromPos.y < 0 || fromPos.y>7 || toPos.x < 0 || toPos.x>7 || toPos.y < 0 || toPos.y>7)
			{
				continue;
			}

			game.canRedo = false;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{

					game.board.undo[cou][i][j] = game.board.board[i][j];
					game.board.rePlay[repl][i][j] = game.board.board[i][j];
				}

			}
			repl++;
			game.current_player = curr % 2;

			game.players[game.current_player].onMove(game.current_player, game.board, fromPos, toPos); //判斷是否可移動
			if (game.players[game.current_player].canMove)
			{
				game.players[game.current_player].Move(game.board, fromPos, toPos);//移動	

			}
			if (game.gameOver(game.board))
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						game.board.undo[cou + 1][i][j] = game.board.board[i][j];
						game.board.rePlay[repl][i][j] = game.board.board[i][j];
					}
				}
				repl++;
				//cout << "將死!! 玩家" << game.current_player+1 << "輸了 遊戲結束!!";
				system("cls");
				game.viewer.print_GG(game.current_player, game.board, repl);
				break;
			}

			if (game.players->isKingEaten(game.current_player, game.board))		//如果 將軍
			{
				game.board.reboToBo(game.board.reBoard); //將棋盤回復


				cout << "將軍" << endl << "玩家" << game.current_player + 1 << " 請重新輸入:";
				continue;
			}
			if (game.players[game.current_player].canMove == 0)
			{

				cout << "移動不合法! 玩家" << game.current_player + 1 << " 請重新輸入:";
				continue;
			}
			cou++;
			game.canRedo = false;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					game.board.undo[cou][i][j] = game.board.board[i][j];
					game.board.rePlay[repl][i][j] = game.board.board[i][j];
				}

			}
			repl++;
			game.current_player = curr % 2;
			if (game.board.canPassant)
			{
				game.board.passCount++;
			}
			if (game.board.passCount == 2)
			{
				game.board.canPassant = false;
			}

			system("cls");

			game.viewer.print(curr, game.board);
			//			game.viewer.print_time(curr, game.board);
			game.AI.randenMove(game.board);
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					//					game.board.board[i][j] = game.board.undo[curr][i][j];
					//					game.board.reBoard[i][j] = game.board.undo[curr - 1][i][j];
					game.board.rePlay[repl][i][j] = game.board.board[i][j];
				}

			}
			repl++;

			system("cls");
			game.viewer.print(curr, game.board);
			//			game.viewer.print_time(curr, game.board);
		}
		if (game.viewer.is_time_zero)
			break;


	}
}





void play(int corrent) {
	curr++;
	while (getline(cin, from))
	{

		if (from == "Save" || from == "save") {
			cout << "Enter file name" << endl;
			string fileName;
			getline(cin, fileName);
			while (validateFileName(fileName) == false) {
				cout << "Invalid format. Please re-enter." << endl;
				getline(cin, fileName);
			}
			fileName = fileName + ".txt";
			ofstream fout(fileName);
			if (fout.is_open()) {
				for (int i = 0; i < 8; i++) {
					for (int j = 0; j < 8; j++) {
						fout << game.board.board[i][j] << " ";
					}
				}
				fout << curr << " " << game.viewer.Player1_time << " " << game.viewer.Player2_time;
				fout.close();
			}
			else {
				cout << "Unable to open file";
			}
			system("cls");
			cout << "Saved!" << endl;
			game.viewer.print(curr, game.board);
			game.viewer.print_time(curr, game.board);

		}

		else if (from == "Surrender" || from == "surrender") {
			system("cls");
			curr++;
			game.current_player = curr % 2;
			game.viewer.print_GG(game.current_player, game.board, repl);

			break;
		}
		else if (from == "undo" || from == "Undo")
		{
			if (curr >= 2)
			{
				game.canRedo = true;
				game.undo++;
				curr = curr - 2;
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						game.board.board[i][j] = game.board.undo[curr][i][j];
						game.board.reBoard[i][j] = game.board.undo[curr - 1][i][j];
						game.board.rePlay[repl][i][j] = game.board.board[i][j];
					}

				}
				repl++;
				system("cls");
				game.viewer.print(curr, game.board);
				game.viewer.print_time(curr, game.board);
				if (game.current_player == 1)
				{
					cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
					cout << "輪到玩家2(上面):";
				}
				if (game.current_player == 0)
				{
					cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
					cout << "輪到玩家1(下面):";
				}
			}
			else
			{
				cout << "不能undo 請重新輸入\n";
			}

		}
		else if (from == "redo" || from == "Redo")
		{
			if (game.undo > 0 && game.canRedo)
			{
				game.undo--;
				curr = curr + 2;
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						game.board.board[i][j] = game.board.undo[curr][i][j];
						game.board.reBoard[i][j] = game.board.undo[curr - 1][i][j];
						game.board.rePlay[repl][i][j] = game.board.board[i][j];
					}

				}
				repl++;
				system("cls");
				game.viewer.print(curr, game.board);
				game.viewer.print_time(curr, game.board);
				if (game.current_player == 1)
				{
					cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
					cout << "輪到玩家2(上面):";
				}
				if (game.current_player == 0)
				{
					cout << "可用指令 Save, Undo , Redo , Surrender" << endl;
					cout << "輪到玩家1(下面):";
				}
			}
			else
			{
				cout << "不能redo 請重新輸入";
			}
		}
		else {
			Position fromPos, toPos;
			fromPos.x = from[0] - 97;
			fromPos.y = from[1] - 49;
			toPos.x = from[3] - 97;
			toPos.y = from[4] - 49;
			if (fromPos.x < 0 || fromPos.x>7 || fromPos.y < 0 || fromPos.y>7 || toPos.x < 0 || toPos.x>7 || toPos.y < 0 || toPos.y>7)
			{
				continue;
			}

			game.canRedo = false;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{

					game.board.undo[curr][i][j] = game.board.board[i][j];
					game.board.rePlay[repl][i][j] = game.board.board[i][j];
				}

			}
			repl++;
			game.current_player = curr % 2;

			game.players[game.current_player].onMove(game.current_player, game.board, fromPos, toPos); //判斷是否可移動
			if (game.players[game.current_player].canMove)
			{
				game.players[game.current_player].Move(game.board, fromPos, toPos);//移動	

			}
			if (game.gameOver(game.board))
			{
				for (int i = 0; i < 8; i++)
				{
					for (int j = 0; j < 8; j++)
					{
						game.board.undo[curr + 1][i][j] = game.board.board[i][j];
						game.board.rePlay[repl][i][j] = game.board.board[i][j];
					}
				}
				repl++;
				//cout << "將死!! 玩家" << game.current_player+1 << "輸了 遊戲結束!!";
				system("cls");
				game.viewer.print_GG(game.current_player, game.board, repl);
				break;
			}

			if (game.players->isKingEaten(game.current_player, game.board))		//如果 將軍
			{
				game.board.reboToBo(game.board.reBoard); //將棋盤回復


				cout << "將軍" << endl << "玩家" << game.current_player + 1 << " 請重新輸入:";
				continue;
			}
			if (game.players[game.current_player].canMove == 0)
			{

				cout << "移動不合法! 玩家" << game.current_player + 1 << " 請重新輸入:";
				continue;
			}
			curr++;
			game.canRedo = false;
			for (int i = 0; i < 8; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					game.board.undo[curr][i][j] = game.board.board[i][j];
					game.board.rePlay[repl][i][j] = game.board.board[i][j];
				}

			}
			repl++;
			game.current_player = curr % 2;
			if (game.board.canPassant)
			{
				game.board.passCount++;
			}
			if (game.board.passCount == 2)
			{
				game.board.canPassant = false;
			}

			system("cls");

			game.viewer.print(curr, game.board);
			game.viewer.print_time(curr, game.board);

		}
		if (game.viewer.is_time_zero)
			break;
	}
}
int main()
{



	cout << "   _____ _    _ ______  _____ _____ \n  / ____| |  | |  ____|/ ____/ ____| \n | |    | |__| | |__  | (___| (___  \n | |    |  __  |  __|  \\___  \\___ \\ \n | |____| |  | | |____ ____) |___) | \n  \\_____|_|  |_|______|_____/_____/ \n" << endl;
	cout << "西洋棋" << endl;
	cout << "Enter one of the available commands: " << endl;
	cout << "Start, Load " << endl;
	cin >> s;

	if (s == "Load" || s == "load") {
		system("cls");
		getline(cin, s);
		cout << "Enter file name" << endl;
		string fileName;
		getline(cin, fileName);
		// VALIDATE FILE NAME 
		while (validateFileName(fileName) == false) {
			cout << "Invalid format. Please re-enter." << endl;
			getline(cin, fileName);
		}
		fileName = fileName + ".txt";
		ifstream input(fileName);


		if (input.is_open()) {
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					input >> game.board.board[i][j];
				}
			}


			input >> curr >> game.viewer.Player1_time >> game.viewer.Player2_time;

			system("cls");
			cout << "Loaded!" << endl;

			game.viewer.print(curr, game.board);
			game.viewer.print_time(curr, game.board);
			curr--;
			play(curr);

		}
		else {
			cout << "No such file!!!" << endl;
		}
	}

	else if (s == "Start" || s == "start")
	{
		string ss;
		cout << "AI or Player:";

		getline(cin, s);
		cin >> ss;
		if (ss == "AI" || ss == "ai")
		{
			system("cls");
			getline(cin, s);

			game.viewer.print(curr, game.board);
			game.viewer.print_time(curr, game.board);
			playAI();
		}
		else if (ss == "Player" || ss == "player")
		{
			system("cls");
			getline(cin, s);
			int tmp;
			cout << "選擇玩家先攻(1,2) :" << endl;
			cin >> tmp;
			getline(cin, s);
			if (tmp == 1) {
				curr++;
				game.viewer.print(curr, game.board);
				game.viewer.print_time(curr, game.board);
				curr--;
				play(curr);
			}
			else if (tmp == 2) {
				curr += 2;
				game.viewer.print(curr, game.board);
				game.viewer.print_time(curr, game.board);
				curr--;
				play(curr);
			}
		}



	}
	//遊戲結束畫面


}
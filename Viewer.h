#pragma once
#include<iostream>
#include<string>
#include"board.h"
using namespace std;

class Viewer
{
public:
	int Player1_time , Player2_time;
	bool is_time_zero ;
	Viewer();
	~Viewer();
	void print(int curr,const Board& b);
	void print_time(int curr,const Board& b);
	void print_GG(int winIs, const Board& b,int repl);
	void print_GGAI(const Board& b, int repl);
	void prin_draw(const Board& b, int repl);
	void view(Board& b);
private:

};


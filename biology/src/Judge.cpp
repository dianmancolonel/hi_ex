//
// Created by 34329 on 2025/9/13.
//

#include "Judge.h"
#include <string>
#include <iostream>

#include "../include/ConstVal.h"

bool Judge::CheckInput(std::string a, std::string b) {
    if ((a == "11" || a == "10" || (a.size() == 1 && a[0] >= '1' && a[0] <= '9'))
    && (b.size() == 1 && b[0] >= 'a' && b[0] <= 'k')) return true;
    return false;
}

bool Judge::CheckChessLegal(Chess chess, Board &board) {
    int x = chess.GetPosition().row;
    int y = chess.GetPosition().col;

    auto boardStatu = board.GetBoard();
    if (boardStatu[x][y] == -1) return true;
    return false;
}

int Judge::CheckPre() {
    std::string op = "-1";
    while (true)
    {
        std::cout << "Input first hand: [0:Human],[1:Ai]" << std::endl;
        std::cin >> op;
        if (op == "0" || op == "1") break;
    }

    return op[0] - '0';
}

bool Judge::CheckIsRepentance(Board &board) {
    std::string op = "-1";
    board.PrintBoard();
    while (true){
        std::cout << "是否确定悔棋(y, n)" << std::endl;

        std::cout << "#:";
        std::cin >> op;

        //判断输入是否正确
        if (op == "y" || op == "n") break;      //输入正确, 退出循环
        board.PrintBoard();
        std::cout << "[err] 输入错误, 请重新输入" << std::endl; //输入错误, 提示
    }

    if (op == "y") return true;
    return false;

}


bool Judge::CheckIsWin(std::vector<std::vector<int>> boardStatu) {
	std::vector<std::vector<bool>> BoardFlag(11, std::vector<bool>(11, 0));
    bool WinFlag = false;   //胜利标记

    for (int i = 0; i < 11; i++)
    {
        if (WinFlag == true)break;
        if (boardStatu[0][i] == Red) {
            BoardFlag[0][i] = true;
            WinFlag = CheckDFS_R(0, i, boardStatu, BoardFlag);
        } //红方查询
    }
    for (int i = 0; i < 11; i++)
    {
        if (WinFlag == true)break;
        if (boardStatu[i][0] == Blue) {
            BoardFlag[i][0] = true;
            WinFlag = CheckDFS_B(i, 0, boardStatu, BoardFlag);
        } //蓝方查询
    }
    return WinFlag;
}

bool Judge::CheckDFS_R(int x, int y, std::vector<std::vector<int>> board_statu, std::vector<std::vector<bool>> Boardflag)
{
	if (x == 10)return true; //找到通路
	bool Tmpflag = false;
	if (x - 1 >= 0 && board_statu[x - 1][y] == Red&&!Boardflag[x-1][y]) //左上角
	{
		Boardflag[x - 1][y] = true;
		Tmpflag = (Tmpflag || CheckDFS_R(x - 1, y, board_statu, Boardflag));
	}
	if (x - 1 >= 0 && y + 1 <11 && board_statu[x - 1][y + 1] == Red && !Boardflag[x - 1][y + 1]) //右上角
	{
		Boardflag[x - 1][y + 1] = true;
		Tmpflag = (Tmpflag || CheckDFS_R(x - 1, y + 1, board_statu, Boardflag));
	}
	if (y - 1 >= 0 && board_statu[x][y - 1] == Red && !Boardflag[x][y - 1]) //左
	{
		Boardflag[x][y - 1] = true;
		Tmpflag = (Tmpflag || CheckDFS_R(x, y - 1, board_statu, Boardflag));
	}
	if (y + 1 < 11 && board_statu[x][y + 1] == Red && !Boardflag[x][y + 1]) //右
	{
		Boardflag[x][y + 1] = true;
		Tmpflag = (Tmpflag || CheckDFS_R(x, y + 1, board_statu, Boardflag));
	}
	if (x + 1 < 11 && y - 1 >= 0 && board_statu[x + 1][y - 1] == Red && !Boardflag[x + 1][y - 1]) //左下角
	{
		Boardflag[x + 1][y - 1] = true;
		Tmpflag = (Tmpflag || CheckDFS_R(x + 1, y - 1, board_statu, Boardflag));
	}
	if (x + 1 < 11 && board_statu[x + 1][y] == Red && !Boardflag[x + 1][y]) //右下角
	{
		Boardflag[x + 1][y] = true;
		Tmpflag = (Tmpflag || CheckDFS_R(x + 1, y, board_statu, Boardflag));
	}
	return Tmpflag;
}


bool Judge::CheckDFS_B(int x, int y, std::vector<std::vector<int>> board_statu, std::vector<std::vector<bool>> Boardflag)
{
	if (y == 10)return true; //找到通路
	bool Tmpflag = false;
	if (x - 1 >= 0 && board_statu[x - 1][y] == Blue && !Boardflag[x - 1][y]) //左上角
	{
		Boardflag[x - 1][y] = true;
		Tmpflag = (Tmpflag || CheckDFS_B(x - 1, y, board_statu, Boardflag));
	}
	if (x - 1 >= 0 && y + 1 < 11 && board_statu[x - 1][y + 1] == Blue && !Boardflag[x - 1][y + 1]) //右上角
	{
		Boardflag[x - 1][y + 1] = true;
		Tmpflag = (Tmpflag || CheckDFS_B(x - 1, y + 1, board_statu, Boardflag));
	}
	if (y - 1 >= 0 && board_statu[x][y - 1] == Blue && !Boardflag[x][y - 1]) //左
	{
		Boardflag[x][y - 1] = true;
		Tmpflag = (Tmpflag || CheckDFS_B(x, y - 1, board_statu, Boardflag));
	}
	if (y + 1 < 11 && board_statu[x][y + 1] == Blue && !Boardflag[x][y + 1]) //右
	{
		Boardflag[x][y + 1] = true;
		Tmpflag = (Tmpflag || CheckDFS_B(x, y + 1, board_statu, Boardflag));
	}
	if (x + 1 < 11 && y - 1 >= 0 && board_statu[x + 1][y - 1] == Blue && !Boardflag[x + 1][y - 1]) //左下角
	{
		Boardflag[x + 1][y - 1] = true;
		Tmpflag = (Tmpflag || CheckDFS_B(x + 1, y - 1, board_statu, Boardflag));
	}
	if (x + 1 < 11 && board_statu[x + 1][y] == Blue && !Boardflag[x + 1][y]) //右下角
	{
		Boardflag[x + 1][y] = true;
		Tmpflag = (Tmpflag || CheckDFS_B(x + 1, y, board_statu, Boardflag));
	}
	return Tmpflag;
}
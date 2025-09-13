//
// Created by 34329 on 2025/9/13.
//

#include "Board.h"

#include <iostream>
#include <string>
#include <vector>

#include "Chess.h"
#include "../include/ConstVal.h"

using namespace std;

void Board::InitBoard() {
    boardStatu.assign(11, std::vector<int>(11, -1));
    chessOrder.clear();
}

bool Board::IsEmpty() {
    return chessOrder.empty();
}

std::vector<std::vector<int>>& Board::GetBoard() {
    return boardStatu;
}

std::vector<Chess>& Board::GetChesses() {
    return chessOrder;
}

void Board::RepentanceChess() {
    auto t_chesses = GetChesses();
    auto t = t_chesses.back();
    t_chesses.pop_back();
    boardStatu[t.GetPosition().row][t.GetPosition().col] = -1;
}

void Board::AddChess(Chess chess) {
    boardStatu[chess.GetPosition().row][chess.GetPosition().col] = chess.GetColor();
    auto& t_chesses = GetChesses();
    t_chesses.push_back(chess);
}

void Board::PrintBoard() {
    cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
    cout << "┃   \033[31mA B C D E F G H I J K \033[0m          ┃" << endl;
    for (int i = 0; i < 11; i++)
    {
        cout << "┃";
        for (int k = 0; k < i; k++) cout << " ";

        //输出棋盘左边的数字
        int L = i + 1;
        if (L < 10){
            cout << ' ';
        }
        cout << "\033[34m" << L << "\033[0m" << ' ';

        //输出棋盘本体
        for (int j = 0; j < 11; j++) {
            if (boardStatu[i][j] == Red)
                display.ShowRedStr	("R ");
            else if (boardStatu[i][j] == Blue)
                display.ShowBlueStr("B ");
            else
                display.ShowGreyStr("_ ");
        }
        for (int k = 0; k < 11 - i - 1; k++) {
            cout << " ";
        }
        cout << "┃";
        cout << endl;
    }
    cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
}


//
// Created by 34329 on 2025/9/13.
//

#include "Human.h"
#include "Chess.h"
#include <iostream>

using namespace std;

Chess Human::GiveChess(Board &board) {
    board.PrintBoard();
    Chess chess;
    chess.SetColor(getColor());
    Position p;
    string x, y;
    while (true) {
        cout << "Input Your Position: (Example: [6 f])" << endl;
        cin >> x >> y;
        if (x[0] >= 'a' && x[0] <= 'k') swap(x, y);
        if (judge.CheckInput(x, y))  //如果输入合法
        {
            //输入的转为坐标
            if (x == "11") p.row = 10;
            else if (x == "10") p.row = 9;
            else p.row = x[0] - '1';
            p.col = y[0] - 'a';

            chess.SetPosition(p);

            if (judge.CheckChessLegal(chess, board))
                break;
            board.PrintBoard();
            cout << "Error, the position is occupied, reput please" << endl;
        }
        else
        {
            board.PrintBoard();
            cout << "Error, input unexpected, reput please" << endl;
        }
    }
    return chess;
}
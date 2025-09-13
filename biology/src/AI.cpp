//
// Created by 34329 on 2025/9/13.
//

#include "AI.h"
#include <iostream>

using namespace std;

Chess AI::GiveChess(Board &board) {
    board.PrintBoard();
    Chess chess;
    chess.SetColor(getColor());
    ab.init(board);
    int index = ab.getbestMove();
    Position p(index / 11, index % 11);
    chess.SetPosition(p);
    return chess;
}

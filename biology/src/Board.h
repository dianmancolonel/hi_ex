//
// Created by 34329 on 2025/9/13.
//

#ifndef HI_EX_BOARD_H
#define HI_EX_BOARD_H
#include <vector>
#include "Chess.h"
#include "Display.h"

class Board {
public:
    void InitBoard();
    void PrintBoard();
    void AddChess(Chess chess);
    void RepentanceChess();
    bool IsEmpty();
    int rounds(){return (int)chessOrder.size();}
    std::vector<std::vector<int>>& GetBoard();
    std::vector<Chess>& GetChesses();
    Display display;

private:
    Chess last_chess;
    std::vector<Chess> chessOrder;
    std::vector<std::vector<int>> boardStatu;
};

#endif //HI_EX_BOARD_H


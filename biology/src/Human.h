//
// Created by 34329 on 2025/9/13.
//

#ifndef HI_EX_HUMAN_H
#define HI_EX_HUMAN_H
#include "Board.h"
#include "Player.h"
#include "Judge.h"


class Human: public Player{
    public:
    Human(const std::string &name, const int color) : Player(name, color) {};
    Chess GiveChess(Board &board);
    Judge judge;
};


#endif //HI_EX_HUMAN_H
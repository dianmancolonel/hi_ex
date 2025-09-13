//
// Created by 34329 on 2025/9/13.
//

#ifndef HI_EX_AI_H
#define HI_EX_AI_H
#include <string>

#include "AlpheBeta.h"
#include "Board.h"
#include "Judge.h"
#include "Player.h"


class AI: public Player {
    public:
    AI(const std::string &name, const int color) : Player(name, color) {};
    Chess GiveChess(Board &board);
    Judge judge;
    AB ab;
};


#endif //HI_EX_AI_H
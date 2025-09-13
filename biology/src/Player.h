//
// Created by 34329 on 2025/9/13.
//

#ifndef HI_EX_PLAYER_H
#define HI_EX_PLAYER_H

#include <string>

#include "Board.h"
#include "Chess.h"

class Player {
public:
    virtual ~Player() = default;

    Player(const std::string& name, int color);

    std::string getName();
    int getColor();

    void setName(std::string name);
    void setColor(int color);

    virtual Chess GiveChess(Board& board) = 0;

private:
    std::string name;
    int color;
};

#endif //HI_EX_PLAYER_H




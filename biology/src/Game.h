//
// Created by 34329 on 2025/9/13.
//


#ifndef HI_EX_GAME_H
#define HI_EX_GAME_H

#include "Player.h"
#include "AI.h"
#include "Human.h"
#include "Chess.h"
#include "Judge.h"

class Game {
public:
    void InitGame();
    void StartGame();
    void EndGame();

    Game();

    bool isRepentance = false;
    bool isWin = false;
    bool isRestart = false;

    Player* current_player{};
    Player* ai_player{};
    Player* human_player{};
    Board board;
    Judge judge;
    Chess chess;
    Display display;
private:

    AI ai;
    Human human;

};

#endif //HI_EX_GAME_H


//
// Created by 34329 on 2025/9/13.
//

#include "Game.h"

#include <iostream>
#include <ostream>


void Game::InitGame() {
    isRepentance = false;
    isWin = false;
    isRestart = false;
    current_player = nullptr;
    board.InitBoard();
    human.setName("Human");
    ai.setName("AI");
}

Game::Game() : ai("AI", -1), human("Human", -1) {
    InitGame();
}


void Game::StartGame() {
    this->human_player = &human;
    this->ai_player = &ai;

    switch (judge.CheckPre()) {
        case 0:
            this->current_player = &human;
            this->human_player->setColor(Red);
            this->ai_player->setColor(Blue);
            break;
        case 1:
            this->current_player = &ai;
            this->ai_player->setColor(Red);
            this->human_player->setColor(Blue);
            break;

        default:
            break;
    }
    //先后手判断

    while (!isWin) {
        // if (!board.IsEmpty()) {
        //     isRepentance = judge.CheckIsRepentance(board);
        //     if (isRepentance) {
        //         board.RepentanceChess();
        //         isRepentance = false;
        //         current_player = current_player == ai_player?human_player:ai_player;
        //         continue;
        //     }
        // }
        //悔棋判断
        if (current_player == ai_player) {std::cout << "AI" << std::endl;}
        else {std::cout << "Human" << std::endl;}

        //board.PrintBoard();

        chess = current_player->GiveChess(board);
        board.AddChess(chess);
        std::cout << "size of Chess: " << board.GetChesses().size() << std::endl;
        isWin = judge.CheckIsWin(board.GetBoard());
        if (isWin) {
            if (current_player->getColor() == Red) display.ShowRedWin();  //显示红方胜利
            else display.ShowBlueWin();
        }

        current_player = current_player == ai_player?human_player:ai_player;//交换
    }

}

void Game::EndGame() {

}

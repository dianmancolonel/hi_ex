//
// Created by 34329 on 2025/9/13.
//

#ifndef HI_EX_JUDGE_H
#define HI_EX_JUDGE_H
#include "Board.h"

class Judge {
public:
    bool CheckInput(std::string, std::string);
    bool CheckChessLegal(Chess, Board &board);
    bool CheckIsWin(std::vector<std::vector<int>>);
    bool CheckIsRepentance(Board &board);
    int CheckPre();
    bool CheckDFS_R(int, int ,std::vector<std::vector<int>>, std::vector<std::vector<bool>>);
    bool CheckDFS_B(int, int ,std::vector<std::vector<int>>, std::vector<std::vector<bool>>);
};

#endif //HI_EX_JUDGE_H


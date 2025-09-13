//
// Created by 34329 on 2025/9/13.
//

#ifndef HI_EX_DISPLAY_H
#define HI_EX_DISPLAY_H
#include "Chess.h"
#include <string>

class Display {
    public:
    void ShowRedWin();					//打印红棋胜
    void ShowBlueWin();					//打印蓝棋胜
    void ShowChessPoint(Chess chess);	//打印棋子的坐标
    void ShowRedStr(std::string s);			//打印红色的字
    void ShowBlueStr(std::string s);			//打印蓝色的字
    void ShowGreyStr(std::string s);			//打印灰色的字
};


#endif //HI_EX_DISPLAY_H
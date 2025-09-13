//
// Created by 34329 on 2025/9/13.
//

#ifndef HI_EX_ALPHEBETA_H
#define HI_EX_ALPHEBETA_H


#include "Evaluate.h"
#include <unordered_map>
#include "Board.h"


using namespace std;

struct extended
{
    extended(int idx, int total):idx(idx),totalPotential(total){}
    int idx;
    int totalPotential;
};

class ABNode
{
public:
    ABNode(ABNode* parent, size_t nChildren);
    ~ABNode();

    unsigned short nChildren{ 0 };  //子节点的数量
    unsigned short index{ 0 };      //下棋下标
    int winner{ EMPTY };            //胜利者
    int profit{ 0 };                //收益

    ABNode* parent;                   //父节点
    ABNode* children[121];    //所有子节点
};


class AB
{
public:
    AB() = default;
    ~AB() = default;
    void init(Board& board);

    int getbestMove();
    int alpha_beta(int depth, int previousBest, int currentColour);
    static int position_to_index(int x, int y);                                //将(x,y)转化为index

    int rounds;
    int status[121];                                                          //uf为临时棋盘
    int colorAI{ EMPTY };                                                      //AI的颜色
    Evaluate* ev;                                                               //估值函数
    unordered_map<string, int> valuemap;
};


#endif //HI_EX_ALPHEBETA_H
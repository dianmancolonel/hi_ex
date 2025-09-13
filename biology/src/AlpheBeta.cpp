//
// Created by 34329 on 2025/9/13.
//

#include "AlpheBeta.h"
#include <iostream>

using namespace std;

int total_round = 0;

ABNode::ABNode(ABNode* parent, size_t nChildren)
    : parent(parent), nChildren((unsigned short)nChildren){}

ABNode::~ABNode()
{
    for (int i = 0; i < 121; ++i)
        delete children[i];
}

void AB::init(Board& board)
{
    this->rounds = board.rounds();
    this->colorAI = board.rounds() & 1;
    for (int i = 0; i < 11; i++)
        for (int j = 0; j < 11; j++)
            status[i * 11 + j] = board.GetBoard()[i][j];

}

int AB::position_to_index(int x, int y)
{
    return (x - 1) * 11 + (y - 1);
}


//自定义一个random函数
static auto random = [](double end) {
    return (int)(end * rand() / (RAND_MAX + 1.0));
};

int AB::getbestMove()
{
    if (0 == rounds) //如果为先手, 下棋盘中央
        return position_to_index(6, 6);
    if (1 == rounds && status[60]!=EMPTY) //如果为后手,且对方第一手为6，6 下棋5，6
        return position_to_index(5, 6);

    int bestvalue = colorAI == Red ? -MAXNUM : MAXNUM;
    int bestidx = -1;
    total_round++;
    //进入alphaBeta剪枝，选取最优节点
    for (int i = 0; i < 121; i++)
    {
        if (status[i] != EMPTY)continue;//如果该点没被下，就继续，否则退出
        status[i] = colorAI;
        int value = alpha_beta(1, bestvalue, colorAI == Red ? Blue : Red);
        status[i] = EMPTY;//恢复棋盘

        if (colorAI == Red && value > bestvalue)
            //如果当前颜色为红色，并且估值比之前的最好估值大，则替换最好估值，并记录当前点所在的行和列
        {
            bestvalue = value;
            bestidx = i;
        }
        else if (colorAI == Blue && value < bestvalue)
            //如果当前颜色为蓝色，并且估值比之前的最好估值小，则替换最好估值，并记录当前点所在的行和列
        {
            bestvalue = value;
            bestidx = i;
        }

    }
    cout << "AI position: " << bestidx / 11 + 1 << ',' <<(char) (bestidx % 11 + 'a') << endl;
    cout << "Expected val: " << bestvalue << endl;
    return bestidx;
}

string boardToString(int board[])
{
    string sb = "";
    for (int i = 0; i < 121; i++)
    {
        sb += board[i] + '0';
    }
    return sb;
}

int AB::alpha_beta(int depth, int previousBest, int currentColor)
{
    if (depth == MAX_DEPTH)
    {
        string s = boardToString(status);
        if (valuemap.count(s))return valuemap[s];
        ev = new Evaluate(status);
        int temp = ev->getValue();//调用评估函数
        valuemap[s] = temp;
        delete ev;
        return temp;
    }

    int bestvalue = currentColor == Red ? -MAXNUM : MAXNUM;
    vector<extended> ex;
    ev = new Evaluate(status);
    for (int i = 0; i < 121; i++)
    {
        if (status[i] != EMPTY)continue;
        extended e(i, ev->getChessTotalPotential(i/11+1,i%11+1));
        ex.push_back(e);
    }
    delete ev;
    sort(ex.begin(), ex.end(), [](extended a, extended b) {
        return a.totalPotential < b.totalPotential;
        });
    for (int i = 0;i<5 && i<ex.size();i++)
    {
        status[ex[i].idx] = currentColor;//把选中的点设置为当前颜色
        int value = alpha_beta(depth + 1, bestvalue, currentColor == Red ? Blue : Red);//递归调用自己
        status[ex[i].idx] = EMPTY;//把之前填充的颜色清空

        if (currentColor == Red && value > bestvalue) bestvalue = value;//红色棋子得到比自己估值大的就替换
        else if (currentColor == Blue && value < bestvalue) bestvalue = value;//蓝色棋子得到比自己估值小的就替换
        if ((currentColor == Red && bestvalue > previousBest) || (currentColor == Blue && bestvalue < previousBest)) return bestvalue;
    }

    if (bestvalue == -MAXNUM || bestvalue == MAXNUM)
    {
        string s = boardToString(status);
        if (valuemap.count(s))bestvalue = valuemap[s];
        else
        {
            ev = new Evaluate(status);
            bestvalue = ev->getValue();//调用评估函数
            delete ev;
        }
    }
    return bestvalue;

}
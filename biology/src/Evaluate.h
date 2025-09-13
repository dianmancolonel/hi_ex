//
// Created by 34329 on 2025/9/13.
//

#ifndef HI_EX_EVALUATE_H
#define HI_EX_EVALUATE_H

#include <set>
#include <queue>
#include <algorithm>
#include <vector>
#include <bitset>
#include "..\include/ConstVal.h"

using namespace std;

class evNode
{
public:
    evNode() = default;
    evNode(int x, int y);//建立估值操作结点
    ~evNode() = default;
    set<int> redNeighbours;
    set<int> blueNeighbours;
    int x;//行
    int y;//列
};


class Evaluate
{
public:


    Evaluate(int status[]);
    ~Evaluate();

    int xyToPostion(int i, int j);
    void initializeDistances();
    void processNeighbours(int nowidx, int i, int j);
    void computeDistance(int arrs[13][13], int red_b[13][13], int i);
    void computeTotalPotential();
    void detectThreats();
    void computeMobilityAndPotential();

    long long getValue();//评估函数
    int getChessTotalPotential(int x, int y);//棋子总潜力
    bool isCriticalPoint(int x, int y) const;// 检查是否是关键点
    int getboardTotalPotential();//棋盘总潜力

    int board[13 * 13] = { 0 };
    evNode* evboard[13 * 13];
    int redA[13][13];
    int redB[13][13];
    int blueA[13][13];
    int blueB[13][13];
    int total[13][13];
    vector<vector<int>> positionWeights;
    int redThreats = 0;     // 红方威胁点数
    int blueThreats = 0;    // 蓝方威胁点数
    bitset<121> criticalPoints; // 关键点位置（11x11=121），使用 bitset
    int controlFactor = 0;  // 控制因子
    long long redPotential = BASE_VALUE;//红色潜力值
    long long bluePotential = BASE_VALUE;//蓝色潜力值
    long long totalPotential = BASE_VALUE;// 总潜力值
    long long redMobility = 0;//红色的进攻机动性
    long long blueMobility = 0;//蓝色的进攻机动性
};

#endif //HI_EX_EVALUATE_H
//
// Created by 34329 on 2025/9/13.
//

#include "Evaluate.h"

#include <cstring>

int dx[] = { -1,1,-12,-13,12,13 };
int dx1[] = { -1,-1,0,0,1,1 };
int dy1[] = { 0,1,-1,1,-1,0 };

evNode::evNode(int x, int y) :x(x), y(y) {}

Evaluate::~Evaluate()
{
    for (int i = 0; i < 13 * 13; i++)
    {
        delete evboard[i];
    }
}

int Evaluate::xyToPostion(int i, int j) {
    return i * 13 + j;
}


Evaluate::Evaluate(int status[]) {
    redThreats = 0;
    blueThreats = 0;
    criticalPoints.reset();  // 重置关键点位图

    memset(board, 0, sizeof(board));
    for (int i = 1; i <= 11; i++) {
        board[i] = 1;
        board[156 + i] = 1;
        board[i * 13] = 2;
        board[12 + i * 13] = 2;
    }
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 11; j++) {
            board[xyToPostion(i + 1, j + 1)] = status[i * 11 + j] + 1;
        }
    }

    // 初始化估值节点
    for (int i = 0; i < 13; i++) {
        for (int j = 0; j < 13; j++) {
            evboard[xyToPostion(i, j)] = new evNode(i, j);
        }
    }

    // 初始化各节点邻居
    for (int i = 1; i <= 11; i++) {
        for (int j = 1; j <= 11; j++) {
            int nowidx = xyToPostion(i, j);
            if (board[nowidx] == 0) {
                processNeighbours(nowidx, i, j);
            }
        }
    }

    // 初始化双距离
    initializeDistances();

    // 计算红蓝双距离
    computeDistance(redA, redB, 0);  // redA & redB
    computeDistance(blueA, blueB, 2);  // blueA & blueB

    // 求各点总潜力
    computeTotalPotential();

    // 威胁检测
    detectThreats();

    // 求红蓝和总潜力
    computeMobilityAndPotential();
}

void Evaluate::processNeighbours(int nowidx, int i, int j) {
    // 红色邻居
    bool flag1[13 * 13] = {false};
    std::queue<int> q1;
    q1.push(nowidx);
    flag1[nowidx] = true;
    while (!q1.empty()) {
        int tempidx = q1.front();
        q1.pop();
        for (int i = 0; i < 6; i++) {
            int tx = tempidx / 13 + dx1[i];
            int ty = tempidx % 13 + dy1[i];
            int t = tx * 13 + ty;
            if (tx < 0 || tx > 12 || ty < 0 || ty > 12) continue;
            if (board[t] == 0 && t != nowidx) evboard[nowidx]->redNeighbours.insert(t);
            if (board[t] == 1 && !flag1[t]) {
                q1.push(t);
                flag1[t] = true;
            }
        }
    }

    // 蓝色邻居
    bool flag2[13 * 13] = {false};
    std::queue<int> q2;
    q2.push(nowidx);
    flag2[nowidx] = true;
    while (!q2.empty()) {
        int tempidx = q2.front();
        q2.pop();
        for (int i = 0; i < 6; i++) {
            int tx = tempidx / 13 + dx1[i];
            int ty = tempidx % 13 + dy1[i];
            int t = tx * 13 + ty;
            if (tx < 0 || tx > 12 || ty < 0 || ty > 12) continue;
            if (board[t] == 0 && t != nowidx) evboard[nowidx]->blueNeighbours.insert(t);
            if (board[t] == 2 && !flag2[t]) {
                q2.push(t);
                flag2[t] = true;
            }
        }
    }
}

void Evaluate::initializeDistances() {
    for (int i = 0; i <= 12; i++) {
        for (int j = 0; j <= 12; j++) {
            redA[i][j] = BASE_VALUE;
            redB[i][j] = BASE_VALUE;
            blueA[i][j] = -BASE_VALUE;
            blueB[i][j] = -BASE_VALUE;
        }
    }

    redA[0][0] = 0;
    redA[0][12] = 0;
    redB[12][0] = 0;
    redB[12][12] = 0;

    blueA[0][0] = 0;
    blueA[12][0] = 0;
    blueB[0][12] = 0;
    blueB[12][12] = 0;
}

void Evaluate::computeDistance(int distA[13][13], int distB[13][13], int targetColor) {
    bool found = true;
    while (found) {
        found = false;
        for (int i = 1; i <= 11; i++) {
            for (int j = 1; j <= 11; j++) {
                if (distA[i][j] != BASE_VALUE || board[xyToPostion(i, j)] != 0) continue;
                int min = BASE_VALUE;
                int secondMin = BASE_VALUE;
                for (auto& e : evboard[xyToPostion(i, j)]->redNeighbours) {
                    int number = distA[e / 13][e % 13];
                    if (number < secondMin) {
                        secondMin = number;
                        if (number < min) {
                            secondMin = min;
                            min = number;
                        }
                    }
                }
                if (secondMin < 100 && distA[i][j] != secondMin + 1) {
                    found = true;
                    distA[i][j] = secondMin + 1;
                }
            }
        }
    }

    found = true;
    while (found) {
        found = false;
        for (int i = 11; i >= 1; i--) {
            for (int j = 1; j <= 11; j++) {
                if (distB[i][j] != BASE_VALUE || board[xyToPostion(i, j)] != 0) continue;
                int min = BASE_VALUE;
                int secondMin = BASE_VALUE;
                for (auto& e : evboard[xyToPostion(i, j)]->redNeighbours) {
                    int number = distB[e / 13][e % 13];
                    if (number < secondMin) {
                        secondMin = number;
                        if (number < min) {
                            secondMin = min;
                            min = number;
                        }
                    }
                }
                if (secondMin < 100 && distB[i][j] != secondMin + 1) {
                    found = true;
                    distB[i][j] = secondMin + 1;
                }
            }
        }
    }
}

void Evaluate::computeTotalPotential() {
    for (int i = 1; i <= 11; i++) {
        for (int j = 1; j <= 11; j++) {
            total[i][j] = redA[i][j] + redB[i][j] + blueA[i][j] + blueB[i][j];
        }
    }
}

void Evaluate::detectThreats() {
    for (int i = 1; i <= 11; i++) {
        for (int j = 1; j <= 11; j++) {
            int pos = xyToPostion(i, j);
            if (board[pos] != 0) continue;  // 只检查空位

            // 红方威胁检测：红方双距离和=1表示只差一步就能连接
            if (redA[i][j] + redB[i][j] == 1) {
                redThreats++;
                criticalPoints.set((i - 1) * 11 + (j - 1));  // 标记为关键点
            }

            // 蓝方威胁检测
            if (blueA[i][j] + blueB[i][j] == 1) {
                blueThreats++;
                criticalPoints.set((i - 1) * 11 + (j - 1));
            }
        }
    }
}

void Evaluate::computeMobilityAndPotential() {
    for (int i = 1; i <= 11; i++) {
        for (int j = 1; j <= 11; j++) {
            if (board[xyToPostion(i, j)] == 0) {
                if (redA[i][j] + redB[i][j] < redPotential) {
                    redPotential = redA[i][j] + redB[i][j];
                    redMobility = 1;
                }
                else if (redA[i][j] + redB[i][j] == redPotential) {
                    redMobility++;
                }

                if (blueA[i][j] + blueB[i][j] < bluePotential) {
                    bluePotential = blueA[i][j] + blueB[i][j];
                    blueMobility = 1;
                }
                else if (blueA[i][j] + blueB[i][j] == bluePotential) {
                    blueMobility++;
                }

                if (total[i][j] < totalPotential) {
                    totalPotential = redA[i][j] + redB[i][j] + blueA[i][j] + blueB[i][j];
                }
            }
        }
    }
}


long long Evaluate::getValue()
{
    long long baseValue = (bluePotential - redPotential) - 10 * (blueMobility - redMobility);

    // 添加威胁值影响 - 高权重
    baseValue += blueThreats * 500;  // 蓝方威胁加分
    baseValue -= redThreats * 500;   // 红方威胁减分

    // 终局判断：当一方有威胁而另一方没有时直接返回极大值
    if (blueThreats > 0 && redThreats == 0) return MAXNUM;
    if (redThreats > 0 && blueThreats == 0) return -MAXNUM;

    return baseValue;
}

int Evaluate::getChessTotalPotential(int x, int y)
{
    return total[x][y];
}

int Evaluate::getboardTotalPotential()
{
    return totalPotential;
}

bool Evaluate::isCriticalPoint(int x, int y) const {
    if (x < 1 || x > 11 || y < 1 || y > 11) return false;
    return criticalPoints.test((x - 1) * 11 + (y - 1));
}
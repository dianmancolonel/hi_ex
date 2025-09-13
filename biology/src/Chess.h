//
// Created by 34329 on 2025/9/13.
//

#ifndef HI_EX_CHESS_H
#define HI_EX_CHESS_H

struct Position {
    int row;
    int col;
    Position(){row = -1, col = -1;};
    Position(int row, int col) : row(row), col(col) {}
};

class Chess {

public:
    Chess(Position position, int color);

    Chess();

    Position GetPosition();
    int GetColor();

    void SetPosition(Position position);
    void SetColor(int color);

private:
    Position position;
    int color;
};

#endif //HI_EX_CHESS_H


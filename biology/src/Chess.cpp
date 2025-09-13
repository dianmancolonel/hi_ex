//
// Created by 34329 on 2025/9/13.
//

#include "Chess.h"

Position Chess::GetPosition() {
    return position;
}

int Chess::GetColor() {
    return color;
}

void Chess::SetPosition(Position position) {
    this->position = position;
}

void Chess::SetColor(int color) {
    this->color = color;
}

Chess::Chess() {
    position = Position();
    color = -1;
}

Chess::Chess(Position position, int color) {
    this->position = position;
    this->color = color;
}


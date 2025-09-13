//
// Created by 34329 on 2025/9/13.
//

#include "Player.h"

std::string Player::getName() {
    return name;
}

Player::Player(const std::string &name, const int color) {
    this->name = name;
    this->color = color;
}

void Player::setName(std::string name) {
    this->name = name;
}

void Player::setColor(int color) {
    this->color = color;
}

int Player::getColor() {
    return this->color;
}


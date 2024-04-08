#ifndef GAME_H
#define GAME_H

#include "Square.h"
#include <iostream>

class Game {
    Square board[9];
    bool playerX;
    bool AI;

    void AIMove() {
        if (!playerX) {
            for (int i = 0; i < 9; i++) {
                if (board[i].isEmpty()) {
                    board[i].playO();
                    break;
                }
            }
            playerX = !playerX;
        }
    }

public:
    Game() {
        board[0] = Square(-0.9f, 0.9f, 0.6f);
        board[1] = Square(-0.3f, 0.9f, 0.6f);
        board[2] = Square(0.3f, 0.9f, 0.6f);

        board[3] = Square(-0.9f, 0.3f, 0.6f);
        board[4] = Square(-0.3f, 0.3f, 0.6f);
        board[5] = Square(0.3f, 0.3f, 0.6f);

        board[6] = Square(-0.9f, -0.3f, 0.6f);
        board[7] = Square(-0.3f, -0.3f, 0.6f);
        board[8] = Square(0.3f, -0.3f, 0.6f);

        playerX = true;
        AI = false;
    }

    void AIOn() {
        AI = true;
        AIMove();
    }

    void AIOff() {
        AI = false;
    }

    void playerXFirst() {
        playerX = true;
    }

    void playerOFirst() {
        playerX = false;
    }

    void start() {
        if (AI) {
            AIMove();
        }
    }

    void handleMouseClick(float x, float y) {
        for (int i = 0; i < 9; i++) {
            if (board[i].contains(x,  y)) {
                if (board[i].isEmpty()) {
                    if (playerX) {
                        board[i].playX();
                    } else {
                        board[i].playO();
                    }
                    playerX = !playerX;
                    break;
                }
            }
        }

        if (AI) {
            AIMove();
        }
    }

    void draw() {
        for (int i = 0; i < 9; i++) {
            board[i].draw();
        }
    }
};

#endif
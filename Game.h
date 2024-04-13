#ifndef GAME_H
#define GAME_H

#include "Square.h"
#include <iostream>
#include <string>
#include "Button.h"

enum STATE{START, PLAYING, END};

class Game {
    Square **board;
    int count;

    bool playerX;
    bool AI;
    STATE gameState;

    //Start screen elements
    Button title;
    Button playButton;
    Button button3;
    Button button4;
    Button button5;
    Button AIButton;

    //End screen elements
    Button displayResults;

    Button againButton;
    Button quitButton;
    
    std::string message;

    void AIMove() {
        if (!playerX) {
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < count; j++) {
                    if (board[i][j].isEmpty()) {
                        board[i][j].playO();
                        break;
                    }
                }
            }
            playerX = !playerX;
        }
    }

    void makeBoard(){
        board = new Square*[count];
        for (int i = 0; i < count; i++){
            board[i] = new Square[count];
        }
        float x = -0.9;
        float y = 0.9;

        float w = 1.8 / count;
        float h = 1.5 / count;
        // Initialize your state variables
        for (int i = 0; i < count; i++){
            x = -0.9;
            for (int j = 0; j < count; j++){
                board[i][j] = Square(x, y, w, h);
                x += w;
            }
            y -= h;
        }
    }

public:
    Game() {
        //Start screen
        title = Button("Let's play Tic Tac Toe", -0.5, 0.75);
        playButton = Button("Play", -0.1, 0.3);
        
        
        button3 = Button("3 x 3", -0.9, -0.75);
        button4 = Button("4 x 4", -0.5, -0.75);
        button5 = Button("5 x 5", -0.1, -0.75);
        AIButton = Button("With AI?", 0.5, -0.75);

        //End screen

        //Button displayResults = Button(message, -0.9, 0.75);

        Button againButton = Button("Again?", -0.9, -0.75);
        Button quitButton = Button("Quit?", -0.1, -0.75);

        playerX = true;
        AI = false;
        gameState = START;
        count = 3;
        makeBoard();
    }

    void AIOn() {
        AI = true;
        //AIMove();
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

    void end() {
        gameState = END;
    }

    STATE getState() {
        return gameState;
    }

    void handleMouseClick(float x, float y) {
        if (gameState == PLAYING) {
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < count; j++) {
                    if (board[i][j].contains(x,  y)) {
                        if (board[i][j].isEmpty()) {
                            if (playerX) {
                                board[i][j].playX();
                            } else {
                                board[i][j].playO();
                            }
                            playerX = !playerX;
                            break;
                        }
                    }
                }
            }

            if (AI) {
            AIMove();
        }
        }


        if (gameState == START) {

            if (playButton.contains(x, y)) {
                playButton.setPressed();
                gameState = PLAYING;
            }

            if (AIButton.contains( x,  y)) {
                AIButton.togglePressed();
                AI = AIButton.getPressed();
            }

            if (button3.contains(x, y)){
                std::cout << "Will change to 3x3" << std::endl;
                /*for (int i = 0; i < count; i++){
                    delete[] board[i];
                }
                delete[] board;*/
                count = 3;
                gameState = PLAYING;
                button3.setPressed();
                button4.setUnpressed();
                button5.setUnpressed();
                //makeBoard();
            }
            else if (button4.contains(x, y)){
                std::cout << "Will change to 4x4" << std::endl;
                for (int i = 0; i < count; i++){
                    delete[] board[i];
                }
                delete[] board;
                count = 4;
                button4.setPressed();
                button3.setUnpressed();
                button5.setUnpressed();
                makeBoard();
            }
            else if (button5.contains(x, y)){
                std::cout << "Will change to 5x5" << std::endl;
                /*for (int i = 0; i < count; i++){
                    delete[] board[i];
                }
                delete[] board;*/
                count = 5;
                button5.setPressed();
                button3.setUnpressed();
                button4.setUnpressed();
                //makeBoard();
            }
        }
    }

    void draw() {
        if (gameState == START){
            drawStart();
        } else if (gameState == END) {
            drawEnd();
        } else if (gameState == PLAYING) {
            for (int i = 0; i < count; i++) {
                for (int j = 0; j < count; j++) {
                    board[i][j].draw();
                    std::cout << "DRAWING" << std::endl;
                }
            }
        }
        
    }

    void drawStart() {
        button3.draw();
        button4.draw();
        button5.draw();
        title.draw();
        AIButton.draw();
        playButton.draw();
    }

    void drawEnd() {
        displayResults.draw();
        againButton.draw();
        quitButton.draw();
    } 

    bool checkFull() {
        for(int i = 0; i < count; i++) {
            for(int j = 0; j < count; j++) {
                if(board[i][j].getState() == EMPTY) {
                    return false;
                }
            }
        }
        return true;
    }
    
};

#endif
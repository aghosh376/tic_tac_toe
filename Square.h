#ifndef SQUARE_H
#define SQUARE_H

#include <GL/gl.h>
#include <cmath>

enum SquareState {EMPTY, PLAYER_X, PLAYER_O};

class Square {
    float x;
    float y;
    float size;
    float width;
    float height;
    SquareState state;

public:
    Square() {
        x = 0.0f;
        y = 0.0f;
        size = 0.6f;
        state = EMPTY;
    }

    Square(float x, float y, float size) {
        this->x = x;
        this->y = y;
        this->size = size;
        width = size;
        height = size;
        state = EMPTY;
    }

    Square(float x, float y, float width, float height) {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        size = width;
        state = EMPTY;
    }

    bool isEmpty() {
        return state == EMPTY;
    }

    SquareState getState() {
        return state;
    }

    void playX() {
        state = PLAYER_X;
    }

    void playO() {
        state = PLAYER_O;
    }

    void draw() {
        glColor3f(0.0f, 0.0f, 0.0f);
        glLineWidth(2.0f);

        glBegin(GL_LINES);
            glVertex2f(x, y);
            glVertex2f(x + width, y);

            glVertex2f(x + width, y);
            glVertex2f(x + width, y - height);

            glVertex2f(x + width, y - height);
            glVertex2f(x, y - height);

            glVertex2f(x, y - height);
            glVertex2f(x, y);
        glEnd();

        if (state == PLAYER_X) {
            glBegin(GL_LINES);
                glVertex2f(x + 0.1f, y - 0.1f);
                glVertex2f(x + width - 0.1f, y - height + 0.1f);

                glVertex2f(x + width - 0.1f, y - 0.1f);
                glVertex2f(x + 0.1f, y - height + 0.1f);
            glEnd();
        } else if (state == PLAYER_O) {
            glBegin(GL_LINES);
                float inc = (2 * M_PI) / 60;
                for (float theta = 0; theta <= 2 * M_PI; theta += inc) {
                    glVertex2f((x + (size / 2)) + (size / 2 - 0.1f) * cos(theta), (y - (height / 2)) + (height / 2 - 0.1f) * sin(theta));
                    glVertex2f((x + (size / 2)) + (size / 2 - 0.1f) * cos(theta + inc), (y - (height / 2)) + (height / 2 - 0.1f) * sin(theta + inc));
                }
            glEnd();
        }
    }

    bool contains(float mx, float my) {
        if (mx >= x && mx <= x + width && my <= y && my >= y - height) {
            return true;
        } else {
            return false;
        }
    }
};

#endif
#ifndef TETRIS_CPP_
#define TETRIS_CPP_

#include "util.h"
#include "game-release.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <string>
#include <unistd.h>
#include <sstream>
#include <cmath>      

using namespace std;

// --- Global Variables ---
int x5 = 200, y5 = 0;          // Player position
int x6 = 141, y6 = 850;        // Obstacle position
int x7 = 300, y7 = 600;        // AI Follower position
int x9 = 141, y9 = 850;        // Coin position

bool gamepause = false;
bool obsrun = true;
bool coin = true;

int score = 0;
int dis = 0;
int live = 3;
int rand1, rand2;
string name;

// --- Functions ---

void SetCanvasSize(int width, int height) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1); 
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Display() {
    glClearColor(0.2, 0.2, 0.2, 0); 
    glClear(GL_COLOR_BUFFER_BIT);

    if (gamepause) {
        // --- Pause Screen ---
        DrawRoundRect(150, 150, 550, 550, colors[GRAY], 20);
        DrawString(350, 600, "Game Pause", colors[BLACK]);
        DrawString(250, 550, "Player : " + name, colors[WHITE]);
        DrawString(250, 500, "Distance: " + to_string(dis), colors[WHITE]);
        DrawString(250, 450, "Score : " + to_string(score), colors[WHITE]); 
        DrawString(250, 350, "Press 'R' to resume", colors[DARK_GRAY]);
        
        glutSwapBuffers();
        
    } else if (live > 0) {
        // --- Game Running ---
        
        if (dis < 200) y5 += 2;

        // HUD
        DrawString(50, 800, "Distance: " + to_string(dis), colors[LIGHT_PINK]);
        DrawString(600, 800, "Remaining Life: " + to_string(live), colors[RED]);
        DrawString(380, 800, "BitCoin: " + to_string(score), colors[GOLD]);
        
        dis += 1;

        // AI Enemy logic
        if (dis > 2000) {
            DrawSquare(x7 + 210, y7 + 20, 50, colors[RED]);
            if (x7 > x5) x7 -= 2;
            if (x7 < x5) x7 += 2;
            if (y7 > y5) y7 -= 2;
            if (y7 < y5) y7 += 2;

            // AI Collision
            if (x7 - 25 <= x5 && x7 + 25 >= x5 && y7 - 100 <= y5 && y7 + 100 >= y5) {
                y7 = 700;
                x7 = 300;
                live -= 1;
            }
        }

        // Random Spawner Logic
        if (y6 >= 850) {
            rand1 = rand() % 3;
            rand2 = rand() % 3;
            
            // X-Lane selection for obstacle
            if (rand1 == 0)      x6 = 141; 
            else if (rand1 == 1) x6 = 425;
            else                 x6 = 708;

            if (y9 >= 850) {
                // X-Lane selection for coin
                if (rand2 == 0)      x9 = 141;
                else if (rand2 == 1) x9 = 425;
                else                 x9 = 708;
                coin = true;
            }
            obsrun = true;
        }

        // Coin Logic
        if (coin) {
            DrawCircle(x9, y9, 30, colors[GOLD]);
            DrawString(x9 - 8, y9 - 7, "B", colors[DARK_GOLDEN_ROD]);
            y9 -= 10;

            if (x9 + 30 >= x5 + 210 && x9 - 30 <= x5 + 240 && y9 + 30 >= y5 + 20 && y9 - 30 <= y5 + 160) {
                score += 10;
                cout << "\a";
                y9 = 900;   
                coin = false;  
            }
            if (y9 <= 0) y9 = 900;
        }

        // Obstacle Logic
        if (obsrun) {
            DrawLine(x6 - 70, y6, x6 + 70, y6, 20, colors[RED]);
            DrawLine(x6 - 70, y6 - 60, x6 - 70, y6 + 10, 20, colors[RED]);
            DrawLine(x6 + 70, y6 - 60, x6 + 70, y6 + 10, 20, colors[RED]);
            DrawCircle(x6 - 70, y6, 20, colors[YELLOW]);
            DrawCircle(x6 + 70, y6, 20, colors[YELLOW]);
            DrawLine(x6 + 60, y6 + 10, x6 + 80, y6 - 10, 20, colors[BLACK]);
            DrawLine(x6 - 80, y6 + 10, x6 - 60, y6 - 10, 20, colors[BLACK]);

            // Speed progression
            if (dis > 2500)      y6 -= 25;
            else if (dis > 1500) y6 -= 20;
            else if (dis > 500)  y6 -= 15;
            else                 y6 -= 10;

            // Obstacle Collision
            if (x6 + 70 >= x5 + 180 && x6 - 70 <= x5 + 270 && y6 + 10 >= y5 + 20 && y6 - 60 <= y5 + 150) {
                live -= 1;
                y6 = 850;   
                obsrun = false; 
            }
            if (y6 <= 0) {
                y6 = 850;
                obsrun = false;
            }
        }

        // Player Character Drawing
        DrawTriangle(x5 + 180, y5 + 60, x5 + 270, y5 + 60, x5 + 225, y5 + 150, colors[DARK_GRAY]);
        DrawTriangle(x5 + 195, y5 + 25, x5 + 255, y5 + 25, x5 + 225, y5 + 55, colors[DARK_GRAY]);
        DrawRoundRect(x5 + 210, y5 + 20, 30, 140, colors[GRAY], 20);
        DrawString(x5 + 208, y5 + 75, "NU", colors[DARK_ORCHID]);

        // Road Lines
        DrawLine(283, 0, 283, 850, 20, colors[MISTY_ROSE]);
        DrawLine(566, 0, 566, 850, 20, colors[MISTY_ROSE]);

        glutSwapBuffers();

    } else if (live == 0) {
        // --- Game Over Screen ---
        DrawRoundRect(150, 150, 550, 550, colors[GRAY], 20);
        DrawString(350, 600, "Game Details", colors[BLACK]);
        DrawString(250, 550, "Player : " + name, colors[WHITE]);
        DrawString(250, 500, "Distance: " + to_string(dis), colors[WHITE]);
        DrawString(250, 450, "Score : " + to_string(score), colors[WHITE]); 
        DrawString(250, 350, "Press 'R' for restart", colors[DARK_GRAY]);
        DrawString(250, 300, "Press 'ESC' to end ", colors[DARK_GRAY]);

        glutSwapBuffers();
    } 
}

void NonPrintableKeys(int key, int x, int y) {
    if (key == GLUT_KEY_LEFT) {
        if (x5 > 0) x5 -= 283;
    } else if (key == GLUT_KEY_RIGHT) {
        if (x5 < 400) x5 += 283;
    } else if (key == GLUT_KEY_UP) {
        if (y5 < 500) y5 += 20;
    } else if (key == GLUT_KEY_DOWN) {
        if (y5 > 0) y5 -= 20;
    }
    glutPostRedisplay();
}

void PrintableKeys(unsigned char key, int x, int y) {
    if (key == KEY_ESC) {
        exit(1);
    }
    if (key == 'R' || key == 'r') {
        if (live > 0) {
            gamepause = false;
        } else {
            live = 3;
            dis = 0;
            score = 0;
            gamepause = false;
        }
    }
    if (key == 'P' || key == 'p') {
        gamepause = true;
    }
    glutPostRedisplay();
}

void Timer(int m) {
    glutPostRedisplay();
    glutTimerFunc(100.0 / FPS, Timer, 0);
}

int main(int argc, char* argv[]) {
    cout << "Enter Name: ";
    cin >> name;

    srand(time(NULL));
    int width = 850, height = 850;
    
    InitRandomizer();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(width, height);
    glutCreateWindow("PF's Game");
    
    SetCanvasSize(width, height);

    glutDisplayFunc(Display);
    glutSpecialFunc(NonPrintableKeys);
    glutKeyboardFunc(PrintableKeys);
    glutTimerFunc(5.0 / FPS, Timer, 0);

    glutMainLoop();
    return 1;
}

#endif
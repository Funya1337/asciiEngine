#include <stdio.h>
#include <string.h>
#include <time.h>

#include "../libs/vector.h"
#include "engine.h"
#include "math.h"

int nScreenWidth = 120;
int nScreenHeight = 40;

int nMapWidth = 16;
int nMapHeight = 16;

float fPlayerX = 8.0;
float fPlayerY = 8.0;
float fPlayerA = 0.0;

float fFOV = M_PI / 4.0;
float fDepth = 16.0;

void fillMapFromFile(char map[nMapWidth][nMapHeight]);
void printMap(char map[nMapWidth][nMapHeight]);

int main() {
    char map[nMapWidth][nMapHeight];
    fillMapFromFile(map);
    initscr();
    start_color();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    init_color(COLOR_CYAN, 201, 195, 195);  // Custom Grey (R, G, B)
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    while (isRunning()) {
        switch (getch()) {
            case 'q':
                setIsRunning();
                break;
            case 'a':
                fPlayerA -= 0.1;
                break;
            case 'd':
                fPlayerA += 0.1;
                break;
            case 'w':
                fPlayerX += sinf(fPlayerA) * 0.5;
                fPlayerY += cosf(fPlayerA) * 0.5;

                if (map[(int)fPlayerY][(int)fPlayerX] == '#') {
                    fPlayerX -= sinf(fPlayerA) * 0.5;
                    fPlayerY -= cosf(fPlayerA) * 0.5;
                }
                break;
            case 's':
                fPlayerX -= sinf(fPlayerA) * 0.5;
                fPlayerY -= cosf(fPlayerA) * 0.5;

                if (map[(int)fPlayerY][(int)fPlayerX] == '#') {
                    fPlayerX += sinf(fPlayerA) * 0.5;
                    fPlayerY += cosf(fPlayerA) * 0.5;
                }
                break;
        }

        for (int x = 0; x < nScreenWidth; ++x) {
            float fRayAngle = (fPlayerA - fFOV / 2.0) + ((float)x / (float)nScreenWidth) * fFOV;
            float fDistanceToWall = 0;
            int bHitWall = 0;
            int bBoundary = 0;

            float fEyeX = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);

            while (!bHitWall && fDistanceToWall < fDepth) {
                fDistanceToWall += 0.1;

                int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int)(fPlayerY + fEyeY * fDistanceToWall);

                if (nTestX < 0 || nTestX >= nMapWidth || nTestY < 0 || nTestY >= nMapHeight) {
                    bHitWall = 1;
                    fDistanceToWall = fDepth;
                } else {
                    if (map[nTestY][nTestX] == '#') {
                        bHitWall = 1;

                        Vector* p = initVector(1);

                        for (int tx = 0; tx < 2; ++tx)
                            for (int ty = 0; ty < 2; ++ty) {
                                float vy = (float)nTestY + ty - fPlayerY;
                                float vx = (float)nTestX + tx - fPlayerX;
                                float d = sqrt(vx * vx + vy * vy);
                                float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
                                Pair pair = {d, dot};
                                push_back(p, &pair);
                            }
                        qsort(p->data, p->used, sizeof(Pair), compare);

                        float fBound = 0.01;
                        if (acos(p->data[0].second) < fBound) bBoundary = true;
                        if (acos(p->data[1].second) < fBound) bBoundary = true;
                        // if (acos(p->data[2].second) < fBound) bBoundary = true;
                    }
                }
            }
            int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
            int nFloor = nScreenHeight - nCeiling;

            int nShade = ' ';
            int nShadeFloor = ' ';

            if (fDistanceToWall <= fDepth / 4.0)
                nShade = '#';
            else if (fDistanceToWall < fDepth / 3.0)
                nShade = '+';
            else if (fDistanceToWall < fDepth / 2.0)
                nShade = '-';
            else
                nShade = '.';

            if (bBoundary) nShade = ' ';

            for (int y = 0; y < nScreenHeight; ++y) {
                if (y < nCeiling) {
                    mvaddch(y, x, ' ' | COLOR_PAIR(3));
                } else if (y > nCeiling && y <= nFloor) {
                    mvaddch(y, x, (char)nShade | COLOR_PAIR(1));
                } else {
                    float b = 1.0 - (((float)y - nScreenHeight / 2.0) / ((float)nScreenHeight / 2.0));
                    if (b < 0.25)
                        nShadeFloor = '#';
                    else if (b < 0.5)
                        nShadeFloor = '+';
                    else if (b < 0.75)
                        nShadeFloor = '-';
                    else if (b < 0.9)
                        nShadeFloor = ':';
                    else
                        nShadeFloor = '.';
                    mvaddch(y, x, nShadeFloor | COLOR_PAIR(2));
                }
            }
        }
        refresh();
    }
    endwin();

    return 0;
}

void fillMapFromFile(char map[nMapWidth][nMapHeight]) {
    int bufferLength = 18;
    char buffer[bufferLength];
    FILE* ptr = fopen("../assets/map.txt", "r");

    if (ptr == NULL) {
        printf("FILE NOT FOUND\n");
        return;
    }

    for (int y = 0; y < nMapHeight; ++y) {
        if (fgets(buffer, bufferLength, ptr) != NULL) {
            for (int x = 0; x < nMapWidth; ++x) {
                map[x][y] = buffer[x];
            }
        } else {
            printf("Error reading line %d\n", y);
            break;
        }
    }
    fclose(ptr);
}

void printMap(char map[nMapWidth][nMapHeight]) {
    for (int i = 0; i < nMapWidth; ++i) {
        for (int j = 0; j < nMapHeight; ++j) {
            printw("%c", map[i][j]);
        }
        printw("\n");
    }
}
#include <stdio.h>
#include <string.h>

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
    const char* map =
        "#################..............##..............##..............##..............##..............##..."
        "...........##..............##..............##..............##..............##..............##......."
        ".......##..............##..............#################";
    // char map[nMapWidth][nMapHeight];
    // fillMapFromFile(map);
    initscr();

    // for (int i = 0; i < nScreenHeight; ++i) {
    //     for (int j = 0; j < nScreenWidth; ++j) {
    //         mvaddch(i, j, '.');
    //     }
    // }

    // printMap(map);

    while (isRunning()) {
        for (int x = 0; x < nScreenWidth; ++x) {
            float fRayAngle = (fPlayerA - fFOV / 2.0) + ((float)x / (float)nScreenWidth) * fFOV;
            float fDistanceToWall = 0;
            int bHitWall = 0;

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
                    if (map[nTestY * nMapWidth + nTestX] == '#') {
                        bHitWall = 1;
                    }
                }
            }
            int nCeiling = (float)(nScreenHeight / 2.0) - nScreenHeight / ((float)fDistanceToWall);
            int nFloor = nScreenHeight - nCeiling;

            int nShade = ' ';

            if (fDistanceToWall <= fDepth / 4.0)
                nShade = 0x2588;
            else if (fDistanceToWall < fDepth / 3.0)
                nShade = 0x2593;
            else if (fDistanceToWall < fDepth / 2.0)
                nShade = 0x2592;
            else if (fDistanceToWall < fDepth) {
                init_pair(1, COLOR_BLACK, COLOR_RED);
                nShade = 0x2591;
            } else
                nShade = ' ';

            for (int y = 0; y < nScreenHeight; ++y) {
                if (y < nCeiling)
                    mvaddch(y, x, ' ');
                else if (y > nCeiling && y <= nFloor)
                    mvaddch(y, x, (char)nShade);
                else
                    mvaddch(y, x, ' ');
            }
        }
        refresh();
        char ch = getch();
        if (ch == 'q') setIsRunning();
        if (ch == 'a') fPlayerA -= (0.3);
        if (ch == 'd') fPlayerA += (0.3);
        if (ch == 'w') {
            fPlayerX += sinf(fPlayerA) * 1.0;
            fPlayerY += cosf(fPlayerA) * 1.0;
        }
        if (ch == 's') {
            fPlayerX -= sinf(fPlayerA) * 1.0;
            fPlayerY -= cosf(fPlayerA) * 1.0;
        }
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
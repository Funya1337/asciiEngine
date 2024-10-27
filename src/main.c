#include <stdio.h>
#include <string.h>
#include <time.h>

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
        "...........##......#.......##..............##..............##..............##..............##......."
        ".......##..............##..............#################";
    // char map[nMapWidth][nMapHeight];
    // fillMapFromFile(map);
    initscr();
    start_color();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    init_color(COLOR_CYAN, 201, 195, 195);  // Custom Grey (R, G, B)
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);

    struct timespec t1, t2;
    clock_gettime(CLOCK_MONOTONIC, &t1);

    while (isRunning()) {
        clock_gettime(CLOCK_MONOTONIC, &t2);
        double fElapsedTime = (t2.tv_sec - t1.tv_sec) + (t2.tv_nsec - t1.tv_nsec) / 1e9;
        t1 = t2;

        switch (getch()) {
            case 'q':
                setIsRunning();
                break;
            case 68:
                fPlayerA -= 200 * fElapsedTime;
                break;
            case 67:
                fPlayerA += 200 * fElapsedTime;
                break;
            case 'w':
                fPlayerX += sinf(fPlayerA) * 800 * fElapsedTime;
                fPlayerY += cosf(fPlayerA) * 800 * fElapsedTime;

                if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                    fPlayerX -= sinf(fPlayerA) * 800 * fElapsedTime;
                    fPlayerY -= cosf(fPlayerA) * 800 * fElapsedTime;
                }
                break;
            case 's':
                fPlayerX -= sinf(fPlayerA) * 800 * fElapsedTime;
                fPlayerY -= cosf(fPlayerA) * 800 * fElapsedTime;

                if (map[(int)fPlayerY * nMapWidth + (int)fPlayerX] == '#') {
                    fPlayerX += sinf(fPlayerA) * 800 * fElapsedTime;
                    fPlayerY += cosf(fPlayerA) * 800 * fElapsedTime;
                }
                break;
        }

        for (int x = 0; x < nScreenWidth; ++x) {
            float fRayAngle = (fPlayerA - fFOV / 2.0) + ((float)x / (float)nScreenWidth) * fFOV;
            float fDistanceToWall = 0;
            int bHitWall = 0;
            // int bBoundary = 0;

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
            int nShadeFloor = ' ';

            // NOT WORKING WITH BLOCK ASCII CHARACTERS (TO DO)
            // if (fDistanceToWall <= fDepth / 4.0)
            //     nShade = 0x2588;
            // else if (fDistanceToWall < fDepth / 3.0)
            //     nShade = 0x2593;
            // else if (fDistanceToWall < fDepth / 2.0)
            //     nShade = 0x2592;
            // else if (fDistanceToWall < fDepth) {
            //     nShade = 0x2591;
            // } else
            //     nShade = ' ';

            if (fDistanceToWall <= fDepth / 4.0)
                nShade = '#';
            else if (fDistanceToWall < fDepth / 3.0)
                nShade = '+';
            else if (fDistanceToWall < fDepth / 2.0)
                nShade = '-';
            else
                nShade = '.';

            for (int y = 0; y < nScreenHeight; ++y) {
                if (y < nCeiling)
                    mvaddch(y, x, ' ');
                else if (y > nCeiling && y <= nFloor) {
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
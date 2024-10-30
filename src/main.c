#include <stdio.h>
#include <string.h>

#include "engine.h"

void fillMapFromFile(char map[N_MAP_WIDTH][N_MAP_HEIGHT]);
void printMap(char map[N_MAP_WIDTH][N_MAP_HEIGHT], Player* player);

int main() {
    Player player = playerInit();
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
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_WHITE, COLOR_WHITE);

    while (isRunning()) {
        handlePlayerInput(&player, &stopRunning);
        for (int x = 0; x < N_SCREEN_WIDTH; ++x) {
            float fRayAngle =
                (player.fPlayerA - player.fFOV / 2.0) + ((float)x / (float)N_SCREEN_WIDTH) * player.fFOV;
            float fDistanceToWall = 0;
            int bHitWall = 0;
            int bBoundary = 0;

            float fEyeX = sinf(fRayAngle);
            float fEyeY = cosf(fRayAngle);

            while (!bHitWall && fDistanceToWall < player.fDepth) {
                fDistanceToWall += 0.1;

                int nTestX = (int)(player.fPlayerX + fEyeX * fDistanceToWall);
                int nTestY = (int)(player.fPlayerY + fEyeY * fDistanceToWall);

                if (nTestX < 0 || nTestX >= N_MAP_WIDTH || nTestY < 0 || nTestY >= N_MAP_HEIGHT) {
                    bHitWall = 1;
                    fDistanceToWall = player.fDepth;
                } else {
                    if (map[nTestY][nTestX] == '#') {
                        bHitWall = 1;

                        Vector* p = initVector(1);

                        for (int tx = 0; tx < 2; ++tx)
                            for (int ty = 0; ty < 2; ++ty) {
                                float vy = (float)nTestY + ty - player.fPlayerY;
                                float vx = (float)nTestX + tx - player.fPlayerX;
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
                        empty_vector(p);
                    }
                }
            }
            int nCeiling = (float)(N_SCREEN_HEIGHT / 2.0) - N_SCREEN_HEIGHT / ((float)fDistanceToWall);
            int nFloor = N_SCREEN_HEIGHT - nCeiling;

            int nShade = ' ';
            int nShadeFloor = ' ';

            if (fDistanceToWall <= player.fDepth / 4.0) {
                nShade = '#';
            } else if (fDistanceToWall < player.fDepth / 3.0)
                nShade = '+';
            else if (fDistanceToWall < player.fDepth / 2.0)
                nShade = '*';
            else
                nShade = '.';

            if (bBoundary) nShade = ' ';

            for (int y = 0; y < N_SCREEN_HEIGHT; ++y) {
                if (y < nCeiling) {
                    mvaddch(y, x, ' ');
                } else if (y > nCeiling && y <= nFloor) {
                    mvaddch(y, x, (char)nShade | COLOR_PAIR(1));
                } else {
                    float b = 1.0 - (((float)y - N_SCREEN_HEIGHT / 2.0) / ((float)N_SCREEN_HEIGHT / 2.0));
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
        printMap(map, &player);
        refresh();
    }
    endwin();
    return 0;
}

void fillMapFromFile(char map[N_MAP_WIDTH][N_MAP_HEIGHT]) {
    int bufferLength = 18;
    char buffer[bufferLength];
    FILE* ptr = fopen("../assets/map.txt", "r");

    if (ptr == NULL) {
        printf("FILE NOT FOUND\n");
        return;
    }

    for (int y = 0; y < N_MAP_HEIGHT; ++y) {
        if (fgets(buffer, bufferLength, ptr) != NULL) {
            for (int x = 0; x < N_MAP_WIDTH; ++x) {
                map[x][y] = buffer[x];
            }
        } else {
            printf("Error reading line %d\n", y);
            break;
        }
    }
    fclose(ptr);
}

void printMap(char map[N_MAP_WIDTH][N_MAP_HEIGHT], Player* player) {
    for (int i = 0; i < N_MAP_WIDTH; ++i) {
        for (int j = 0; j < N_MAP_HEIGHT; ++j) {
            if (i == (int)player->fPlayerX && j == (int)player->fPlayerY)
                mvaddch(i, j, 'P');
            else
                mvaddch(i, j, map[j][i] | COLOR_PAIR(3));
        }
    }
}
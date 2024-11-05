// #include "engine.h"

// void fillMapFromFile(char map[N_MAP_WIDTH][N_MAP_HEIGHT]);
// void printMap(char map[N_MAP_WIDTH][N_MAP_HEIGHT], Player* player);

// int main() {
//     Player player = playerInit();
//     fillMapFromFile(map);
// initscr();
// start_color();
// noecho();
// cbreak();
// curs_set(0);
// nodelay(stdscr, TRUE);

//     init_color(COLOR_CYAN, 201, 195, 195);  // Custom Grey (R, G, B)
//     init_pair(1, COLOR_WHITE, COLOR_BLACK);
//     init_pair(2, COLOR_CYAN, COLOR_BLACK);
//     init_pair(3, COLOR_GREEN, COLOR_BLACK);
//     init_pair(4, COLOR_WHITE, COLOR_WHITE);

//     while (isRunning()) {
//         handlePlayerInput(&player, &stopRunning);
//         for (int x = 0; x < N_SCREEN_WIDTH; ++x) {
//             float fRayAngle =
//                 (player.fPlayerA - player.fFOV / 2.0) + ((float)x / (float)N_SCREEN_WIDTH) * player.fFOV;
//             float fDistanceToWall = 0;
//             int bHitWall = 0;
//             int bBoundary = 0;

//             float fEyeX = sinf(fRayAngle);
//             float fEyeY = cosf(fRayAngle);

//             while (!bHitWall && fDistanceToWall < player.fDepth) {
//                 fDistanceToWall += 0.1;

//                 int nTestX = (int)(player.fPlayerX + fEyeX * fDistanceToWall);
//                 int nTestY = (int)(player.fPlayerY + fEyeY * fDistanceToWall);

//                 if (nTestX < 0 || nTestX >= N_MAP_WIDTH || nTestY < 0 || nTestY >= N_MAP_HEIGHT) {
//                     bHitWall = 1;
//                     fDistanceToWall = player.fDepth;
//                 } else {
//                     if (map[nTestY][nTestX] == '#') {
//                         bHitWall = 1;

//                         Vector(Pair) vect;
//                         vector_init(&vect);

//                         for (int tx = 0; tx < 2; ++tx)
//                             for (int ty = 0; ty < 2; ++ty) {
//                                 float vy = (float)nTestY + ty - player.fPlayerY;
//                                 float vx = (float)nTestX + tx - player.fPlayerX;
//                                 float d = sqrt(vx * vx + vy * vy);
//                                 float dot = (fEyeX * vx / d) + (fEyeY * vy / d);
//                                 Pair pair = {d, dot};
//                                 vector_push_back(&vect, pair);
//                             }
//                         qsort(vect.data, vect.capacity, sizeof(Pair), compare);

//                         float fBound = 0.01;
//                         if (acos(vect.data[0].second) < fBound) bBoundary = true;
//                         if (acos(vect.data[1].second) < fBound) bBoundary = true;
//                         vector_clear(&vect);
//                     }
//                 }
//             }
//             int nCeiling = (float)(N_SCREEN_HEIGHT / 2.0) - N_SCREEN_HEIGHT / ((float)fDistanceToWall);
//             int nFloor = N_SCREEN_HEIGHT - nCeiling;

//             int nShade = ' ';
//             int nShadeFloor = ' ';

//             if (fDistanceToWall <= player.fDepth / 4.0) {
//                 nShade = '#';
//             } else if (fDistanceToWall < player.fDepth / 3.0)
//                 nShade = '+';
//             else if (fDistanceToWall < player.fDepth / 2.0)
//                 nShade = '*';
//             else
//                 nShade = '.';

//             if (bBoundary) nShade = ' ';

//             for (int y = 0; y < N_SCREEN_HEIGHT; ++y) {
//                 if (y < nCeiling) {
//                     mvaddch(y, x, ' ');
//                 } else if (y > nCeiling && y <= nFloor) {
//                     mvaddch(y, x, (char)nShade | COLOR_PAIR(1));
//                 } else {
//                     float b = 1.0 - (((float)y - N_SCREEN_HEIGHT / 2.0) / ((float)N_SCREEN_HEIGHT / 2.0));
//                     if (b < 0.25)
//                         nShadeFloor = '#';
//                     else if (b < 0.5)
//                         nShadeFloor = '+';
//                     else if (b < 0.75)
//                         nShadeFloor = '-';
//                     else if (b < 0.9)
//                         nShadeFloor = ':';
//                     else
//                         nShadeFloor = '.';
//                     mvaddch(y, x, nShadeFloor | COLOR_PAIR(2));
//                 }
//             }
//         }
//         printMap(map, &player);
//         refresh();
//     }
//     endwin();
//     return 0;
// }

// void fillMapFromFile(char map[N_MAP_WIDTH][N_MAP_HEIGHT]) {
//     int bufferLength = 18;
//     char buffer[bufferLength];
//     FILE* ptr = fopen("../assets/map.txt", "r");

//     if (ptr == NULL) {
//         printf("FILE NOT FOUND\n");
//         return;
//     }

//     for (int y = 0; y < N_MAP_HEIGHT; ++y) {
//         if (fgets(buffer, bufferLength, ptr) != NULL) {
//             for (int x = 0; x < N_MAP_WIDTH; ++x) {
//                 map[x][y] = buffer[x];
//             }
//         } else {
//             printf("Error reading line %d\n", y);
//             break;
//         }
//     }
//     fclose(ptr);
// }

// void printMap(char map[N_MAP_WIDTH][N_MAP_HEIGHT], Player* player) {
//     for (int i = 0; i < N_MAP_WIDTH; ++i) {
//         for (int j = 0; j < N_MAP_HEIGHT; ++j) {
//             if (i == (int)player->fPlayerX && j == (int)player->fPlayerY)
//                 mvaddch(i, j, 'P');
//             else
//                 mvaddch(i, j, map[j][i] | COLOR_PAIR(3));
//         }
//     }
// }

// ENGINE IMPL

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"

int main() {
    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    Vector(vec3) points;
    Vector(connection) connections;

    vector_init(&points);
    vector_init(&connections);

    vec3 point1 = {20, 20, 20};
    vec3 point2 = {40, 20, 20};
    vec3 point3 = {40, 40, 20};
    vec3 point4 = {20, 40, 20};

    vec3 point5 = {20, 20, 40};
    vec3 point6 = {40, 20, 40};
    vec3 point7 = {40, 40, 40};
    vec3 point8 = {20, 40, 40};

    connection conn1 = {0, 4};
    connection conn2 = {1, 5};
    connection conn3 = {2, 6};
    connection conn4 = {3, 7};

    connection conn5 = {0, 1};
    connection conn6 = {1, 2};
    connection conn7 = {2, 3};
    connection conn8 = {3, 0};

    connection conn9 = {4, 5};
    connection conn10 = {5, 6};
    connection conn11 = {6, 7};
    connection conn12 = {7, 4};

    // engine_normalize3d(&point1);
    // engine_normalize3d(&point2);
    // engine_normalize3d(&point3);
    // engine_normalize3d(&point4);
    // engine_normalize3d(&point5);
    // engine_normalize3d(&point6);
    // engine_normalize3d(&point7);
    // engine_normalize3d(&point8);

    vector_push_back(&connections, conn1);
    vector_push_back(&connections, conn2);
    vector_push_back(&connections, conn3);
    vector_push_back(&connections, conn4);

    vector_push_back(&connections, conn5);
    vector_push_back(&connections, conn6);
    vector_push_back(&connections, conn7);
    vector_push_back(&connections, conn8);

    vector_push_back(&connections, conn9);
    vector_push_back(&connections, conn10);
    vector_push_back(&connections, conn11);
    vector_push_back(&connections, conn12);

    vector_push_back(&points, point1);
    vector_push_back(&points, point2);
    vector_push_back(&points, point3);
    vector_push_back(&points, point4);
    vector_push_back(&points, point5);
    vector_push_back(&points, point6);
    vector_push_back(&points, point7);
    vector_push_back(&points, point8);

    // CALCULATE CENTROID
    vec3 c = {0, 0, 0};
    for (int i = 0; i < points.length; ++i) {
        c.x += points.data[i].x;
        c.y += points.data[i].y;
        c.z += points.data[i].z;
    }

    c.x /= points.length;
    c.y /= points.length;
    c.z /= points.length;

    while (isRunning()) {
        handleUserInput();

        for (int i = 0; i < points.length; ++i) {
            points.data[i].x -= c.x;
            points.data[i].y -= c.y;
            points.data[i].z -= c.z;
            engine_rotate(&points.data[i], 0.02, 0.01, 0.04);
            points.data[i].x += c.x;
            points.data[i].y += c.y;
            points.data[i].z += c.z;
            mvaddch(points.data[i].y, points.data[i].x, 'P');
        }

        for (int i = 0; i < connections.length; ++i) {
            vec2 from = {points.data[connections.data[i].a].x, points.data[connections.data[i].a].y};
            vec2 to = {points.data[connections.data[i].b].x, points.data[connections.data[i].b].y};
            engine_draw_line(&from, &to, 'P');
        }

        refresh();
        clear();
        napms(50);
    }

    // INIT CUBE VERTICIES
    // mesh cubeMesh;
    // vector_init(&cubeMesh.tris);

    // Triangle south1 = {.p = {{0.0f, 0.0f, 0.0f}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 0.0f}}};
    // Triangle south2 = {.p = {{0.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}};

    // Triangle east1 = {.p = {{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}}};
    // Triangle east2 = {.p = {{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 0.0f, 1.0f}}};

    // Triangle north1 = {.p = {{1.0f, 0.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 1.0f}}};
    // Triangle north2 = {.p = {{1.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 0.0f, 1.0f}}};

    // Triangle west1 = {.p = {{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 1.0f}, {0.0f, 1.0f, 0.0f}}};
    // Triangle west2 = {.p = {{0.0f, 0.0f, 1.0f}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f, 0.0f}}};

    // Triangle top1 = {.p = {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 1.0f}}};
    // Triangle top2 = {.p = {{0.0f, 1.0f, 0.0f}, {1.0f, 1.0f, 1.0f}, {1.0f, 1.0f, 0.0f}}};

    // Triangle bottom1 = {.p = {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}}};
    // Triangle bottom2 = {.p = {{1.0f, 0.0f, 1.0f}, {0.0f, 0.0f, 0.0f}, {1.0f, 0.0f, 0.0f}}};

    // vector_push_back(&cubeMesh.tris, south1);
    // vector_push_back(&cubeMesh.tris, south2);

    // vector_push_back(&cubeMesh.tris, east1);
    // vector_push_back(&cubeMesh.tris, east2);

    // vector_push_back(&cubeMesh.tris, north1);
    // vector_push_back(&cubeMesh.tris, north2);

    // vector_push_back(&cubeMesh.tris, west1);
    // vector_push_back(&cubeMesh.tris, west2);

    // vector_push_back(&cubeMesh.tris, top1);
    // vector_push_back(&cubeMesh.tris, top2);

    // vector_push_back(&cubeMesh.tris, bottom1);
    // vector_push_back(&cubeMesh.tris, bottom2);

    // // PROJECTION MATRIX

    // float fNear = 0.1f;
    // float fFar = 1000.0f;
    // float fFov = 90.0f;
    // float fAspectRatio = (float)N_SCREEN_HEIGHT / (float)N_SCREEN_WIDTH;
    // float fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * M_PI);
    // mat4 matProj = {0};

    // matProj.m[0][0] = fAspectRatio * fFovRad;
    // matProj.m[1][1] = fFovRad;
    // matProj.m[2][2] = fFar / (fFar - fNear);
    // matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
    // matProj.m[2][3] = 1.0f;
    // matProj.m[3][3] = 0.0f;

    // for (int i = 0; i < cubeMesh.tris.length; ++i) {
    //     Triangle triProjected;

    //     mat4_mult(&cubeMesh.tris.data[i].p[0], &triProjected.p[0], &matProj);
    //     mat4_mult(&cubeMesh.tris.data[i].p[1], &triProjected.p[1], &matProj);
    //     mat4_mult(&cubeMesh.tris.data[i].p[2], &triProjected.p[2], &matProj);

    //     triProjected.p[0].x += 1.0f;
    //     triProjected.p[0].y += 1.0f;
    //     triProjected.p[1].x += 1.0f;
    //     triProjected.p[1].y += 1.0f;
    //     triProjected.p[2].x += 1.0f;
    //     triProjected.p[2].y += 1.0f;

    //     triProjected.p[0].x *= 0.5f * (float)N_SCREEN_WIDTH;
    //     triProjected.p[0].y *= 0.5f * (float)N_SCREEN_HEIGHT;

    //     triProjected.p[1].x *= 0.5f * (float)N_SCREEN_WIDTH;
    //     triProjected.p[1].y *= 0.5f * (float)N_SCREEN_HEIGHT;

    //     triProjected.p[2].x *= 0.5f * (float)N_SCREEN_WIDTH;
    //     triProjected.p[2].y *= 0.5f * (float)N_SCREEN_HEIGHT;

    //     vec2 v1 = {triProjected.p[0].x, triProjected.p[0].y};
    //     vec2 v2 = {triProjected.p[1].x, triProjected.p[1].y};
    //     vec2 v3 = {triProjected.p[2].x, triProjected.p[2].y};
    //     draw_triangle_optimized(&v1, &v2, &v3, 'p');
    // }

    // PRINT VERTICIES
    // for (int i = 0; i < cubeMesh.tris.length; ++i) {
    //     printf("----------------\n");
    //     for (int j = 0; j < 3; ++j) {
    //         printf("%f %f %f\n", cubeMesh.tris.data[i].p[j].x, cubeMesh.tris.data[i].p[j].y,
    //                cubeMesh.tris.data[i].p[j].z);
    //     }
    //     printf("----------------\n");
    // }

    getch();
    endwin();
    return 0;
}
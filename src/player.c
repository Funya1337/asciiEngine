#include "player.h"

Player playerInit() {
    Player player;
    player.fPlayerX = 8.0;
    player.fPlayerY = 8.0;
    player.fPlayerA = 0.0;
    player.fFOV = M_PI_4;
    player.fDepth = 16.0;
    return player;
}

void playerAngleRotationLeft(float offset, Player *player) { player->fPlayerA -= offset; }
void playerAngleRotationRight(float offset, Player *player) { player->fPlayerA += offset; }
void playerMoveForward(float offset, Player *player) {
    player->fPlayerX += sinf(player->fPlayerA) * offset;
    player->fPlayerY += cosf(player->fPlayerA) * offset;
    if (map[(int)player->fPlayerY][(int)player->fPlayerX] == '#') {
        player->fPlayerX -= sinf(player->fPlayerA) * 0.5;
        player->fPlayerY -= cosf(player->fPlayerA) * 0.5;
    }
}

void playerMoveBackward(float offset, Player *player) {
    player->fPlayerX -= sinf(player->fPlayerA) * offset;
    player->fPlayerY -= cosf(player->fPlayerA) * offset;

    if (map[(int)player->fPlayerY][(int)player->fPlayerX] == '#') {
        player->fPlayerX += sinf(player->fPlayerA) * 0.5;
        player->fPlayerY += cosf(player->fPlayerA) * 0.5;
    }
}

void handlePlayerInput(Player *player, void (*stopRunning)()) {
    switch (getch()) {
        case 'q':
            (*stopRunning)();
            break;
        case 'a':
            playerAngleRotationLeft(0.1, player);
            break;
        case 'd':
            playerAngleRotationRight(0.1, player);
            break;
        case 'w':
            playerMoveForward(0.5, player);
            break;
        case 's':
            playerMoveBackward(0.5, player);
            break;
    }
}
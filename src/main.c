// ENGINE IMPL

#include <stdio.h>
#include <stdlib.h>

#include "engine.h"

int main() {
    ASPECT = (float)N_SCREEN_WIDTH / N_SCREEN_HEIGHT;
    int shapeScale = 25;

    update_screen_size();
    printf("Initial size: width = %d, height = %d\n", N_SCREEN_WIDTH, N_SCREEN_HEIGHT);

    struct sigaction sa;
    sa.sa_handler = handle_winch;
    sa.sa_flags = 0;
    sigemptyset(&sa.sa_mask);

    if (sigaction(SIGWINCH, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    initscr();
    noecho();
    cbreak();
    curs_set(0);
    nodelay(stdscr, TRUE);

    Vector(vec3) points;
    Vector(connection) connections;
    vector_init(&points);
    vector_init(&connections);
    engine_input_points((void*)(&points), (void*)(&connections));
    engine_scale_shape(&points, points.length, shapeScale);
    engine_align_coords_center(&points);

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
            // mvaddch(points.data[i].y, points.data[i].x, '*');
        }

        for (int i = 0; i < connections.length; ++i) {
            vec2 from = {points.data[connections.data[i].a].x, points.data[connections.data[i].a].y * 0.7};
            vec2 to = {points.data[connections.data[i].b].x, points.data[connections.data[i].b].y * 0.7};
            engine_draw_line(&from, &to, '*');
        }

        refresh();
        clear();
        napms(50);
    }
    getch();
    endwin();
    vector_clear(&points);
    vector_clear(&connections);
    return 0;
}
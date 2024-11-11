#include "engine.h"

void engine_rotate(vec3 *point, float x, float y, float z) {
    float rad = 0;
    rad = x;
    point->y = cos(rad) * point->y - sin(rad) * point->z;
    point->z = sin(rad) * point->y + cos(rad) * point->z;

    rad = y;
    point->x = cos(rad) * point->x + sin(rad) * point->z;
    point->z = -sin(rad) * point->x + cos(rad) * point->z;

    rad = z;
    point->x = cos(rad) * point->x - sin(rad) * point->y;
    point->y = sin(rad) * point->x + cos(rad) * point->y;
}

void engine_draw_line(vec2 *v1, vec2 *v2, char ch) {
    float dx = v2->x - v1->x;
    float dy = v2->y - v1->y;

    float length = sqrt(dx * dx + dy * dy);
    float angle = atan2(dy, dx);

    for (float i = 0; i < length; ++i) mvaddch(v1->y + sin(angle) * i, v1->x + cos(angle) * i, ch);
}

void engine_align_coords_center(void *points) {
    float max_x, max_y = -1e9;
    float min_x, min_y = 1e9;

    for (int i = 0; i < (*(Vector(vec3) *)points).length; ++i) {
        float cur_x = (*(Vector(vec3) *)points).data[i].x;
        float cur_y = (*(Vector(vec3) *)points).data[i].y;
        if (max_x < cur_x) max_x = cur_x;
        if (max_y < cur_y) max_y = cur_y;
        if (min_x > cur_x) min_x = cur_x;
        if (min_y > cur_y) min_y = cur_y;
    }

    float x_center = (max_x + min_x) / 1.5;
    float y_center = (max_y + min_y) / 2.5;
    float x_offset = ((float)N_SCREEN_WIDTH / 2) - x_center;
    float y_offset = ((float)N_SCREEN_HEIGHT / 2) - y_center;

    for (int i = 0; i < (*(Vector(vec3) *)points).length; ++i) {
        vec3_add_each(&(*(Vector(vec3) *)points).data[i], x_offset, y_offset, 0);
    }
}

void engine_scale_shape(void *points, int size, int scale) {
    for (int i = 0; i < size; ++i) {
        vec3_scale(&(*(Vector(vec3) *)points).data[i], scale);
    }
}

void engine_input_points(void *points, void *connections) {
    FILE *file = fopen("../assets/cube.txt", "r");
    char line[256];
    int checker = 0;
    if (file != NULL) {
        while (fgets(line, sizeof(line), file)) {
            if (!checker && line[0] != '\n') {
                int file_x = line[0] - '0';
                int file_y = line[2] - '0';
                int file_z = line[4] - '0';

                vec3 vec = {file_x, file_y, file_z};
                vector_push_back((Vector(vec3) *)points, vec);
            } else if (checker && line[0] != '\n') {
                int file_a = line[0] - '0';
                int file_b = line[2] - '0';
                connection conn = {file_a, file_b};
                vector_push_back((Vector(connection) *)connections, conn);
            }
            if (line[0] == '\n') checker = !checker;
        }
        fclose(file);

        // for (int i = 0; i < (*(Vector(vec3) *)points).length; ++i)
        //     printf("%f %f %f\n", (*(Vector(vec3) *)points).data[i].x, (*(Vector(vec3) *)points).data[i].y,
        //            (*(Vector(vec3) *)points).data[i].z);

        // printf("-------------------\n");

        // for (int i = 0; i < (*(Vector(connection) *)connections).length; ++i)
        //     printf("%d %d\n", (*(Vector(connection) *)connections).data[i].a,
        //            (*(Vector(connection) *)connections).data[i].b);
    } else {
        fprintf(stderr, "Unable to open file!\n");
    }
}

void update_screen_size() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    N_SCREEN_WIDTH = w.ws_col;
    N_SCREEN_HEIGHT = w.ws_row;
    ASPECT = (float)N_SCREEN_WIDTH / N_SCREEN_HEIGHT;
}

void handle_winch(int sig) {
    (void)sig;
    update_screen_size();
    // printw("N_SCREEN_WIDTH: %d, N_SCREEN_HEIGHT: %d\n", N_SCREEN_WIDTH, N_SCREEN_HEIGHT);
}

void handleUserInput() {
    switch (getch()) {
        case 'q':
            stopRunning();
            break;
    }
}

int isRunning() { return running; }

void stopRunning() { running = 0; }
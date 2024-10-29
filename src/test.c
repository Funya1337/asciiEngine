#include <locale.h>
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

int main() {
    setlocale(LC_ALL, "");
    initscr();
    wchar_t wstr[] = {9474, L'\0'};
    mvaddwstr(0, 0, wstr);
    refresh();
    getch();
    endwin();
    return 0;
}

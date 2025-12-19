/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** This file manage everything about the window I open in the terminal.
*/

#include "./include/global_includes.h"

void write_in_file(file_infos_t *file_infos, char *new_content)
{
    file_infos->fd = open(file_infos->filepath, O_WRONLY | O_TRUNC);
    write(file_infos->fd, new_content, strlen(new_content));
    ftruncate(file_infos->fd, strlen(new_content));
    close(file_infos->fd);
}

int window_loop(file_infos_t *file_infos)
{
    int is_running = 1;
    int typed_ch;
    int len;
    char *tempo_realloc_test;
    int saved = 1;
    int cursor_x;
    int cursor_y;

    initscr();
    raw();
    noecho();
    keypad(stdscr, TRUE);
    while (is_running == 1) {
        clear();
        printw("\n");
        printw("                         /`·.¸          \n");
        printw("                        /¸...¸`:·       \n");
        printw("   ---              ¸.·´  ¸   `·.¸.·´)  \n");
        printw(" | cod |          : © ):´;      ¸  {    \n");
        printw("   ----            `·.¸ `·  ¸.·´\\`·¸)  \n");
        printw("                        `\\\\´´\\¸.·´       current version : %s\n\n", VERSION);
        printw("%s", file_infos->filecontent);
        getyx(stdscr, cursor_y, cursor_x);
        if (saved == 1)
            mvprintw(LINES - 1, COLS - 20, "STATUS : SAVED");
        else
            mvprintw(LINES - 1, COLS - 20, "STATUS : NOT SAVED");
        move(cursor_y, cursor_x);
        refresh();
        typed_ch = getch();
        if (typed_ch == 27 && saved == 0) {
            mvprintw(LINES - 1, 0, "Quit without saving : y/n");
            refresh();
            if (getch() == 'y') {
                is_running = 0;
            }
        } else if (typed_ch == 27 && saved == 1) {
            is_running = 0;
        }
        if (typed_ch == CTRL('s')) {
            write_in_file(file_infos, file_infos->filecontent);
            saved = 1;
        } else if (typed_ch >= 32 && typed_ch <= 126 || typed_ch == '\t' || typed_ch == '\n') {
            len = strlen(file_infos->filecontent);
            tempo_realloc_test = realloc(file_infos->filecontent, len + 2);
            if (tempo_realloc_test == NULL) {
                endwin();
                printf("REALLOC FAILED, try again...");
                exit(EXIT_FAIL);
            } else
                file_infos->filecontent = tempo_realloc_test;
            file_infos->filecontent[len] = (char)typed_ch;
            file_infos->filecontent[len + 1] = '\0';
            saved = 0;
        } else if (typed_ch == KEY_BACKSPACE || typed_ch == 127 || typed_ch == 8) {
            len = strlen(file_infos->filecontent);
            if (len > 0) {
                tempo_realloc_test = realloc(file_infos->filecontent, len);
                if (tempo_realloc_test == NULL) {
                    endwin();
                    printf("REALLOC FAILED, try again...");
                    exit(EXIT_FAIL);
                } else
                    file_infos->filecontent = tempo_realloc_test;
                file_infos->filecontent[len - 1] = '\0';
                saved = 0;
            }
        }
    }
    endwin();
    return SUCCESS;
}

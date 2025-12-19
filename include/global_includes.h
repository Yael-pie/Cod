/*
** EPITECH PROJECT, 2025
** shell.h
** File description:
** Header file for Organized.
*/

#ifndef GLOBAL_INCLUDE_H_
    #define GLOBAL_INCLUDE_H_
// All my macros
    #define SUCCESS 0
    #define EXIT_FAIL 84
    #define FAIL -1
    #define VERSION "0.1.0"
    #define CTRL(c) ((c) & 0x1F)
// All my libs includes
    #include <stdlib.h>
    #include <stdio.h>
    #include <unistd.h>
    #include <string.h>
    #include <fcntl.h>
    #include <sys/stat.h>
    #include <ncurses.h>
// File infos struct to stock everything about the given file
typedef struct file_infos_s {
    struct stat *file_stat;
    char *filepath;
    char *filecontent;
    int fd;
} file_infos_t;
// Global functions to use everywhere
int display_error_msg(char *part, char *msg);
char *my_strdup(char const *src);
// Window relative functions to manipulate the window
int window_loop(file_infos_t *file_infos);
#endif /* GLOBAL_INCLUDE_H_ */

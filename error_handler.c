/*
** EPITECH PROJECT, 2025
** return_errors.c
** File description:
** This cool function displays an error message
** on the error output with the return code -1.
*/
#include "./include/global_includes.h"

int display_error_msg(char *part, char *msg)
{
    char *error_message_1 = "\033[31m        |   ❌ - Error :   |\033[0m";
    char *error_message_2 = "\nUnfortunately, an error occurred.\n";
    char *error_message_3 = "The error occured during ";
    char *error_message_4 = "      ========================\n";

    write(2, error_message_4, 31);
    write(2, error_message_1, 38);
    write(2, error_message_2, 35);
    write(2, error_message_3, 25);
    write(2, part, strlen(part));
    write(2, ".\n", 2);
    write(2, msg, strlen(msg));
    write(2, ".\n", 2);
    write(2, error_message_4, 31);
    return EXIT_FAIL;
}

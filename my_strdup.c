/*
** EPITECH PROJECT, 2025
** my_strcpy
** File description:
** Copies a string to another one.
*/
#include "./include/global_includes.h"

char *my_strdup(char const *src)
{
    int len;
    char *new_str;

    if (!src)
        return NULL;
    len = strlen(src);
    new_str = malloc((len + 1) * sizeof(char));
    if (!new_str)
        return NULL;
    return strcpy(new_str, src);
}

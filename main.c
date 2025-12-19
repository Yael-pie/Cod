/*
** EPITECH PROJECT, 2025
** main.c
** File description:
** Main file of my editor project, basically it will handle
** given arguments, and a few error handling.
*/

#include "./include/global_includes.h"

static int display_help_message(int code)
{
    printf("\n");
    printf("\033[36m╔════════════════════════════════════════════════════════════╗\033[0m\n");
    printf("\033[36m║\033[0m          \033[33m╔═══════════════════════════════════╗\033[0m             \033[36m║\033[0m\n");
    printf("\033[36m║\033[0m          \033[33m║\033[1;32m       COD - Text Editor v%s\033[0m\033[33m    ║\033[0m             \033[36m║\033[0m\n", VERSION);
    printf("\033[36m║\033[0m          \033[33m╚═══════════════════════════════════╝\033[0m            \033[36m ║\033[0m\n");
    printf("\033[36m╠════════════════════════════════════════════════════════════╣\033[0m\n");
    printf("\033[36m║\033[0m \033[1;35mUSAGE:\033[0m                                                    \033[36m ║\033[0m\n");
    printf("\033[36m║\033[0m   \033[32m./cod\033[0m                   Create a new file                \033[36m║\033[0m\n");
    printf("\033[36m║\033[0m   \033[32m./cod <filename>\033[0m       Open or create a file            \033[36m ║\033[0m\n");
    printf("\033[36m║\033[0m   \033[32m./cod --help\033[0m           Display this help message       \033[36m  ║\033[0m\n");
    printf("\033[36m║\033[0m   \033[32m./cod --version\033[0m        Show version information        \033[36m  ║\033[0m\n");
    printf("\033[36m╠════════════════════════════════════════════════════════════╣\033[0m\n");
    printf("\033[36m║\033[0m \033[1;35mKEYBINDS:\033[0m                                                \033[36m  ║\033[0m\n");
    printf("\033[36m║\033[0m   \033[34mCtrl + S\033[0m                Save the file                   \033[36m ║\033[0m\n");
    printf("\033[36m║\033[0m   \033[34mEsc\033[0m                    Quit the editor                 \033[36m  ║\033[0m\n");
    printf("\033[36m╠════════════════════════════════════════════════════════════╣\033[0m\n");
    printf("\033[36m║\033[0m \033[1;35mDESCRIPTION:\033[0m                                            \033[36m   ║\033[0m\n");
    printf("\033[36m║\033[0m   COD is my minimal code editor integred in the cmd        \033[36m║\033[0m\n");
    printf("\033[36m║\033[0m   directly. There are a few shortcuts alvailable and I     \033[36m║\033[0m\n");
    printf("\033[36m║\033[0m          will add more features later.                     \033[36m║\033[0m\n");
    printf("\033[36m╚════════════════════════════════════════════════════════════╝\033[0m\n\n");
    return code;
}

static int display_version_message(int code)
{
    printf("------------------------\n");
    printf("Current version : \033[32m%s\033[0m\n", VERSION);
    printf("------------------------\n");
    return code;
}

static int check_if_file_is_here(file_infos_t *file_infos)
{
    if (stat(file_infos->filepath, file_infos->file_stat) == FAIL)
        return FAIL;
    file_infos->fd = open(file_infos->filepath, O_RDONLY);
    if (file_infos->fd == -1)
        return FAIL;
    return SUCCESS;
}

static int read_the_file(file_infos_t *file_infos)
{
    file_infos->filecontent = malloc((file_infos->file_stat->st_size + 1) * sizeof(char));
    if (read(file_infos->fd, file_infos->filecontent, file_infos->file_stat->st_size) == FAIL)
        return FAIL;
    return SUCCESS;
}

void free_it(file_infos_t *file_infos)
{
    free(file_infos->filecontent);
    free(file_infos->filepath);
    close(file_infos->fd);
}

static char *ask_for_name(void)
{
    char *name = malloc(256 * sizeof(char));
    size_t name_max_size = 256;
    int confirm = 0;

    if (!(name)) {
        printf("MALLOC FAILED, please try again...");
        exit(EXIT_FAIL);
    }
    while (confirm == 0) {
        printf("Please, enter a name for the new file : ");
        getline(&name, &name_max_size, stdin);
        name[strcspn(name, "\n")] = '\0';
        printf("\n");
        if (strlen(name) < 1) {
            printf("The new file name needs to be longer than one character. Please, try again...\n");
            continue;
        }
        confirm = 1;
        for (int i = 0; i < strlen(name); i++) {
            if (name[i] == '/') {
                printf("The new name cannot contain characters such as \"/\" or \"\\0\", please try again.\n");
                confirm = 0;
                break;
            }
        }
    }
    return name;
}

static int create_new_file(char *name)
{
    char command[512];

    sprintf(command, "touch %s", name);
    if (system(command) == 0)
        return SUCCESS;
    return FAIL;
}

static int create_new_file_ask(void)
{
    char *yes_or_no = malloc(256 * sizeof(char));
    size_t name_max_size = 256;
    int confirm = 0;

    if (!(yes_or_no)) {
        printf("MALLOC FAILED, please try again...");
        exit(EXIT_FAIL);
    }
    while (confirm == 0) {
        printf("Do you want to create a new file? (y/n) : ");
        getline(&yes_or_no, &name_max_size, stdin);
        yes_or_no[strcspn(yes_or_no, "\n")] = '\0';
        printf("\n");
        if (strcmp(yes_or_no, "y") != 0 && strcmp(yes_or_no, "n") != 0) {
            printf("Answer y or n please...\n");
            continue;
        }
        confirm = 1;
    }
    if (strcmp(yes_or_no, "n") == 0) {
        free(yes_or_no);
        return FAIL;
    }
    free(yes_or_no);
    return SUCCESS;
}

void fill_new_file_infos(char *name, file_infos_t *file_infos)
{
    struct stat file_stat_new;
    file_infos->file_stat = &file_stat_new;
    file_infos->filepath = my_strdup(name);
    file_infos->fd = open(name, O_RDONLY);
    free(name);
}

int main(int ac, char **av)
{
    file_infos_t file_infos;
    struct stat file_stat;
    char *custom_file_name;

    if (ac != 2) {
        if (ac == 1) {
            if (create_new_file_ask() == SUCCESS) {
                custom_file_name = my_strdup(ask_for_name());
                create_new_file(custom_file_name);
                fill_new_file_infos(custom_file_name, &file_infos);
                window_loop(&file_infos);
                free_it(&file_infos);
                return SUCCESS;
            }
        }
        else
            return display_help_message(EXIT_FAIL);
    }
    else if (ac == 2) {
        if (strcmp(av[1], "--help") == 0 || strcmp(av[1], "--h") == 0)
            return display_help_message(SUCCESS);
        if (strcmp(av[1], "--version") == 0 || strcmp(av[1], "--v") == 0)
            return display_version_message(SUCCESS);
        file_infos.filepath = malloc((strlen(av[1]) + 1) * sizeof(char));
        file_infos.file_stat = &file_stat;
        strcpy(file_infos.filepath, av[1]);
        if (check_if_file_is_here(&file_infos) == FAIL) {
            if (create_new_file_ask() == SUCCESS) {
                custom_file_name = my_strdup(ask_for_name());
                create_new_file(custom_file_name);
                fill_new_file_infos(custom_file_name, &file_infos);
            }
            free(file_infos.filepath);
            return SUCCESS;
        }
        if (read_the_file(&file_infos) == FAIL) {
            free_it(&file_infos);
            return display_error_msg("the reading of the file you gave as an argument", "Please try again");
        }
        window_loop(&file_infos);
        free_it(&file_infos);
        return SUCCESS;
    }
    return EXIT_FAIL;
}
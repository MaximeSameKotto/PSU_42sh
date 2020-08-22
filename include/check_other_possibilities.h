/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** check_other_possibilities
*/

#ifndef __CHECK_OTHER_POSSIBILITIES__
#define __CHECK_OTHER_POSSIBILITIES__

#include <stdbool.h>
#include <wordexp.h>
#include "shell.h"

bool is_dir(char *line);
wordexp_t get_matches(char *to_autocomplet);
wordexp_t search_match(char *to_autocomplet, shell_t *shell);
char **clean_matches(char **matches);

#endif

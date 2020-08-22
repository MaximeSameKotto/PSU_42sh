/*
** EPITECH PROJECT, 2020
** project_name
** File description:
** check_other_possibilities
*/

#include "env.h"
#include "my.h"
#include "shell.h"
#include "utils.h"
#include "check_other_possibilities.h"
#include <wordexp.h>
#include <stdbool.h>
#include <string.h>

char **check_other_possibilities(char *to_autocomplete, shell_t *shell)
{
    wordexp_t matches;

    if (is_dir(to_autocomplete))
        matches = get_matches(to_autocomplete);
    else
        matches = search_match(to_autocomplete, shell);
    matches.we_wordv = clean_matches(matches.we_wordv);
    return matches.we_wordv;
}

bool is_dir(char *line)
{
    for (int i = 0; line[i] ;i++)
        if (line[i] == '/')
            return true;
    return false;
}

wordexp_t get_matches(char *to_autocomplet)
{
    wordexp_t p;

    wordexp(to_autocomplet, &p, 0);
    return p;
}

wordexp_t search_match(char *to_autocomplet, shell_t *shell)
{
    wordexp_t p;
    char **path = my_str_to_word_array(my_getenv("PATH", shell->env), ":");

    wordexp(concate("./", to_autocomplet), &p, 0);
    for (int i = 0; path[i]; i++) {
        path[i] = concate(path[i], "/");
        path[i] = realloc(path[i], strlen(path[i]) +
                strlen(to_autocomplet) + 1);
        path[i] = strcat(path[i], to_autocomplet);
        wordexp(path[i], &p, WRDE_APPEND);
    }
    return p;
}

char **clean_matches(char **matches)
{
    int len = arraylen(matches);
    char **cleaned_match = malloc(sizeof(char *) * (len + 1));
    int j = 0;

    for (int i = 0; i != len; i++) {
        if (!rindex(matches[i], '*')) {
            cleaned_match[j] = rindex(matches[i], '/') + 1;
            j++;
        }
    }
    cleaned_match[j] = NULL;
    return cleaned_match;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 20:14:55 by moel-idr          #+#    #+#             */
/*   Updated: 2025/06/19 17:01:14 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

void free_token_list(t_token *token)
{
	t_token *tmp;
	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
}


int match_pattern(char *pattern, char *str)
{
    char *star;
    char *str_ptr;

	str_ptr = str;
	star = NULL;
    while (*str_ptr)
	{
        if (*pattern == '*')
		{
            star = pattern++;
            str = str_ptr;
        } 
        else if (*pattern == *str_ptr || *pattern == '?')
		{
            pattern++;
            str_ptr++;
        } 
        else if (star)
		{
            pattern = star + 1;
            str_ptr = ++str;
        } 
        else {
            return 0;
        }
    }

    while (*pattern == '*') pattern++;
    return *pattern == '\0';
}

int matched_count(char *token)
{
    DIR *dir;
    struct dirent *entry;
    int count = 0;

    dir = opendir(".");
    if (!dir) return 0;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' && token[0] != '.')
            continue;
        if (match_pattern(token, entry->d_name))
            count++;
    }
    closedir(dir);
    return count;
}
int no_matches(char *token)
{
	DIR *dir;
	int count;
    struct dirent *entry;

	dir = opendir(".");
    if (!dir)
        return (0);
	count = 0;	
	while ((entry = readdir(dir)) != NULL)
	{
        if (entry->d_name[0] == '.' && token[0] != '.')
            continue;
        
        if (match_pattern(token, entry->d_name))
		{
            count++;
        }
    }
	closedir(dir);
	return(count);
}

char **expand_wildcard(char *token , NodeType type)
{
    DIR *dir;
    struct dirent *entry;
    char **matches;
    int count = 0;
    int total = matched_count(token);
    matches = malloc((total + 1) * sizeof(char *));
    if (!matches) return NULL;

	if(no_matches(token) == 0 || type == QUOTED_VAR)
	{
		matches = ft_split(token,'\0');
		return(matches);
	}
    dir = opendir(".");
    if (!dir) {
        free(matches);
        return NULL;
    }
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] == '.' && token[0] != '.')
            continue;
        
        if (match_pattern(token, entry->d_name)) {
            matches[count] = strdup(entry->d_name);
            if (!matches[count]) {
                while (count-- > 0) free(matches[count]);
                free(matches);
                closedir(dir);
                return NULL;
            }
            count++;
        }
    }
    closedir(dir);
    matches[count] = NULL;
    return matches;
}

t_token *handel_wild_card(t_token *xpnd)
{
    t_token *result = NULL;
    t_token *new = NULL;
    char **res = NULL;
    int i;

    while (xpnd) {
        if (ft_strchr(xpnd->value, '*'))
		{
			res = expand_wildcard(xpnd->value ,xpnd->type);
            if (!res)
			{
                free_token_list(result);
                return NULL;
            }
			i = 0;
			
			while (res[i])
			{
				new = create_token(xpnd->type, res[i]);
				if (!new)
				{
					free_token_list(result);
					while (res[i]) free(res[i++]);
					free(res);
					return NULL;
				}
				append_list(&result, new);
				i++;
			}
            free(res);
        } 
        else
		{
            new = create_token(xpnd->type, ft_strdup(xpnd->value));
            if (!new)
			{
                free_token_list(result);
                return NULL;
            }
            append_list(&result, new);
        }
        xpnd = xpnd->next;
    }
    return result;
}

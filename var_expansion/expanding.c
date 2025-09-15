
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/07/04 20:35:36 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int replace_single_variable(char *str, int *i, char *result, int j, char **env)
{
    int start, k;
    char *var;
    char *val;

    start = *i;
    while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
        (*i)++;
    var = ft_substr(str, start, *i - start);
    val = get_env_value(var, env);
    k = 0;
    while (val && val[k])
        result[j++] = val[k++];
    free(var);
    free(val);
    return j;
}

int handle_dollars(char *str, int *i, char *result, int j, char **env)
{
    int count, mod;

    count = 0;
    while (str[*i + count] == '$')
        count++;
    mod = count / 2;
    while (mod--)
        j = double_dollars(result, j);
    if (count % 2 == 1)
    {
        *i += count;
        if (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
            j = replace_single_variable(str, i, result, j, env);
        else
            result[j++] = '$';
    }
    else
        *i += count;
    return j;
}

char *replace_in_arg(char *str, char **env)
{
    char    *result;
    int     i, j;

    result = malloc(4096);
    if (!result)
        return NULL;
    i = 0;
    j = 0;
    while (str[i])
    {
        if (str[i] == '$')
            j = handle_dollars(str, &i, result, j, env);
        else
            result[j++] = str[i++];
    }
    result[j] = '\0';
    return result;
}


char *expand(t_token *tokens, char **env)
{
	char *var_val;

	var_val = NULL;
	var_val = replace_in_arg(tokens->value,env);
	return(var_val);
}

void append_list(t_token **head, t_token *new_node)
{
	if (!*head)
		*head = new_node;
	else
	{
		t_token *temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
	}
}

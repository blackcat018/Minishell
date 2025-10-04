/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/20 19:45:12 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int has_unquoted_space(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (is_space_unquoted(str, i))
            return 1;
        i++;
    }
    return 0;
}

int handle_token(t_token *xpnd, t_token **result, t_token *prev)
{
    if (xpnd->type == VAR && has_unquoted_space(xpnd->value) &&
        (prev == NULL || prev->type != HERE_DOC))
        return split_var_token(xpnd, result);
    else
        return copy_token(xpnd, result);
}


int token_has_quotes(t_token *token)
{
    char quote_char = 0;

    int (i), (in_quotes);
    i = 0;
    in_quotes =0;
    while (token->value[i])
    {
        if (!in_quotes && (token->value[i] == '\'' || token->value[i] == '"'))
        {
            in_quotes = 1;
            quote_char = token->value[i];
        }
        else if (in_quotes && token->value[i] == quote_char)
        {
            in_quotes = 0;
            quote_char = 0;
        }
        else if (in_quotes && token->value[i] == '$')
            return 1;
        i++;
    }
    
    return 0;
}

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


int is_space_unquoted(char *str, int index)
{
    char quote_char = 0;

    int (i), (in_quotes);
    i = 0;
    in_quotes =0;
    while (i < index && str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            if (!in_quotes)
            {
                in_quotes = 1;
                quote_char = str[i];
            }
            else if (str[i] == quote_char)
            {
                in_quotes = 0;
                quote_char = 0;
            }
        }
        i++;
    }
    if (str[index] == ' ' && !in_quotes)
        return 1; 
    return 0;
}

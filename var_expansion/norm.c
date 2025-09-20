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

int handle_token(t_token *xpnd, t_token **result, t_token *prev)
{
    if (xpnd->type == VAR && ft_strchr(xpnd->value, ' ') &&
        (prev == NULL || prev->type != HERE_DOC))
        return split_var_token(xpnd, result);
    else
        return copy_token(xpnd, result);
}

int token_has_quotes(t_token *token)
{
    int i = 0;
    while (token->value[i])
    {
        if (token->value[i] == '\'' || token->value[i] == '"')
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
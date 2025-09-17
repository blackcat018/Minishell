/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stripping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:05:52 by moel-idr          #+#    #+#             */
/*   Updated: 2025/06/19 20:13:57 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

char	*strip_str(char *str)
{
	char	*res;
	int		i;
	int		k;
	char	quote;

	res = malloc(strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			quote = str[i++];
			while (str[i] && str[i] != quote)
				res[k++] = str[i++];
			if (str[i] == quote)
				i++;
		}
		else
			res[k++] = str[i++];
	}
	res[k] = '\0';
	return (res);
}

t_token	*stripper(t_token *xpnd)
{
	t_token	*result;
	t_token	*new;
	char	*res;

	result = NULL;
	while (xpnd)
	{
		if (!xpnd->var_nam)
			res = strip_str(xpnd->value);
		else
			res = ft_strdup(xpnd->value);
		if (!res)
			clear_tokens(&result);
		new = create_token(xpnd->type, res,xpnd->var_nam);
		if (!new)
		{
			free(res);
			clear_tokens(&result);
		}
		append_list(&result, new);
		free(res);
		xpnd = xpnd->next;
	}
	return (result);
}

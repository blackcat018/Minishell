/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_stripping.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:05:52 by moel-idr          #+#    #+#             */
/*   Updated: 2025/05/26 20:40:09 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"


char *strip_str(char *str)
{
    char *res = malloc(strlen(str) + 1);
    if (!res) 
		return NULL;
    int i = 0;
    int k = 0;
    while (str[i])
    {
        if (str[i] == '\'' || str[i] == '"')
        {
            char quote = str[i++];
            while (str[i] && str[i] != quote)
                res[k++] = str[i++];
            if (str[i] == quote)
                i++;
        }
        else
        {
            res[k++] = str[i++];
        }
    }
    res[k] = '\0';

    return res;
}

t_token *stripper(t_token *xpnd)
{
	t_token *result;
	t_token *new;
	char 	*res;

	result = NULL;
	while(xpnd)
	{
		res = strip_str(xpnd->value);
		new = create_token(xpnd->type,res);
		append_list(&result, new);
		xpnd = xpnd->next;
	}
	return(result);
}

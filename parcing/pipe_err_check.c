/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_err_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:43:08 by moel-idr          #+#    #+#             */
/*   Updated: 2025/06/27 02:54:41 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int pipe_err(t_token **list)
{
	t_token *curr = *list;
	t_token *last = NULL;

	if (curr && curr->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		clear_tokens(list);
		return (1);
	}
	while (curr)
	{
		if (curr->type == PIPE && curr->next && curr->next->type == PIPE)
		{
			printf("syntax error near unexpected token `|'\n");
			clear_tokens(list);
			return (1);
		}
		last = curr;
		curr = curr->next;
	}
	if (last && last->type == PIPE)
	{
		printf("syntax error near unexpected token `|'\n");
		clear_tokens(list);
		return (1);
	}
	return (0);
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/05/23 17:50:40 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

t_token *tokenizer(t_token **head, t_token **tail,char *input)
{
    int i = 0;
    
    while (input[i])
        {
            if (input[i] == ' ')
            {
                i++;
                continue;
            }
            if (input[i] == '|') 
                is_it_pipe(head, tail, &i, input);
			// else if (input[i] == '\'' || input[i] == '"')
			// 	is_it_quote(head, tail, &i, input,input[i]);
            else if (input[i] == '<' || input[i] == '>')
                is_it_op(head, tail, &i, input);
            else if (input[i] == '&')
                is_it_and(head, tail, &i, input);
            else
                is_it_word(head, tail, &i, input);
        }
        return(*head);
}
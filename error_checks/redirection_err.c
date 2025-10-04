/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_err_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 17:43:08 by moel-idr          #+#    #+#             */
/*   Updated: 2025/07/04 18:25:46 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"
int ft_isspace(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] != ' ' && str[i] != '\t')
            return 0;
        i++;
    }
    return 1;
}

int redir_check(t_token *token)
{
    if (!token)
    {
        printf("bash: syntax error near unexpected token `newline'\n");
        return(1);
    }
    if (is_token_redirect(token) || is_it_opp(token))
    {
        printf("syntax error near unexpected token `%s'\n", token->value);
        return(1);
    }
    
    if ((token->type == VAR || token->type == QUOTED_VAR) &&
        is_empty_string(token))
    {
        printf("bash: : ambiguous redirect\n");
        return(1);
    }
        if ((token->type == VAR || token->type == QUOTED_VAR) &&
        (ft_isspace(token->value) || (token->var_nam != NULL && token->next 
            &&token->var_nam == token->next->var_nam)))
    {
        printf("bash: : ambiguous redirect\n");
        return(1);
    }
	return(0);
}

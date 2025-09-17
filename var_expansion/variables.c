/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/17 21:18:43 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int token_has_quotes(t_token *token)
{
    int i = 0;
    while (token->value[i])
    {
        if (token->value[i] == '\'' || token->value[i] == '"')
            return 1; // contains quote
        i++;
    }
    return 0;
}

t_token *expand_token(t_token *token, char **envp)
{
    t_token *new;
    char *res;
    char *name = var_name(token->value);

    // Use handle_double only if token contains quotes
    if (token_has_quotes(token))
        res = handle_double(token, envp);
    else
        res = expand(token, envp);

    if (token_has_quotes(token))
        new = create_token(QUOTED_VAR, res, name);
    else
        new = create_token(VAR, res, name);

    free(res);
    return new;
}


t_token *expand_variables(t_token *tokens, char **envp)
{
    t_token *result;
    t_token *new;
    t_token *prev;

    result = NULL;
    prev = NULL;
    while (tokens)
    {
        if (is_it_var(tokens->value) && 
			!(prev && prev->type == HERE_DOC))
            new = expand_token(tokens, envp);
        else
            new = create_token(tokens->type, tokens->value, NULL);

        append_list(&result, new);
        prev = tokens;
        tokens = tokens->next;
    }
    return result;
}

int split_var_token(t_token *xpnd, t_token **result)
{
    char **tmp;
    t_token *new;
    int i;

    tmp = ft_split(xpnd->value, ' ');
    if (!tmp)
        return 0;
    i = 0;
    while (tmp[i])
    {
        new = create_token(VAR, tmp[i], xpnd->var_nam);
        if (!new)
        {
            free_split(tmp);
            return -1;
        }
        append_list(result, new);
        i++;
    }
    free_split(tmp);
    return 1;
}

int copy_token(t_token *xpnd, t_token **result)
{
    t_token *new;

    new = create_token(xpnd->type, xpnd->value, xpnd->var_nam);
    if (!new)
        return 0;
    append_list(result, new);
    return 1;
}

t_token *expanding_it(t_token *token, char **env)
{
    t_token *xpnd = expand_variables(token, env);
    t_token *result = NULL;
    t_token *prev = NULL;
    t_token *xpnd_head = xpnd;

    while (xpnd)
    {
        if (handle_token(xpnd, &result, prev) <= 0)
        {
            free_token_list(result);
            free_token_list(xpnd_head);
            return NULL;
        }
        prev = xpnd;
        xpnd = xpnd->next;
    }

    free_token_list(xpnd_head);
    return result;
}

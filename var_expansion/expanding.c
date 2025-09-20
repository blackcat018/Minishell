
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

int replace_single_variable(char *str, t_ctx *ctx, char *result, char **env)
{
    int start, k;
    char *var;
    char *val;

    start = ctx->i;
    while (str[ctx->i] && (ft_isalnum(str[ctx->i]) || str[ctx->i] == '_'))
        (ctx->i)++;
    var = ft_substr(str, start, ctx->i - start);
    val = get_env_value(var, env);
    k = 0;
    while (val && val[k])
        result[ctx->j++] = val[k++];
    free(var);
    free(val);
    return ctx->j;
}

int handle_dollars(char *str, t_ctx *ctx, char *result, char **env)
{
    int count, mod;

    count = 0;
    while (str[ctx->i + count] == '$')
        count++;
    mod = count / 2;
    while (mod--)
        ctx->j = double_dollars(result, ctx->j);
    if (count % 2 == 1)
    {
        ctx->i += count;
        if (str[ctx->i] && (ft_isalnum(str[ctx->i]) || str[ctx->i] == '_'))
            ctx->j = replace_single_variable(str, ctx, result, env);
        else
            result[ctx->j++] = '$';
    }
    else
        ctx->i += count;
    return ctx->j;
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
char *replace_in_arg(char *str, char **env)
{
    char    *result;
   	t_ctx     ctx;

    result = malloc(4096);
    if (!result)
        return NULL;
    ctx.i = 0;
    ctx.j = 0;
    while (str[ctx.i])
    {
        if (str[ctx.i] == '$')
            ctx.j = handle_dollars(str,&ctx, result, env);
        else
            result[ctx.j++] = str[ctx.i++];
    }
    result[ctx.j] = '\0';
    return result;
}

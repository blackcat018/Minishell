/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_replace.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/17 22:11:16 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int replace_variable(char *str, int *i, char *result, int j, char **env)
{
	char	*var;
	char	*val;
	int		start;
	int		k;

	start = ++(*i);
	while (str[*i] && (ft_isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	var = ft_substr(str, start, *i - start);
	val = get_env_value(var, env);
	k = 0;
	while (val && val[k])
		result[j++] = val[k++];
	free(var);
	free(val);
	return (j);
}
int handle_quotes(char *str, char *result, t_ctx *ctx)
{
    if (str[ctx->i] == '\'' && !ctx->in_double)
    {
        ctx->in_single = !ctx->in_single;
        result[ctx->j++] = str[ctx->i++];
        return (1);
    }
    if (str[ctx->i] == '"' && !ctx->in_single)
    {
        ctx->in_double = !ctx->in_double;
        result[ctx->j++] = str[ctx->i++];
        return (1);
    }
    return (0);
}

int handle_expansion(char *str, char *result, t_ctx *ctx, char **env)
{
    if (str[ctx->i] == '$' && str[ctx->i + 1] == '$' && !ctx->in_single)
    {
        ctx->j = double_dollars(result, ctx->j);
        ctx->i += 2;
        return (1);
    }
    if (str[ctx->i] == '$' && str[ctx->i + 1] == '"' && !ctx->in_single)
    {
        ctx->i++;
        return (1);
    }
    if (str[ctx->i] == '$' && !ctx->in_single &&
        (ft_isalnum(str[ctx->i + 1]) || str[ctx->i + 1] == '_'))
    {
        ctx->j = replace_variable(str, &ctx->i, result, ctx->j, env);
        return (1);
    }
    return (0);
}

char *replace_in_quotes(char *str, char **env)
{
    char *result;
	int (i),(j),(in_single),(in_double);
    i = 0;
	j = 0;
    in_single = 0;
	in_double = 0;
    
    result = malloc(4096);
    if (!result)
        return NULL;
    while (str[i])
    {
        if (str[i] == '\'' && !in_double)
        {
            in_single = !in_single;
            result[j++] = str[i++];
        }
        else if (str[i] == '"' && !in_single)
        {
            in_double = !in_double;
            result[j++] = str[i++];
        }
        else if (str[i] == '$' && !in_single)
        {
            if (str[i + 1] == '$')
            {
                j = double_dollars(result, j);
                i += 2;
            }
            else if (ft_isalnum(str[i + 1]) || str[i + 1] == '_')
                j = replace_variable(str, &i, result, j, env);
            else
                result[j++] = str[i++];
        }
        else
            result[j++] = str[i++];
    }
    result[j] = '\0';
    return result;
}

char *handle_double(t_token *token, char **env)
{
    char *expanded;
    char *final_result;
    
    expanded = replace_in_quotes(token->value, env);
    if (!expanded)
        return NULL;
    final_result = remove_quotes(expanded);
    free(expanded);
    
    return final_result;
}


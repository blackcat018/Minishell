/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_handle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:06:58 by moel-idr          #+#    #+#             */
/*   Updated: 2025/05/21 19:21:30 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

// int red_flag(t_token *token)
// {
// 	return( token->type == REDIR_IN);
// }

// int is_ambiguous_redirect(char *expanded)
// {
// 	if (!expanded || *expanded == '\0')
// 		return (1);
// 	if (ft_strchr(expanded, ' ') || ft_strchr(expanded, '\t'))
// 		return (1);
// 	return (0);
// }

// char *get_var_name(t_token *expanded, char **env)
// {
// 	int i = 0;
// 	char *equal_sign;
// 	char *value;
// 	char *key;

// 	while (env[i])
// 	{
// 		equal_sign = ft_strchr(env[i], '=');
// 		if (!equal_sign)
// 		{
// 			i++;
// 			continue;
// 		}
// 		value = equal_sign + 1;
// 		if (ft_strncmp(value, expanded->value,ft_strlen(value)) == 0)
// 		{
// 			int key_len = equal_sign - env[i];
// 			key = malloc(key_len + 1);
// 			if (!key)
// 				return NULL;
// 			ft_strlcpy(key, env[i], key_len + 1);
// 			return key;
// 		}
// 		i++;
// 	}
// 	return NULL;
// }


// void error_checks(t_token *prev, t_token *expnd,char **env, int flag)
// {
// 	char *var;

// 	var = get_var_name(expnd,env);
// 	if(prev && red_flag(prev) && flag == 1)
// 	{
// 		print_file_error(expnd->value);
// 		exit(g_exit_status);//done
// 	}
// 	if(prev && red_flag(prev) && !is_it_doubled(expnd) &&
// 	is_ambiguous_redirect(expnd->value))
// 	{
// 		print_ambiguous_redirect(var);
// 		exit(g_exit_status);//needs tweaking
// 	}
// 	if(prev && red_flag(prev) && flag == 0)
// 	{
// 		print_file_error(expnd->value);;
// 		exit(g_exit_status);//done
// 	}
// }

// void err_handle(t_token *xpnd, char **envp)
// {
// 	t_token *result;
// 	int	flag;
// 	t_token *prev;

// 	result = NULL;
// 	prev = NULL;
// 	flag = 0;
// 	while(xpnd)
// 	{
// 		if(xpnd->type == VAR || xpnd->type == QUOTED_VAR)
// 		{
// 			if (xpnd->type == QUOTED_VAR)
// 			{
// 				error_checks(prev,xpnd,envp,flag);
// 				flag = 1;
// 			}
// 			else if(xpnd->type == VAR)
// 			{
// 				error_checks(prev,xpnd,envp,flag);
// 				flag = 0;
// 			}
// 		}
// 		prev = xpnd;
// 		xpnd = xpnd->next;
// 	}
// }

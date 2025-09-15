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

char	*remove_quotes(char *value)
{
	int		i;
	int		j;
	char	*tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(value)));
	if (!tmp)
		return (NULL);
	i = 0;
	j = 0;
	while (value[i] != '\0')
	{
		if (value[i] != '"')
			tmp[j++] = value[i];
		i++;
	}
	tmp[j] = '\0';
	return (tmp);
}
char	*strip_token(char *value)
{
	int		i;
	int		quote_pos;

	quote_pos = -1;
	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] == '"')
		{
			quote_pos = i;
			break;
		}
		i++;
	}
	if (quote_pos == -1)
		return (ft_strdup(value));
	return (remove_quotes(value));
}
int double_dollars(char *result, int j)
{
    pid_t pid;
    char *res;
    int l;

    pid = getpid();
    res = ft_itoa((int)pid);
    l = 0;
    while (res[l])
        result[j++] = res[l++];
    free(res);
    return (j);
}
char *get_env_value(char *name, char **env)
{
	int i = 0;
	int len = ft_strlen(name);

	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			char *value_start = env[i] + len + 1;
			return ft_strdup(value_start);
		}
		i++;
	}
	return (NULL);
}

int handle_token(t_token *xpnd, t_token **result, t_token *prev)
{
    if (xpnd->type == VAR && ft_strchr(xpnd->value, ' ') &&
        (prev == NULL || prev->type != HERE_DOC))
        return split_var_token(xpnd, result);
    else
        return copy_token(xpnd, result);
}

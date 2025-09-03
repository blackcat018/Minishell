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

void free_split(char **strs)
{
    int i;

    i = 0;
    while(strs[i])
    {
        free(strs[i]);
        i++;
    }
    free(strs);
}

int is_ambiguous_redirect(char *expanded)
{
	if (!expanded || *expanded == '\0')
		return (1);
	if (ft_strchr(expanded, ' ') || ft_strchr(expanded, '\t'))
		return (1);
	return (0);
}
int is_it_var(char *str)
{
	if(ft_strchr(str,'$'))
		return (1);
	else 
		return (0);
}

int is_it_singled(t_token *token)
{
    int in_single = 0;
    int in_double = 0;
    int i = 0;

    if (token->type == DOUBLE_QU) {
        return 0;
    }

    while (token->value[i]) {
        if (token->value[i] == '\'' && !in_double) {
            in_single = !in_single;
        }
        else if (token->value[i] == '"' && !in_single) {
            in_double = !in_double;
        }
        else if (token->value[i] == '$' && in_single) {
            return 1;
        }
        i++;
    }
    return 0;
}

int is_it_doubled(t_token *token)
{
    int in_single = 0;
    int in_double = 0;
    int i = 0;

    if (token->type == SINGL_QU) {
        return 0;
    }

    while (token->value[i]) {
        if (token->value[i] == '"' && !in_single) {
            in_double = !in_double;
        }
        else if (token->value[i] == '\'' && !in_double) {
            in_single = !in_single;
        }
        else if (token->value[i] == '$' && in_double) {
            return 1;
        }
        i++;
    }
    return 0;
}

char *strip_token(char *value)
{
    int i = 0;
    int j = 0;
    char *tmp;
    int quote_pos = -1;

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
    {
        tmp = ft_strdup(value);
        return tmp;
    }
    tmp = malloc(sizeof(char) * (ft_strlen(value)));
    if (!tmp)
        return NULL;
    i = 0;
    while (value[i] != '\0')
    {
        if (value[i] != '"')
            tmp[j++] = value[i];
        i++;
    }
    tmp[j] = '\0';
    return tmp;
}

char *var_name(char *str)
{
    char *dollar;
    char *tmp;

	int (i), (j), (start);
	j = 0;
    tmp = ft_strchr(str, '$');
    if (!tmp)
        return NULL;
    start = 1;
    i = 0;
    while (tmp[start + i] && (ft_isalnum(tmp[start + i]) || tmp[start + i] == '_'))
        i++;
    dollar = malloc(sizeof(char) * (i + 1));
    if (!dollar)
        return NULL;
    while ( j < i)
	{
		dollar[j] = tmp[start + j];
		j++;
	}
    dollar[i] = '\0';
    return dollar;
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

char *replace_in_quotes(char *str, char **env)
{
    char *result = malloc(4096);
    if (!result) return NULL;

    int i = 0, j = 0;
    int in_single = 0;
    int in_double = 0;
    char *val = NULL;
    char *var = NULL;

    while (str[i]) {
        if (str[i] == '\'' && !in_double) {
            in_single = !in_single;
            result[j++] = str[i++];
            continue;
        }
        if (str[i] == '"' && !in_single) {
            in_double = !in_double;
            result[j++] = str[i++];
            continue;
        }
		if(str[i] == '$' && str[i + 1] && str[i+1] == '$' && !in_single)
		{
			j = double_dollars(result, j);
			i += 2;
		}
        if (str[i] == '$' && (!in_single || in_double) && str[i+1] && 
            (ft_isalnum(str[i+1]) || str[i+1] == '_')) {
            int start = ++i;
            while (str[i] && (ft_isalnum(str[i]) || str[i] == '_')) i++;
            
            var = ft_substr(str, start, i - start);
            val = get_env_value(var, env);
            
            int k = 0;
            while (val && val[k]) result[j++] = val[k++];

            free(var);
            free(val);
            var = NULL;
            val = NULL;
        } else {
            result[j++] = str[i++];
        }
    }
    result[j] = '\0';
    return result;
}

char *handle_double(t_token *token, char **env)
{
    char *stripped;
    char *var_val;
    
    if(check_quotes(token->value) == 3)
    {
        printf(REDD"minishell : unclosed quotes!\n"RESET);
        return NULL;
    }
    var_val = replace_in_quotes(token->value, env);
	stripped = strip_token(var_val);
    free(var_val);  // Don't forget to free stripped token
    return stripped;
}

char *replace_in_arg(char *str, char **env)
{
	char	*result;
	char	*var;
	char	*val;

	int (i),(j),(k), (start), (count), (mod);
	result = malloc(4096);
	if (!result)
		return NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if(str[i] == '$')
		{
			count = 0;
			while(str[i+count] == '$')
				count++;
			mod = count / 2;
			while(mod--)
				j = double_dollars(result,j);
			if(count % 2 == 1)
			{
				i += count;
				if(str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				{
					                start = i;
                while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
                    i++;
                var = ft_substr(str, start, i - start);
                val = get_env_value(var, env);
                k = 0;
                while (val && val[k])
                    result[j++] = val[k++];
                free(var);
                free(val);
				}
				else
				result[j++] = '$';
			}
			else
				i += count;
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (result);
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

int red_flag(t_token *token)
{
	return( token->type == REDIR_IN);
}
t_token *expand_variables(t_token *tokens, char **envp)
{
	t_token *result;
	t_token *new;
	int should_expand_vars;
	t_token *prev;
	char 	*res;
	char 	*name;

	result = NULL;
	prev = NULL;
	while(tokens)
	{
		should_expand_vars = !(prev && prev->type == HERE_DOC);
		if(is_it_var(tokens->value) == 1 && should_expand_vars)
		{
			if(is_it_singled(tokens))
			{
				name = var_name(tokens->value);
				res = handle_double(tokens,envp);
				new = create_token(QUOTED_VAR,res,name);
				free(res);
			}
				
			else if (check_quotes(tokens->value) == 2)
			{
				name = var_name(tokens->value);
				res = handle_double(tokens,envp);
				new = create_token(QUOTED_VAR,res,name);
				free(res);
			}
			else
			{
				name = var_name(tokens->value);
				res = expand(tokens,envp);
				new = create_token(VAR,res,name);
				free(res);
			}
		}
		else
			new = create_token(tokens->type, tokens->value,NULL);
		append_list(&result, new);
		prev = tokens;
		tokens = tokens->next;
	}
	return(result);
}

t_token *expanding_it(t_token *token, char **env)
{
	t_token *xpnd;
	t_token *result;
	t_token *new;
	t_token *prev;
	char **tmp;
	int i;

	result = NULL;
	new = NULL;
	tmp = NULL;
	prev = NULL;
	xpnd = expand_variables(token, env);
	t_token *xpnd_head = xpnd;
	while(xpnd)
	{
		if(xpnd->type == VAR && ft_strchr(xpnd->value, ' ') && 
		   (prev == NULL || prev->type != HERE_DOC))
		{
			i = 0;
			tmp = ft_split(xpnd->value, ' ');
			if(!tmp)
				return(NULL);
			while(tmp[i])
			{
				new = create_token(VAR, tmp[i],xpnd->var_nam);
				if (!new)
				{
					free_token_list(result);
					free_split(tmp);
					return NULL;
				}
				append_list(&result, new);
				i++;
			}
			free_split(tmp);
		}
		else
		{
			new = create_token(xpnd->type, xpnd->value,xpnd->var_nam);
			if (!new)
			{
				free_token_list(result);
				return NULL;
			}
			append_list(&result, new);
		}
		prev = xpnd;
		xpnd = xpnd->next;
	}
	free_token_list(xpnd_head);
	return(result);
}

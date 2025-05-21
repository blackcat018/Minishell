/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/05/21 02:44:43 by moel-idr         ###   ########.fr       */
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

int is_it_singled(t_token *dollar)
{
	int (i),(j);
	i = 0;
	j = 0;

	if(dollar->type == SINGL_QU)
	{
		if(dollar->quote_flag == 1)
			(printf(REDD "Minishell: unclosed quotes!" RESET),exit(1));
		return(1);
	}
	if(dollar->type == DOUBLE_QU)
		return(0);
	while(dollar->value[i])
	{
		if(dollar->value[i] == '\'' && dollar->value[i+1] == '$')
		{
			j = i;
			while(dollar->value[j])
			{
				if(dollar->value[j] == '\'')
					return(1);
				j++;
			}
			if(dollar->value[j] == '\0')
				(printf(REDD "Minishell: unclosed quotes!" RESET),exit(1));
		}
		i++;
	}
	return(0);
}
int is_it_doubled(t_token *dollar)
{
	int (i),(j);
	i = 0;
	j = 0;

	if(dollar->type == DOUBLE_QU)
	{
		if(dollar->quote_flag == 1)
			(printf(REDD "Minishell: unclosed quotes!" RESET),exit(1));
		return(1);
	}
	while(dollar->value[i])
	{
		if(dollar->value[i] == '"' && dollar->value[i+1] == '$')
		{
			j = i;
			while(dollar->value[j])
			{
				if(dollar->value[j] == '"')
					return(1);
				j++;
			}
			if(dollar->value[j] == '\0')
				(printf(REDD "Minishell: unclosed quotes!" RESET),exit(1));
		}
		i++;
	}
	return(0);
}

char *strip_token(char *value)
{
	int i;
	char *tmp;

	tmp = malloc(sizeof(char) * (ft_strlen(value)));
	if(!tmp)
		return(NULL);
	i = 1;
	while (value[i] != '"')
	{
		tmp[i - 1] = value[i];
		i++;
	}
	tmp[i - 1] = '\0';
	return(tmp);
}
void quoted_check(char *str)
{
	int i = 0, j = 0;
	char tmp;

	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			tmp = str[i];
			j = i + 1;
			while (str[j] && str[j] != tmp)
				j++;
			if (str[j] == '\0')
				(printf(REDD "Minishell: unclosed quotes!" RESET), exit(1));
			i = j;
		}
		i++;
	}
}

char *var_name(char *str)
{
    int i;
	int j;
    int start;
    char *dollar;
    char *tmp;

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

char *get_env_value(char *name, char **env)
{

	char **split;
	char *value;

	int (i),(len);
	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
		{
			split = ft_split(env[i], '=');//fix! you should start after the first '=' not split the thing
			if (split && split[1])
			{
				value = ft_strdup(split[1]);
				free_split(split);
				return value;
			}
			free_split(split);
		}
		i++;
	}
	return ft_strdup("");
}

char *replace_in_quotes(char *str, char **env)
{
	char *result;
	char *val;
	char *var;

	int (i),(j),(k),(start);
	j = 0;
	i = 0;
	result = malloc(4096);
	if (!result)
		return NULL;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
				i++;
			var = ft_substr(str, start, i - start);
			val = get_env_value(var, env);
			k = 0;
			while (val && val[k])
				result[j++] = val[k++];
			(free(var), free(val));
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (ft_strdup(result));
}


char *handle_double(t_token *token, char **env)
{
	char *tmp;
	char *var_val;
	char **res;

	int (i), (j);
	i = 0;
	j = 0;
	res = NULL;
	quoted_check(token->value);
	tmp = strip_token(token->value);
	if(!tmp)
		return(NULL);
	quoted_check(tmp);
	var_val = replace_in_quotes(tmp,env);
	return(var_val);
}

char *replace_in_arg(char *str, char **env)
{
	char	*result;
	char	*var;
	char	*val;

	int (i),(j),(k), (start);
	result = malloc(4096);
	if (!result)
		return NULL;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && (ft_isalnum(str[i + 1]) || str[i + 1] == '_'))
		{
			start = ++i;
			while (str[i] && (ft_isalnum(str[i]) || str[i] == '_') )
				i++;
			var = ft_substr(str, start, i - start);
			val = get_env_value(var, env);
			k = 0;
			while (val && val[k])
				result[j++] = val[k++];
			(free(var),free(val));
		}
		else
			result[j++] = str[i++];
	}
	result[j] = '\0';
	return (ft_strdup(result));
}

char *expand(t_token *tokens, char **env)
{
	char *var_val;
	char **res;

	int (i), (j);
	i = 0;
	j = 0;
	res = NULL;
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

void error_checks(t_token *prev, t_token *token,char *expanded, int flag)
{
		if(prev && red_flag(prev) && flag == 1)
		{
			print_file_error(expanded);
			exit(g_exit_status);
		}
		if(prev && red_flag(prev) && !is_it_doubled(token) &&
		is_ambiguous_redirect(expanded))
		{
			print_ambiguous_redirect(var_name(token->value));
			exit(g_exit_status);
		}
		if(prev && red_flag(prev) && !is_it_doubled(token))
		{
			print_file_error(expanded);;
			exit(g_exit_status);
		}
}

t_token *expand_variables(t_token *tokens, char **envp)
{
	t_token *result;
	t_token *new;
	int	flag;
	t_token *prev;
	char 	*res;

	result = NULL;
	prev = NULL;
	flag = 0;
	while(tokens)
	{
		if(is_it_var(tokens->value) == 1)
		{
			if(is_it_singled(tokens))
				new = create_token(tokens->type, ft_strdup(tokens->value));
			else if (is_it_doubled(tokens))
			{
				flag = 1;
				res = handle_double(tokens,envp);
				new = create_token(QUOTED_VAR,res);
				error_checks(prev,tokens,new->value,flag);
			}
			else
			{
				flag = 0;
				res = expand(tokens,envp);
				new = create_token(VAR,res);
				error_checks(prev,tokens,new->value,flag);
			}
		}
		else
			new = create_token(tokens->type, ft_strdup(tokens->value));
		append_list(&result, new);
		prev = tokens;
		tokens = tokens->next;
	}
	return(result);
}

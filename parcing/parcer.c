/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/06/26 16:44:31 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

int	is_token_cmd(t_token *T)
{
	return (T->type == COMMAND || T->type == CMD_ARG || T->type == SINGL_QU
		|| T->type == DOUBLE_QU || T->type == QUOTED_VAR || T->type == VAR);
}

int	is_token_redirect(t_token *R)
{
	return (R->type == REDIR_IN || R->type == REDIR_OUT || R->type == APPEND
		|| R->type == HERE_DOC);
}
int	arg_count(t_token *token, NodeType i)
{
	int	j;

	j = 0;
	while (token && token->type != i)
	{
		j++;
		token = token->next;
	}
	return (j);
}
int	redir_counter(t_token *token, NodeType i)
{
	int	j;

	j = 0;
	while (token && token->type != i)
	{
		if (is_token_redirect(token))
			j++;
		token = token->next;
	}
	return (j);
}
t_cmd	*store_cmds(t_token *token)
{
	t_cmd	*cmd;
	int		i;
	int		j;
	int		redir_count;

	i = 0;
	j = 0;
	redir_count = redir_counter(token, PIPE);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->argv = malloc(sizeof(char *) * (arg_count(token, PIPE) + 1));
	cmd->redirect = malloc(sizeof(char *) * (redir_count + 1));
	cmd->file = malloc(sizeof(char *) * (redir_count + 1));
	if (!cmd->argv || !cmd->redirect || !cmd->file)
		return (NULL);
	while (token && token->type != PIPE)
	{
		if (is_token_cmd(token))
			cmd->argv[i++] = ft_strdup(token->value);
		else if (is_token_redirect(token))
		{
			cmd->redirect[j] = ft_strdup(token->value);
			token = token->next;
			if (!token)
			{
				printf("bash: syntax error near unexpected token `newline'\n");
				exit(1);
			}
			cmd->file[j] = ft_strdup(token->value);
			j++;
		}
		token = token->next;
	}
	cmd->argv[i] = NULL;
	cmd->redirect[j] = NULL;
	cmd->file[j] = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*build_cmd_list(t_token *token)
{
	t_cmd *head;
	t_cmd *tail;
	t_cmd *cmd;

	head = NULL;
	cmd = NULL;
	tail = NULL;
	while (token)
	{
		cmd = store_cmds(token);
		if (!head)
			head = cmd;
		else
			tail->next = cmd;
		tail = cmd;
		while (token && token->type != PIPE)
			token = token->next;
		if (token && token->type == PIPE)
			token = token->next;
	}
	return (head);
}

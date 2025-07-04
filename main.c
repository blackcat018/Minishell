/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/07/04 20:06:41 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void print_tokens(t_token *tokens)
{
    while (tokens) {
        printf("Token is: %s\nType is: %d \nQuote flag is : %d\n\n"
				, tokens->value, tokens->type, tokens->quote_flag);
        tokens = tokens->next;
    }
}
void print_parse(t_cmd *cmd)
{
	while (cmd)
	{
		int i = 0;

		// Print command arguments
		while (cmd->argv && cmd->argv[i])
		{
			printf(RED "(commands) argv[%d]: %s\n" RESET, i, cmd->argv[i]);
			i++;
		}

		// Print redirects and corresponding files
		if (cmd->redirect && cmd->file)
		{
			i = 0;
			while (cmd->redirect[i] && cmd->file[i])
			{
				printf(YELLOW "Redirect[%d]: %s\n" RESET, i, cmd->redirect[i]);
				printf(SKYBLUE "File[%d]: %s\n" RESET, i, cmd->file[i]);
				i++;
			}
		}

		printf("----\n");
		cmd = cmd->next;
	}
}


void clear_tokens(t_token **head)
{
    t_token *tmp;

    while (*head)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp->value);  
        free(tmp); 
    }
}
void clear_cmd(t_cmd **head)
{
    t_cmd *tmp;
    int i;

    while (*head)
    {
        tmp = *head;
        *head = (*head)->next;

        if (tmp->argv)
        {
            i = 0;
            while (tmp->argv[i])
                free(tmp->argv[i++]);
            free(tmp->argv);
        }

        if (tmp->redirect)
        {
            i = 0;
            while (tmp->redirect[i])
                free(tmp->redirect[i++]);
            free(tmp->redirect);
        }

        if (tmp->file)
        {
            i = 0;
            while (tmp->file[i])
                free(tmp->file[i++]);
            free(tmp->file);
        }

        free(tmp);
    }
}
void ff()
{
	system("leaks minishell");
}
int main(int ac, char ** av, char **env)
{
    char *input;
    t_token *head = NULL;
    t_token *tail = NULL;
    t_token *output = NULL;
	t_token *expand = NULL;
	t_token *wild = NULL;
	t_token *strip = NULL;
	t_cmd *cmd = NULL;
    
	atexit(ff);
	(void)ac;
	(void)av;
	// (void)env;
    while (1)
    {
        head = NULL;
        tail = NULL;
        input = readline("\033[1;96m minishell > \033[0m");
        if (!input)
        {
            printf("exit\n");
            break;
        }

        if (*input)
            add_history(input);
        tail = NULL;
		output = tokenizer(&head,&tail,input);
		expand = expanding_it(output,env);
		wild = handel_wild_card(expand);
		strip = stripper(wild);
		cmd = build_cmd_list(strip);
		print_parse(cmd);
		// print_tokens(output);
		clear_tokens(&output);
		clear_tokens(&expand);
		clear_tokens(&wild);
		clear_tokens(&strip);
		clear_cmd(&cmd);
       free(input);
    }
    return 0;
}


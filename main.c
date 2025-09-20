/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/09/20 19:40:02 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void print_tokens(t_token *tokens)//just for testing
{
    while (tokens) {
        printf("\n\nToken is: %s\n"
				, tokens->value);
        tokens = tokens->next;
    }
}
void print_parse(t_cmd *cmd)//just for testing 
{
    int i;

	while (cmd)
	{
        i = 0;
		while (cmd->argv && cmd->argv[i])
		{
			printf(RED "(commands) argv[%d]: %s\n" RESET, i, cmd->argv[i]);
			i++;
		}
		if (cmd->redirect && cmd->file)
		{
			i = 0;
			while (cmd->redirect[i] && cmd->file[i])
			{
				printf(YELLOW "Redirect[%d]: %s\n" RESET, i, cmd->redirect[i]);
				printf(SKYBLUE "File[%d]: %s\n" RESET, i, cmd->file[i]);
				printf("\n\n\n\n");
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
char *get_input(void)
{
    char *input = readline("\033[1;96m minishell > \033[0m");
    if (!input)
    {
        printf("exit\n");
        return NULL;
    }
    if (*input)
        add_history(input);
    return input;
}

void free_token_lists(t_token **output, t_token **expand,
                      t_token **wild, t_token **strip)
{
    clear_tokens(output);
    clear_tokens(expand);
    clear_tokens(wild);
    clear_tokens(strip);
}

void process_line(char *input, char **env)
{
    t_token *head   = NULL;
    t_token *tail   = NULL;
    t_token *output = NULL;
    t_token *expand = NULL;
    t_token *wild   = NULL;
    t_token *strip  = NULL;
    t_cmd   *cmd    = NULL;

    output = tokenizer(&head, &tail, input);
    expand = expanding_it(output, env);
    wild   = handel_wild_card(expand);
    strip  = stripper(wild);
    cmd    = build_cmd_list(strip);

    if (cmd)
        print_parse(cmd);
	// print_tokens(output);
    free_token_lists(&output, &expand, &wild, &strip);
    if (cmd)
        clear_cmd(&cmd);
}
int check_unclosed_quotes(const char *line)
{
    int in_single = 0;
    int in_double = 0;
    int i = 0;

    while (line[i])
    {
        if (line[i] == '\'' && !in_double)
            in_single = !in_single;
        else if (line[i] == '"' && !in_single)
            in_double = !in_double;
        i++;
    }
    return (in_single || in_double);
}
char *read_complete_line(void)
{
    char *line = readline("\033[1;96m minishell > \033[0m");
    if (!line)
    {
        printf("exit\n");
        return NULL;
    }
    if (*line)
        add_history(line);
    while (check_unclosed_quotes(line))
    {
        char *more = readline("> ");
        if (!more) 
        {
            printf("bash: unexpected EOF while looking for matching quote\n"
                    "bash: syntax error: unexpected end of file\n");
            free(line);
            return NULL;
        }
        char *tmp = ft_strjoin(line, "\n");
        char *joined = ft_strjoin(tmp, more);
        free(line);
        (free(tmp), free(more));
        line = joined;
    }
    return line;
}

int main(int ac, char **av, char **env)
{
    char *input;

    (void)ac;
    (void)av;

    while (1)
    {
        input = read_complete_line();
        if (!input)
            break;

        process_line(input, env);
        free(input);
    }
    clear_history();
    return 0;
}



/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:41:01 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 20:33:49 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void print_tokens(t_token *tokens)
{
    while (tokens) {
        printf("Token: %s \n", tokens->value);
        tokens = tokens->next;
    }
}

void clear_tokens(t_token **head)
{
    t_token *tmp;

    while (*head)
    {
        tmp = *head;
        *head = (*head)->next;
        free(tmp->value);  // Free the token value
        free(tmp);         // Free the token node
    }
}

int main(void)
{
    char *input;
    int i = 0;
    t_token *head = NULL;
    t_token *tail = NULL;
    
    while (1)
    {
        input = readline("\033[1;32mminishell > \033[0m");

        if (!input)
        {
            printf("exit\n");
            break;
        }

        if (*input)
            add_history(input);
        i = 0;
        tail = NULL;
        while (input[i])
        {
            if (input[i] == ' ')
            {
                i++;
                continue;
            }
            if (input[i] == '|') 
                is_it_pipe(&head, &tail, &i);
            else if (input[i] == '\'' || input[i] == '\"')
                is_it_quote(&head, &tail, &i, input, input[i]);
            else if (input[i] == '<' || input[i] == '>')
                is_it_op(&head, &tail, &i, input); // ✅ correct
            else
                is_it_word(&head, &tail, &i, input);
        }
        print_tokens(head);
        clear_tokens(&head);
        free(input);
    }
    return 0;
}


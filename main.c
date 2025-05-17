/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:41:01 by codespace         #+#    #+#             */
/*   Updated: 2025/05/17 16:00:23 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes.h"

void print_tokens(t_token *tokens)
{
    while (tokens) {
        printf("Token: %s       and its type is: %d \n", tokens->value, tokens->type);
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
        free(tmp->value);  
        free(tmp); 
    }
}

int main(void)
{
    char *input;
    t_token *head = NULL;
    t_token *tail = NULL;
    t_token *output = NULL;
    
    while (1)
    {
        head = NULL;
        tail = NULL;
        input = readline("\033[1;32mminishell > \033[0m");

        if (!input)
        {
            printf("exit\n");
            break;
        }

        if (*input)
            add_history(input);
        tail = NULL;
       output = tokenizer(&head,&tail,input);
       print_tokens(output);
       clear_tokens(&output);
       free(input);
    }
    return 0;
}


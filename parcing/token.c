/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:07:10 by codespace         #+#    #+#             */
/*   Updated: 2025/05/17 16:25:08 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"
/*
we will have to go over the command char by char and when we ever encounter
an operator  (|, >, <, >>, <<), a whitespace single or double quotes, we make a token!
the operators are tokens themselves!
if we stumbel upon "" or '' we make a cheackpoint at the start of the quote untill 
we reach the end of it ! ad whatecer is in between we treat it as a token (script, string...)
the tokenizer returns a linked list or a simple array that we then pass to the parcer!
*/


// |
void is_it_pipe(t_token **head, t_token **tail, int *i, char *input)
{
    t_token *new;
    if(input[*i] == '|' && input[*i+1] == '|' )
    {
        new = create_token(AND, "||");
        *i += 1;
    } 
    else
        new = create_token(PIPE, "|");
    if (!new)
        return;
    if (!*head)
        *head = new;
    else
        (*tail)->next = new;
    *tail = new;
    (*i)++;
}

void is_it_and(t_token **head, t_token **tail, int *i, char *input)
{
    t_token *new;
    if(input[*i] == '&' && input[*i+1] == '&' )
    {
        new = create_token(AND, "&&");
        *i += 1;
    }
    if (!new)
        return;
    if (!*head)
        *head = new;
    else
        (*tail)->next = new;
    *tail = new;
    (*i)++;
}

int is_token_breaker(char c) {
    return (c == ' ' || c == '|' || c == '\'' || c == '"' ||
            c == '<' || c == '>' || c == ';' || c == '`');
}

void is_it_word(t_token **head, t_token **tail, int *i, char *input)
{
    t_token *new;
    char *tmp;

    int (len), (start), (j);
    len = 0;
    j = 0;
    start = *i;
    while (input[*i] && !is_token_breaker(input[*i]))
    {
        (*i)++;
        len++;
    }
    tmp = malloc(sizeof(char) * (len + 1));
    if (!tmp)
        return;
    while (j < len)
    {
        tmp[j] = input[start + j];
        j++;
    }
    tmp[len] = '\0';
    if(input[start] == '-')
        new = create_token(CMD_ARG, tmp);
    else
        new = create_token(COMMAND, tmp);
    free(tmp);
    if (!new)
        return;
    if (!*head)
        *head = new;
    else
        (*tail)->next = new;
    *tail = new;
    // (*i)++;
}

// >> , > , < , <<
void is_it_op(t_token **head, t_token **tail, int *i, char *input)
{
    t_token *new;
    
    if(input[*i] == '<' && input[*i+1] == '<' )
    {
        new = create_token(HERE_DOC, "<<");
        *i += 1;
    }  
    else if(input[*i] == '>' && input[*i+1] == '>')
    {
        new = create_token(APPEND, ">>");
        *i += 1;
    }
    else if(input[*i] == '>')
        new = create_token(REDIR_OUT, ">");
    else if(input[*i] == '<')
        new = create_token(REDIR_IN, "<");
    if (!new)
        exit(1);
    if (!*head)
        *head = new;
    else
        (*tail)->next = new;
    *tail = new;
    (*i)++;
}

//""   ''
void is_it_quote(t_token **head, t_token **tail, int *i, char *input, char c)
{
    t_token *new;
    char *tmp;
    int start;
    int j;

    j = 0;
    (*i)++;
    start = *i;
    if (c == '"') {
        while (input[*i]) {
            if (input[*i] == '\\' && input[*i + 1])
                (*i) += 2;
            else if (input[*i] == c)
                break;
            else
                (*i)++;
        }
    } else {
        while (input[*i] && input[*i] != c) {
            (*i)++;
        }
    }    
    if(input[*i] != c)
    {
        ft_putstr_fd("minishell: unclosed quote\n",2);   ///////handel error
        exit(1);
    }
    tmp = malloc(sizeof(char) * ((*i) - start + 1));
    if(!tmp)
        return;
    while(j < *i - start)
    {
        tmp[j] = input[start +j];
        j++;
    }
    tmp[j] = '\0';
    new = create_token(QUOTES, tmp);
    if (!new)
        return;
    if (!*head)
    *head = new;
    else
        (*tail)->next = new;
    *tail = new;
    (*i)++;
    free(tmp);
}



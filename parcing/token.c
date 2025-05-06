/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:07:10 by codespace         #+#    #+#             */
/*   Updated: 2025/05/06 20:35:41 by codespace        ###   ########.fr       */
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

t_token *create_token(e_token type, char *value)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if(!new_token)
        return(NULL);
    new_token->value = ft_strdup(value);
    new_token->type = type;
    new_token->next = NULL;
    return(new_token);
}


// |
void is_it_pipe(t_token **head, t_token **tail, int *i)
{
    t_token *new;

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

void is_it_word(t_token **head, t_token **tail, int *i, char *input)
{
    t_token *new;
    char *tmp;

    int (len), (start), (j);
    len = 0;
    j = 0;
    start = *i;
    while (input[*i] 
         && input[*i] != ' ' 
         && input[*i] != '|'
         && input[*i] != '\''
         && input[*i] != '<'
         && input[*i] != '>')
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
    new = create_token(WORD, tmp);
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
        new = create_token(OPS, "<<");
        *i += 1;
    }  
    else if(input[*i] == '>' && input[*i+1] == '>')
    {
        new = create_token(OPS, ">>");
        *i += 1;
    }
    else if(input[*i] == '>')
        new = create_token(OPS, ">");
    else if(input[*i] == '<')
        new = create_token(OPS, "<");
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
    while(input[*i] != c && input[(*i)])
        (*i)++;
    if(input[*i] != c)
    {
        ft_putstr_fd("minishell: unclosed quote\n",2);
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
    new = create_token(QUOTED_STRING, tmp);
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






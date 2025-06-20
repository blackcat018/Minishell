/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 17:45:21 by moel-idr          #+#    #+#             */
/*   Updated: 2025/06/19 17:06:27 by moel-idr         ###   ########.fr       */
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
        new = create_token(OR, "||");
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

int is_token_breaker(char c) {
    return (c == ' ' || c == '|'||
            c == '<' || c == '>');
}
void flag_check(char start, char end, t_token *token, int type)
{
	if (type == SINGL_QU || type == DOUBLE_QU)
	{
		if(start == end)
			token->quote_flag = 0;
		else if (start != end)
			token->quote_flag = 1;
		else 
		token->quote_flag = 0;
	}
}

void is_it_word(t_token **head, t_token **tail, int *i, char *input)
{
    t_token *new;
    char *tmp;

    int (len), (start), (j);
    len = 0;
    j = 0;
    start = *i;
	int in_quote = 0;
	char quote_type = 0;
	while (input[*i])
	{
		if (!in_quote && is_token_breaker(input[*i]))
			break;

		if ((input[*i] == '"' || input[*i] == '\''))
		{
			if (!in_quote)
			{
				in_quote = 1;
				quote_type = input[*i];
			}
			else if (quote_type == input[*i])
			{
				in_quote = 0;
			}
	}

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
	else if (input[start] == '"')
		new = create_token(DOUBLE_QU, tmp);
	else if (input[start] == '\'')
		new = create_token(SINGL_QU, tmp);
    else
        new = create_token(COMMAND, tmp);
	flag_check(input[start], tmp[len - 1],new,new->type);
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
    
	new = NULL;
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

// ""   ''
// void is_it_quote(t_token **head, t_token **tail, int *i, char *input, char c)
// {
//     t_token *new;
//     char *tmp;
//     int start;
//     int j;

//     j = 0;
//     (*i)++;
//     start = *i - 1;
//     if (c == '"')
// 	{
//         while (input[*i])
// 		{
//             if (input[*i] == c)
//                 break;
//             else
//                 (*i)++;
//         }
//     } else {
//         while (input[*i] && input[*i] != c) {
//             (*i)++;
//         }
//     }    
//     if(input[*i] != c)
//     {
//         ft_putstr_fd("minishell: unclosed quote\n",2);
//         exit(1);
//     }
// 	(*i)++;
//     tmp = malloc(sizeof(char) * ((*i) - start + 1));
//     if(!tmp)
//         return;
//     while(j < *i - start)
//     {
//         tmp[j] = input[start +j];
//         j++;
//     }
//     tmp[j] = '\0';
// 	if(c == '"')
// 		new = create_token(DOUBLE_QU, tmp);
//     else 
// 		new = create_token(SINGL_QU, tmp);
//     if (!new)
//         return;
//     if (!*head)
//     *head = new;
//     else
//         (*tail)->next = new;
//     *tail = new;
//     free(tmp);
// }



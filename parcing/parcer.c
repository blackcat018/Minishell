/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:00:54 by codespace         #+#    #+#             */
/*   Updated: 2025/05/17 16:15:14 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

// binary parsing!!

// t_trs *parse_cmd(t_token **tokens)
// {
//     t_trs *cmd_node;
//     if (!tokens || !*tokens)
//         return NULL;
//     cmd_node = create_node(NULL);
//     cmd_node->type = COMMAND;
//     while(*tokens && !is_operator(*tokens))
//     {
//         add_arg(cmd_node, (*tokens)->value);
//         *tokens = (*tokens)->next;
//     }
//     return(cmd_node);
// }

// t_trs *parse_redirection(t_trs *left, t_token **tokens)
// {
//     t_trs *right_node;
//     t_trs *redir;

//     if(!tokens || !*tokens)
//         exit(1);
//     if(!left)
//         left = parse_cmd(tokens);
//     while(*tokens && (*tokens)->type == REDIRECT)
//     {
//         redir = create_node((*tokens)->value);
//         redir->type = REDIRECT;
//         *tokens = (*tokens)->next;
//         if(*tokens && (*tokens)->type == COMMAND)
//         {
//             right_node = create_node((*tokens)->value);
//             right_node->type = COMMAND;
//             *tokens = (*tokens)->next;
//             redir->left = left;
//             redir->right = right_node;
//             left = redir;
//         }
//     }
//     return(left);
// }

// t_trs *parse_pipe(t_token **tokens)
// {
//     t_trs *left;
//     t_trs *right;
//     t_trs *pipe_node;

//     left = parse_cmd(tokens);
//     left = parse_redirection(left,tokens);
//     while(*tokens && (*tokens)->type == PIPE)
//     {
//         *tokens = (*tokens)->next;
//         right = parse_cmd(tokens);
//         right = parse_redirection(right,tokens);
//         pipe_node = create_node("|");
//         pipe_node->type = PIPE;
//         pipe_node->right = right;
//         pipe_node->left = left;
//         left = pipe_node;
//     }
//     return(left);
// }

// t_trs *parse_logical(t_token **tokens)
// {
//     t_trs *left;
//     t_trs *right;
//     t_trs *logical_node;

//     left = parse_pipe(tokens);
    
//     while(*tokens && ((*tokens)->type == AND || (*tokens)->type == OR))
//     {
//         logical_node = create_node((*tokens)->value);
//         if ((*tokens)->type == AND)
// 	        logical_node->type = AND;
//         else
// 	        logical_node->type = OR;
//         *tokens = (*tokens)->next;
//         right = parse_pipe(tokens);
//         logical_node->left = left;
//         logical_node->right = right;
//         left = logical_node;
//     }
    
//     return left;
// }



// linked list parsing


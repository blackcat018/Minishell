/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moel-idr <moel-idr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 20:36:28 by moel-idr          #+#    #+#             */
/*   Updated: 2025/05/22 19:30:06 by moel-idr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

// void	print_cmd_not_found(char *cmd)
// {
// 	if (!cmd)
// 		cmd = "";
// 	ft_putstr_fd("bash: ", STDERR_FILENO);
// 	ft_putstr_fd(cmd, STDERR_FILENO);
// 	ft_putstr_fd(": command not found\n", STDERR_FILENO);
// 	g_exit_status = 127;
// }


// void	print_ambiguous_redirect(char *var_name)
// {
// 	ft_putstr_fd("bash: $", STDERR_FILENO);
// 	ft_putstr_fd(var_name, STDERR_FILENO);
// 	ft_putstr_fd(": ambiguous redirect\n", STDERR_FILENO);
// 	g_exit_status = 1;
// }


// void	print_file_error(char *filename)
// {
// 	ft_putstr_fd("bash: ", STDERR_FILENO);
// 	ft_putstr_fd(filename, STDERR_FILENO);
// 	ft_putstr_fd(": ", STDERR_FILENO);
// 	ft_putstr_fd("No such file or directory", STDERR_FILENO);
// 	ft_putstr_fd("\n", STDERR_FILENO);
// 	g_exit_status = 1;
// }


// void	print_syntax_error(char *token)
// {
// 	ft_putstr_fd("bash: syntax error near unexpected token `", STDERR_FILENO);
// 	ft_putstr_fd(token, STDERR_FILENO);
// 	ft_putstr_fd("'\n", STDERR_FILENO);
// 	g_exit_status = 2;
// }


// void	print_command_error(char *cmd, char *error_msg)
// {
// 	ft_putstr_fd("bash: ", STDERR_FILENO);
// 	ft_putstr_fd(cmd, STDERR_FILENO);
// 	ft_putstr_fd(": ", STDERR_FILENO);
// 	ft_putstr_fd(error_msg, STDERR_FILENO);
// 	ft_putstr_fd("\n", STDERR_FILENO);
// }


// void	print_system_error(char *context)
// {
// 	ft_putstr_fd("bash: ", STDERR_FILENO);
// 	if (context)
// 	{
// 		ft_putstr_fd(context, STDERR_FILENO);
// 		ft_putstr_fd(": ", STDERR_FILENO);
// 	}
// 	ft_putstr_fd(strerror(errno), STDERR_FILENO);
// 	ft_putstr_fd("\n", STDERR_FILENO);
// }
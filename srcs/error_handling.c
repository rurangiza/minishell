/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:47:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/16 17:12:57 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_execution_errors(t_token *token)
{
	if (ft_strlen(token->cmd[0]) == 1)
		{
			if (token->cmd[0][0] == '.')
				exitmsg(": filename argument required\n.: usage: . filename [arguments]", token->cmd[0], 2);
			else if (token->cmd[0][0] == '~' || token->cmd[0][0] == '/')
				exitmsg(": is a directory", token->cmd[0], 126);
			else if (token->cmd[0][0] == '*')
				exitmsg(": command not found", "Makefile", 127);
		}
		if (token->cmd[0][0])
		{
			if (is_unexpected_token(token->cmd[0]))
				exitmsg(": syntax error near unexpected token", token->cmd[0], 258);
			if (token->cmd[0][0] == '%')
				exitmsg(": no such job", token->cmd[0], 1);
		}
		if (token->cmd_path == NULL)
		{
			if (ft_strlen(token->cmd[0]) >= 2 && ft_strncmp("./", token->cmd[0], 2) == 0)
			{
				// if "./" -> bash: ./: is a directory
				if (is_directory(token->cmd[0], token->stats))
					exitmsg(": is a directory", token->cmd[0], 126);
				if (!is_executable(token->cmd[0], token->stats))
					exitmsg(": Permissing denied", token->cmd[0], 126);
				execve(token->cmd[0], token->cmd, g_environment);
				exitmsg(": No such file or directory", token->cmd[0], 127);
			}
			exitmsg(": command not found", token->cmd[0], 127);
		}
		//exit(0);
}
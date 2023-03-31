/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:47:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/31 13:07:24 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handle_execution_errors(t_token *token, t_prompt *prompt)
{
	if (!token->cmd)
		exit(0) ;
	if (ft_strlen(token->cmd[0]) == 0)
		exitmsg(": command not found", token->cmd[0], 127);
	if (ft_strlen(token->cmd[0]) == 1)
	{
		if (token->cmd[0][0] == '.')
			exitmsg(": filename argument required\n.: usage: . filename [arguments]", token->cmd[0], 2);
		else if (token->cmd[0][0] == '~' || token->cmd[0][0] == '/')
			exitmsg(": is a directory", token->cmd[0], 126);
		else if (token->cmd[0][0] == '*')
			exitmsg(": command not found", "Makefile", 127);
	}
	if (token->cmd[0] && token->cmd[0][0])
	{
		if (is_unexpected_token(token->cmd[0]))
			exitmsg(": syntax error near unexpected token", token->cmd[0], 258);
		if (token->cmd[0][0] == '%')
			exitmsg(": no such job", token->cmd[0], 1);
	}
	if (token->cmd_path == NULL)
	{
		if (token->cmd[0] && token->cmd[0][0] == '/' && access(token->cmd[0], 0) == 0)
			execve(token->cmd[0], token->cmd, prompt->envp);
		if (ft_strlen(token->cmd[0]) >= 2 && ft_strncmp("./", token->cmd[0], 2) == 0)
		{
			if (is_directory(token->cmd[0], token->stats))
				exitmsg(": is a directory", token->cmd[0], 126);
			if (!is_executable(token->cmd[0], token->stats))
				exitmsg(": Permissing denied", token->cmd[0], 126);
			execve(token->cmd[0], token->cmd, prompt->envp);
			exitmsg(": No such file or directory", token->cmd[0], 127);
		}
		if (token->cmd && token->cmd[0])
			exitmsg(": command not found", token->cmd[0], 127);
		else
			exitmsg(": command not found", "unknown", 127);
	}
	//exit(0);
}
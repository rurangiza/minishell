/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 16:47:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/21 14:44:18 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_executable(char *path)
{
	struct stat	stat_buffer;

	if (ft_strncmp("./", path, 2) == 0)
	{
		if (stat(path + 2, &stat_buffer) == -1)
			return (FALSE);
		return ((stat_buffer.st_mode & S_IXUSR) != 0);
	}
	return (FALSE);
}

static int	is_directory(char *path)
{
	int			file_status;
	struct stat	stat_buffer;

	file_status = stat(path + 2, &stat_buffer);
	if (file_status == 0)
	{
		if (S_ISDIR(stat_buffer.st_mode))
			return (TRUE);
		return (FALSE);
	}
	return (FALSE);
}

static int	is_unexpected_token(char *token)
{
	if (!token && !token[0])
		return (-1);
	if (token[0] == ')' || token[0] == '&' || token[0] == '}')
		return (TRUE);
	return (FALSE);
}

static void	handle_mostcases(t_token *token, t_prompt *prompt)
{
	if (token->cmd[0] && token->cmd[0][0] == '/'
		&& access(token->cmd[0], 0) == 0)
		execve(token->cmd[0], token->cmd, prompt->envp);
	if (ft_strlen(token->cmd[0]) >= 2
		&& ft_strncmp("./", token->cmd[0], 2) == 0)
	{
		if (is_directory(token->cmd[0]))
			exitmsg(": is a directory", token->cmd[0], 126);
		if (!is_executable(token->cmd[0]))
			exitmsg(": Permissing denied", token->cmd[0], 126);
		execve(token->cmd[0], token->cmd, prompt->envp);
		exitmsg(": No such file or directory", token->cmd[0], 127);
	}
	if (token->cmd && token->cmd[0])
		exitmsg(": command not found", token->cmd[0], 127);
	else
		exitmsg(": command not found", "unknown", 127);
}

void	handle_execution_errors(t_token *token, t_prompt *prompt)
{
	if (token->infile == ERR_FD || token->outfile == ERR_FD)
		exitmsg(": No such file or directory", token->cmd[0], 127);
	if (!token->cmd)
		exit(0);
	if (ft_strlen(token->cmd[0]) == 0)
		exitmsg(": command not found", token->cmd[0], 127);
	if (ft_strlen(token->cmd[0]) == 1)
	{
		if (token->cmd[0][0] == '.')
			exitmsg(": filename argument required\n", token->cmd[0], 2);
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
		handle_mostcases(token, prompt);
}

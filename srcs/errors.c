/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:32:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/16 16:35:08 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_msg(void)
{
	perror("minishell");
	exit(errno);
}

void	exitmsg(char *msg, char *cmd, int code)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (cmd[0] && cmd[0] == '%')
		write(STDERR_FILENO, "fg: ", 4);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, "\n", 1);
	exit(code);
}


void	exit_wrongcmd_msg(char *cmd, int error_code)
{
	write(STDERR_FILENO, "minishell: ", 11);
	if (error_code == 126)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": Permission denied\n", 20);
	}
	else if (ft_strncmp("./", cmd, 2) == 0)
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": No such file or directory\n", 27); 
	}
	else if (cmd[0] && cmd[0] == '%')
	{
		write(STDERR_FILENO, "fg: ", 4);
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": no such job\n", 14);
		exit(1);
	}
	else
	{
		write(STDERR_FILENO, cmd, ft_strlen(cmd));
		write(STDERR_FILENO, ": command not found\n", 20);
	}
	exit(error_code);
}

void	exit_nofile_msg(char *filename)
{
	write(2, "minishell: no such file or directory: ", 38);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
	exit(0);
}
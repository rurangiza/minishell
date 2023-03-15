/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:32:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/15 15:41:01 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_msg(void)
{
	perror("minishell");
	exit(errno);
}

void	exit_wrongcmd_msg(char *cmd, int error_code)
{
	write(2, "minishell: command not found: ", 30);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	exit(error_code);
}

void	exit_nofile_msg(char *filename)
{
	write(2, "minishell: no such file or directory: ", 38);
	write(2, filename, ft_strlen(filename));
	write(2, "\n", 1);
	exit(0);
}
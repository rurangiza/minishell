/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/14 16:32:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/03 17:02:36 by arurangi         ###   ########.fr       */
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
	if (cmd && cmd[0] && cmd[0] == '%')
		write(STDERR_FILENO, "fg: ", 4);
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (ft_strncmp(": filename", msg, 10) == 0)
		write(STDERR_FILENO, ".: usage: . filename [arguments]\n", 33);
	write(STDERR_FILENO, "\n", 1);
	exit(code);
}

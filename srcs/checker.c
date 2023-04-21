/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 13:50:23 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/21 11:14:02 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* check whether a string {cmd} matches with the list of built-ins */
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (FALSE);
	if ((ft_strncmp(cmd, "echo", 4) == 0 && !cmd[4])
		|| (ft_strncmp(cmd, "cd", 2) == 0 && !cmd[2])
		|| (ft_strncmp(cmd, "pwd", 3) == 0 && !cmd[3])
		|| (ft_strncmp(cmd, "export", 6) == 0 && !cmd[6])
		|| (ft_strncmp(cmd, "unset", 5) == 0 && !cmd[5])
		|| (ft_strncmp(cmd, "env", 3) == 0 && !cmd[3])
		|| (ft_strncmp(cmd, "exit", 4) == 0 && !cmd[4]))
		return (TRUE);
	return (FALSE);
}

int	is_path_alias(char *directory)
{
	if (ft_strlen(directory) == 1
		&& (directory[0] == '-'
			|| directory[0] == '~'
			|| directory[0] == '/'))
	{
		return (1);
	}
	return (0);
}

int	is_empty_pipe(int read_end)
{
	int	nbytes;

	if (ioctl(read_end, FIONREAD, &nbytes) < 0)
		return (-1);
	else if (nbytes == 0)
		return (1);
	return (0);
}

void	check_user_input(char *input)
{
	if (!input)
		exit (130);
}

void	check_cmds_status(t_token *token, t_prompt *prompt)
{
	int	i;
	int	status;

	i = 0;
	while (i < prompt->pipe_nb)
	{
		waitpid(prompt->saved_pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_exitcode = WEXITSTATUS(status);
			if (WEXITSTATUS(status) != 0 && prompt->pipe_nb == 1
				&& token[i].cmd && ft_strncmp("exit", token[i].cmd[0], 4) == 0)
				exit(g_exitcode);
		}
		i++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_mgmt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 12:52:58 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/04 15:29:16 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_matrix(char **matrix)
{
	int	index;

	if (!matrix)
		return ;
	index = 0;
	while (matrix[index])
	{
		if (matrix[index])
			free(matrix[index]);
		index++;
	}
	free(matrix);
}

void	terminate_exec(t_prompt *prompt)
{
	int	i;

	dup2(prompt->stdio[READ], STDIN_FILENO);
	close(prompt->stdio[READ]);
	dup2(prompt->stdio[WRITE], STDOUT_FILENO);
	close(prompt->stdio[WRITE]);
	if (prompt->pipe_nb > 0)
		free(prompt->saved_pid);
	i = 0;
	while (i < prompt->pipe_nb)
	{
		ft_free_matrix(prompt->cmds[i].cmd);
		if (prompt->cmds[i].cmd_path)
			free(prompt->cmds[i].cmd_path);
		i++;
	}
	free(prompt->cmds);
}

void	ft_freetrio(char *s1, char *s2, char *s3)
{
	free(s1);
	free(s2);
	free(s3);
}

void	ft_freeduo(char *s1, char *s2)
{
	free(s1);
	free(s2);
}

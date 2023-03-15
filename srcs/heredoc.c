/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:10:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/15 15:03:43 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(char *limiter, int var_expand)
{
	char	*stash = NULL;
	char	*buffer = NULL;
	int		ends[2];
	
	pipe(ends);
	while (TRUE)
	{
		//write(1, "> ", 2);
		// write(1, "-- Just Before GNL\n", 19);
		//buffer = get_next_line(STDIN_FILENO);
		buffer = readline("> ");
        if (!buffer)
            exit_msg(); // if I simply return NULL, execve will run
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0 && ft_strlen(buffer) - 1 == ft_strlen(limiter))
		{
			free(buffer);
			break ;
		}
		// Interprete environment variables
		while (ft_strchr_mod(buffer, '$') != -1 && var_expand == TRUE)
			buffer = expand_variable(buffer);
		stash = ft_strjoin_trio(stash, buffer, "\n");
		//stash = ft_strjoin_mod(stash, buffer);
	}
	write(ends[1], stash, ft_strlen(stash));
	free(stash);
	close(ends[1]);
	return (ends[0]);
}

// Similar to get_variable_environment()
char	*get_envp_variable(char *variable)
{
	int index = 0;

	variable = ft_strjoin(variable, "=");
	int len = ft_strlen(variable);
	while (g_environment[index])
	{
		if (ft_strncmp(g_environment[index], variable, len) == 0)
			return (ft_substr(g_environment[index], len, ft_strlen(g_environment[index])));
		index++;
	}
	return (NULL);
}

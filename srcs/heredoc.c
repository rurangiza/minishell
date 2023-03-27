/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:10:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/22 11:59:51 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(char *limiter, int var_expand)
{
	char	*stash = NULL;
	char	*buffer = NULL;
	int		ends[2];
	
	if (pipe(ends) == -1)
		return (-1);
	//printf(CBLUE"Delimiter = %s\n"CRESET, limiter);
	while (TRUE)
	{
		buffer = readline("> ");
        if (buffer == NULL)
            exit_msg();
		if (ft_strncmp(buffer, limiter, ft_strlen(limiter)) == 0
			&& ft_strlen(buffer) == ft_strlen(limiter))
		{
			free(buffer);
			break ;
		}
		while (ft_strchr_mod(buffer, '$') != -1 && var_expand == TRUE)
			buffer = expand_variable(buffer);
		stash = ft_strjoin_trio(stash, buffer, "\n");
		buffer = NULL;
	}
	write(ends[WRITE], stash, ft_strlen(stash));
	free(stash);
	close(ends[WRITE]);
	return (ends[READ]);
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

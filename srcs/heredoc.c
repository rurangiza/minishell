/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:10:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/04 11:59:24 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(char *limiter, int var_expand, t_prompt *prompt)
{
	char	*stash;
	char	*buffer;
	int		ends[2];

	init_heredoc(limiter, ends, &stash, &buffer);
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
			buffer = expand_variable(buffer, prompt->envp);
		stash = ft_strjoin_trio(stash, buffer, "\n");
		buffer = NULL;
	}
	write(ends[WRITE], stash, ft_strlen(stash));
	free(stash);
	close(ends[WRITE]);
	return (ends[READ]);
}

///////////////////////////////////////////////////////////////////////////////

void	init_heredoc(char *limiter, int *ends, char **stash, char **buffer)
{
	*stash = NULL;
	*buffer = NULL;
	if (pipe(ends) == -1)
		return ;
	if (limiter)
		printf(CBOLD"Enter input below. Write \033[31m%s\033[0m to exit\n"
			CRESET, limiter);
}

///////////////////////////////////////////////////////////////////////////////

// Similar to get_variable_environment()
char	*get_envp_variable(char *variable, char **envp)
{
	char	*prefix;
	int		index;
	int		len;

	prefix = ft_strjoin(variable, "=");
	len = ft_strlen(prefix);
	index = 0;
	while (envp[index])
	{
		if (ft_strncmp(envp[index], prefix, len) == 0)
		{
			free(prefix);
			return (ft_substr(envp[index], len, ft_strlen(envp[index])));
		}
		index++;
	}
	free(prefix);
	return (NULL);
}

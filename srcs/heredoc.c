/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:10:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/31 13:24:51 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	heredoc(char *limiter, int var_expand, t_prompt *prompt)
{
	char	*stash = NULL;
	char	*buffer = NULL;
	int		ends[2];

	if (pipe(ends) == -1)
		return (-1);
	if(limiter)
		printf(CBOLD"Enter input below. Write \033[31m%s\033[0m to exit\n"CRESET, limiter);
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

// Similar to get_variable_environment()
char	*get_envp_variable(char *variable, char **envp)
{
	int index = 0;
	char	*tmp;

	tmp = ft_strjoin(variable, "=");
	
	int len = ft_strlen(tmp);
	while (envp[index])
	{
		if (ft_strncmp(envp[index], tmp, len) == 0)
		{
			free(tmp);
			return (ft_substr(envp[index], len, ft_strlen(envp[index])));
		}
		index++;
	}
	free(tmp);
	return (NULL);
}

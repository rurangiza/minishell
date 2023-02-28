/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 15:10:48 by arurangi          #+#    #+#             */
/*   Updated: 2023/02/28 15:17:20 by arurangi         ###   ########.fr       */
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
		write(1, "> ", 2);
		buffer = get_next_line(STDIN_FILENO);
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
		stash = ft_strjoin_mod(stash, buffer);
	}
	write(ends[1], stash, ft_strlen(stash));
	free(stash);
	close(ends[1]);
	return (ends[0]);
}

char *expand_variable(char *buffer)
{
	int		start;
	int		end;
	char	*tmp;
	char	*variable;
	char	*expanded;
	
	// Find start
	start = ft_strchr_mod(buffer, '$') + 1;
	// Find end
	end = start;
	while (buffer[end] && !ft_isspace(buffer[end]) && buffer[end] != '\"')
		end++;
	// Isolate the variable
	variable = ft_substr(buffer, start, end - start);
	// Check if variable exists in envp
	expanded = getenv(variable);
	if (expanded)
		tmp = ft_strjoin_trio(ft_substr(buffer, 0, start - 1), expanded, buffer + end);
	else
		tmp = ft_strjoin_mod(ft_substr(buffer, 0, start - 1), buffer + end);
	free(variable);
	free(buffer);
	return (tmp);
}

char	*ft_strjoin_trio(char *s1, char *s2, char *s3)
{
	int		i;
	int		j;
	int		k;
	char	*tmp;

	if (!s1)
	{
		s1 = ft_strdup("");
		if (!s1)
			return (NULL);
	}
	if (!s2)
	{
		s2 = ft_strdup("");
		if (!s2)
			return (NULL);
	}
	tmp = malloc(sizeof(char) * ((ft_strlen(s1) + ft_strlen(s2)) + ft_strlen(s3) + 1));
	if (!tmp)
		return (NULL);
	i = -1;
	j = 0;
	k = 0;
	while (s1[++i])
		tmp[i] = s1[i];
	while (s2[j])
		tmp[i++] = s2[j++];
	while (s3[k])
		tmp[i++] = s3[k++];
	tmp[ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3)] = '\0';
	free(s1);
	return (tmp);
}

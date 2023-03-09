/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/09 21:55:39 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *directory, t_prompt *prompt)
{
	char	*path = NULL;
	char	*newold = ft_strjoin_mod(ft_strdup("OLDPWD="), ft_strdup(getcwd(NULL, 0)));
	
	(void)prompt;
	if (!directory)
		path = get_userdir();
	else if (ft_strlen(directory) == 1 && is_special_symbol(directory))
	{
		if (directory[0] == '-')
		{
			path = get_previous_directory();
			if (path == NULL)
			{
				free(newold);
				printf("bash: cd: OLDPWD not set\n");
				return ;
			}
			else
				printf("%s\n", path);
		}
		else if (directory[0] == '~')
			path = get_userdir();
		else if (directory[0] == '/')
			path = ft_strdup("/");
	}
	else
	{
		path = ft_strdup(getcwd(NULL, 0));
		if (ft_strlen(path) == 1 && ft_strncmp(path, "/", 1) == 0)
			path = ft_strjoin(path, directory);
		else
			path = ft_strjoin_trio(path, "/", directory);
	}
    if (chdir(path) == -1)
	{
		free(newold);
		perror(CRED"chdir"CRESET);
	}
	else
		update_oldpwd(newold);
	free(path);
}

char	*get_userdir(void)
{
	char	*username;
	char	*path;

	username = ft_strdup(getenv("USER"));
	if (username == NULL)
		return (NULL);
	path = ft_strdup("/Users/");
	return (ft_strjoin(path, username));
}

char	*get_previous_directory(void)
{
	int index = 0;

	while (g_environment[index])
	{
		if (ft_strncmp(g_environment[index], "OLDPWD=", 7) == 0)
			return (ft_substr(g_environment[index], 7, ft_strlen(g_environment[index])));
		index++;
	}
	return (NULL);
}

void	update_oldpwd(char *newold)
{
	int	index;

	index = 0;
	while (g_environment[index])
	{
		if (ft_strncmp(g_environment[index], "OLDPWD=", 7) == 0)
		{
			free(g_environment[index]);
			g_environment[index] = newold;
			return ;
		}
		index++;
	}
	add_missing_oldpwd(newold);
}

void	add_missing_oldpwd(char *newold)
{
	int size;
	int i;
	char **tmp;

	size = 0;
	while (g_environment[size])
		size++;
	size += 1;
	tmp = malloc((size + 1) * sizeof(char *));
	
	tmp[0] = newold;
	
	i = 1;
	int j = 0;
	while (g_environment[j])
	{
		tmp[i++] = ft_strdup(g_environment[j++]);
	}
	tmp[i] = NULL;
	ft_free_matrix(g_environment);
	g_environment = tmp;
}

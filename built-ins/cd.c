/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Arsene <Arsene@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/10 12:56:33 by Arsene           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *directory)
{
	char	*path = NULL;
	char	*newold = ft_strjoin_mod(ft_strdup("OLDPWD="), ft_strdup(getcwd(NULL, 0)));
	
	//path = get_userdir();
	if (!directory)
		path = get_variable_in_environment("HOME=");
	else if (ft_strlen(directory) == 1 && is_special_symbol(directory))
	{
		if (directory[0] == '-')
		{
			path = get_variable_in_environment("OLDPWD=");
			if (path == NULL)
			{
				free(newold);
				return ;
			}
			else
				printf("%s\n", path);
		}
		else if (directory[0] == '~')
			path = ft_strdup(getenv("HOME"));
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
	if (!path)
	{
		free(newold);
		return ;
	}
    if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", directory);
		free(newold);
	}
	else
		update_oldpwd(newold);
	free(path);
}

char	*get_variable_in_environment(char *variable)
{
	int index = 0;
	int	var_length = ft_strlen(variable);

	while (g_environment[index])
	{
		if (ft_strncmp(g_environment[index], variable, var_length) == 0)
			return (ft_substr(g_environment[index], var_length, ft_strlen(g_environment[index])));
		index++;
	}
	write(1, "bash: cd: ", 10);
	index = 0;
	while (variable[index] && variable[index] != '=')
		write(1, &variable[index++], 1);
	write(1, " not set\n", 9);
	return (NULL);
	//char	*username;
	//char	*path;

	// username = ft_strdup(getenv("USER"));
	// if (username == NULL)
	// 	return (NULL);
	// path = ft_strdup("/Users/");
	//path = ft_strdup(getenv("HOME"));
	//return (ft_strjoin(path, username));
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

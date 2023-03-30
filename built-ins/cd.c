/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/30 13:56:28 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *directory, t_prompt *prompt)
{
	char	*path = NULL;
	char	*oldpwd = ft_strjoin_mod(ft_strdup("OLDPWD="), ft_strdup(getcwd(NULL, 0)));
	char	*pwd;
	
	//path = get_userdir();
	if (!directory)
		path = get_variable_in_environment("HOME=", prompt);
	else if (ft_strlen(directory) == 1 && is_special_symbol(directory))
	{
		if (directory[0] == '-')
		{
			path = get_variable_in_environment("OLDPWD=", prompt);
			if (path == NULL)
			{
				free(oldpwd);
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
	else if (directory[0] == '/')
	{
		// Do this
		path = ft_strdup(directory);
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
		free(oldpwd);
		return ;
	}
    if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", directory);
		free(oldpwd);
	}
	else
	{
		char *tmp = ft_strdup("PWD=");
		pwd = ft_strjoin(tmp, path);
		free(tmp);
		update_pwd(oldpwd, pwd, prompt);
	}
	free(path);
}

char	*get_variable_in_environment(char *variable, t_prompt *prompt)
{
	int index = 0;
	int	var_length = ft_strlen(variable);

	while (prompt->envp[index])
	{
		if (ft_strncmp(prompt->envp[index], variable, var_length) == 0)
			return (ft_substr(prompt->envp[index], var_length, ft_strlen(prompt->envp[index])));
		index++;
	}
	write(1, "bash: cd: ", 10);
	index = 0;
	while (variable[index] && variable[index] != '=')
		write(1, &variable[index++], 1);
	write(1, " not set\n", 9);
	return (NULL);
}

char	*getenv_custm(char *variable, t_prompt *prompt)
{
	int index = 0;
	int	var_length = ft_strlen(variable);

	while (prompt->envp[index])
	{
		if (ft_strncmp(prompt->envp[index], variable, var_length) == 0)
			return (ft_substr(prompt->envp[index], var_length, ft_strlen(prompt->envp[index])));
		index++;
	}
	index = 0;
	return (NULL);
}

void	update_pwd(char *oldpwd, char *pwd, t_prompt *prompt)
{
	int	index;
	int	found_oldpwd;

	found_oldpwd = 0;
	index = 0;
	while (prompt->envp[index])
	{
		if (ft_strncmp(prompt->envp[index], "OLDPWD=", 7) == 0)
		{
			free(prompt->envp[index]);
			prompt->envp[index] = oldpwd;
			found_oldpwd = 1;
		}
		else if (ft_strncmp(prompt->envp[index], "PWD=", 4) == 0)
		{
			free(prompt->envp[index]);
			prompt->envp[index] = pwd;
		}
		index++;
	}
	if (found_oldpwd == 0)
		add_missing_oldpwd(oldpwd, prompt);
}

void	add_missing_oldpwd(char *newold, t_prompt *prompt)
{
	int size;
	int i;
	char **tmp;

	size = 0;
	while (prompt->envp[size])
		size++;
	size += 1;
	tmp = malloc((size + 1) * sizeof(char *));
	if (!tmp)
		return ;
	
	tmp[0] = newold;
	
	i = 1;
	int j = 0;
	while (prompt->envp[j])
	{
		tmp[i++] = ft_strdup(prompt->envp[j++]);
	}
	tmp[i] = NULL;
	ft_free_matrix(prompt->envp);
	prompt->envp = tmp;
}

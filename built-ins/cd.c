/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/03 15:28:34 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *directory, t_prompt *prompt)
{
	char	*path;
	char	*oldpwd;
	char	*pwd;

	path = NULL;
	if (!directory)
		path = get_variable_in_environment("HOME=", prompt);
	else if (ft_strlen(directory) == 1 && is_special_symbol(directory))
	{
		if (directory[0] == '-')
		{
			path = get_variable_in_environment("OLDPWD=", prompt);
			if (path == NULL)
				return ;
			else
				printf("%s\n", path);
		}
		else if (directory[0] == '~')
			path = ft_strdup(getenv("HOME"));
		else if (directory[0] == '/')
			path = ft_strdup("/");
	}
	else if (directory[0] == '/')
		path = ft_strdup(directory);
	else
	{
		path = getcwd(NULL, 0);
		if (ft_strlen(path) == 1 && ft_strncmp(path, "/", 1) == 0)
			path = ft_strjoin_freeboth(path, directory);
		else
			path = ft_strjoin_trio(path, "/", directory);
	}

	oldpwd = save_cwd();
	if (!path)
		return ;
    if (chdir(path) == -1)
	{
		free(path);
		free(oldpwd);
		printf("bash: cd: %s: No such file or directory\n", directory);
	}
	else
	{
		char *tmp = ft_strdup("PWD=");
		pwd = ft_strjoin_freeboth(tmp, path);
		update_pwd(oldpwd, pwd, prompt);
	}
}

char	*save_cwd(void)
{
	char	*cwd;
	char	*oldpwd;
	
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	oldpwd = ft_strjoin("OLDPWD=", cwd);
	free(cwd);
	return (oldpwd);
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
	{
		free(newold);
		return ;
	}
	
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

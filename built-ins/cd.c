/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/04/04 17:07:14 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *directory, t_prompt *prompt)
{
	char	*path;
	char	*oldpwd;
	char	*prefix;
	char	*pwd;

	path = ft_find_destination(directory, prompt);
	if (!path)
		return ;
	oldpwd = save_cwd();
	if (chdir(path) == -1)
	{
		ft_freeduo(path, oldpwd);
		printf("bash: cd: %s: No such file or directory\n", directory);
	}
	else
	{
		prefix = ft_strdup("PWD=");
		pwd = ft_strjoin_freeboth(prefix, path);
		update_pwd(oldpwd, pwd, prompt);
	}
}

///////////////////////////////////////////////////////////////////////////////

static char	*convert_aliases(char *directory, t_prompt *prompt)
{
	char	*path;

	path = NULL;
	if (directory[0] == '-')
	{
		path = get_variable_in_environment("OLDPWD=", prompt);
		if (path == NULL)
			return (NULL);
		else
			printf("%s\n", path);
	}
	else if (directory[0] == '~')
		path = ft_strdup(getenv("HOME"));
	else if (directory[0] == '/')
		path = ft_strdup("/");
	return (path);
}

char	*ft_find_destination(char *directory, t_prompt *prompt)
{
	char	*path;

	path = NULL;
	if (!directory)
		path = get_variable_in_environment("HOME=", prompt);
	else if (ft_strlen(directory) == 1 && is_path_alias(directory))
		path = convert_aliases(directory, prompt);
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
	return (path);
}

///////////////////////////////////////////////////////////////////////////////

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

///////////////////////////////////////////////////////////////////////////////

void	add_missing_oldpwd(char *newold, t_prompt *prompt)
{
	int		size;
	int		index_dest;
	int		index_src;
	char	**new_envp;

	size = ft_tablen(prompt->envp) + 1;
	new_envp = malloc((size + 1) * sizeof(char *));
	if (!new_envp)
	{
		free(newold);
		return ;
	}
	new_envp[0] = newold;
	index_dest = 1;
	index_src = 0;
	while (prompt->envp[index_src])
	{
		new_envp[index_dest++] = ft_strdup(prompt->envp[index_src++]);
	}
	new_envp[index_dest] = NULL;
	ft_free_matrix(prompt->envp);
	prompt->envp = new_envp;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 14:33:04 by arurangi          #+#    #+#             */
/*   Updated: 2023/03/07 16:28:38 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	cd(char *directory)
{
	char	*path = NULL;

	if (!directory)
		path = get_userdir();
	else if (ft_strlen(directory) == 1 && is_special_symbol(directory))
	{
		if (directory[0] == '-')
		{
			path = ft_strdup(getenv("OLDPWD"));
			printf("OLDPWD = %s\n", path);
		}
		else if (directory[0] == '~')
			path = get_userdir();
		else if (directory[0] == '/')
		{
			path = ft_strdup("/");
		}
	}
	else
	{
		path = ft_strdup(getcwd(NULL, 0));
		if (ft_strlen(path) == 1 && ft_strncmp(path, "/", 1) == 0)
			path = ft_strjoin(path, directory);
		else
			path = ft_strjoin_trio(path, "/", directory);
		
	}
	printf(CRED"%s\n"CRESET, path);
    if (chdir(path) == -1)
		perror(CRED"chdir"CRESET);
	
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

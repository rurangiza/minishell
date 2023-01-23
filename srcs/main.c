/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/01/23 14:11:10 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*find_path(char **envp)
{
	while (ft_strncmp("PATH", *envp, 4))
	{
		envp++;
	}
	return (*envp + 5);
}

char *get_cmd(char *str, char **cmd_path)
{
	char *cmd;
	char *tmp;

	while (*cmd_path)
	{
		tmp = ft_strjoin(*cmd_path, "/");
		cmd = ft_strjoin(tmp, str);
		free(tmp);
		if (access(cmd, 0) == 0)
			return(cmd);
		free(cmd);
		cmd_path++;
	}
	return (NULL);
}


int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *str;
	char *cmd;
	char *path;
	char **cmd_path;
	char **cmd_args;
	int i;
	
	i = 0;
	path = find_path(envp);
	cmd_path = ft_split(path, ':');
	while (1)
	{
		str = readline("$> ");
		add_history(str);
		cmd = get_cmd(str, cmd_path);
		cmd_args = ft_split(str, ' ');
		execve(cmd, cmd_args, envp);
	}
	return (0);
}
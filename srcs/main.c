/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 11:34:14 by akorompa          #+#    #+#             */
/*   Updated: 2023/01/23 14:48:32 by akorompa         ###   ########.fr       */
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

void execute(t_cmd *cmd, char *str, char **envp)
{
	cmd->path = find_path(envp);
	cmd->cmd_path = ft_split(cmd->path, ':');
	cmd->cmd_args = ft_split(str, ' ');
	cmd->cmd = get_cmd(cmd->cmd_args[0], cmd->cmd_path);
	execve(cmd->cmd, cmd->cmd_args, envp);
	
}


int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	char *str;
	t_cmd cmd;
	pid_t process;

	while (1)
	{
		str = readline("$> ");
		add_history(str);
		process = fork();
		if (process == 0)
			execute(&cmd, str, envp);
		waitpid(process, NULL, 0);
	}
	return (0);
}
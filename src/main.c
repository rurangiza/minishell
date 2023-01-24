/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/24 13:02:22 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
 * Pipex
 * Recreating the UNIX mechanism known as pipe "|"
*/

int	main(int arg_count, char **arg_list, char **envp)
{
	t_data	data;
	t_cmd	cmd;
	int		status;
	
	load_data(&data, arg_count, arg_list, envp);
	while (1)
	{
		char	*str = readline("\033[30mminishell >\033[0m ");
		add_history(str);
		pid_t pid = fork();
		if (pid == 0)
		{
			char **tab = ft_split(str, ' ');
			expandor(tab[0], envp);
			
			init_cmd(envp, str, &cmd);
			execve(cmd.path, cmd.args, envp);
		}
		waitpid(pid, &status, 0);
	}	
	return (EXIT_SUCCESS);
}

void	ft_pipex(t_data *data)
{
	pid_t	pid;
	int		pipe_ends[2];
	int		index;

	index = 2;
	while (index <= data->arg_count - 2)
	{
		if (pipe(pipe_ends) == -1)
			exit_msg();
		pid = fork();
		if (pid == -1)
			exit_msg();
		else if (pid == 0)
		{
			if (index == 2)
				first_child(data, pipe_ends);
			else
				last_child(data);
		}
		parent_process(pid, pipe_ends, index, data->arg_count);
		index++;
	}
}



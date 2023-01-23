/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 11:21:06 by Arsene            #+#    #+#             */
/*   Updated: 2023/01/23 16:49:44 by arurangi         ###   ########.fr       */
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
	int		status;

	load_data(&data, arg_count, arg_list, envp);
	
	t_cmd cmd;
	while (1)
	{
		// Lexor
		char *str = readline("\033[30mminishell >\033[0m ");
		add_history(str);
		// Parser
		/*
		 * EXPANDER:
		 * Takes the parser tokens as argument and interprete the environment variables into their corresponding value
		 * It also handles subshells, creates pipes and handles all the opening of input-/output-redirections and storing the correct ones in the executor tokens
		*/
		pid_t pid = fork();
		if (pid == 0)
		{
			char **tab = ft_split(str, ' ');
			expandor(tab[0], envp);
			/*
			 * EXECUTOR:
			 * executes the command. If the given command is an inbuilt, it will just run the command in the same process, if it isn't it will create a child process to run the command in
			*/
			init_cmd(envp, str, &cmd);
			execve(cmd.path, cmd.args, NULL);
		}
		waitpid(pid, &status, 0);
	}
	//ft_pipex(&data);
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



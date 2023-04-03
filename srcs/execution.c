/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/04/03 17:11:55 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

///////////////////////////////////////////////////////////////////////////////

void	execute(t_token *token, t_prompt *prompt)
{	
	int		index;
	int		cmd_type;
	pid_t	pid;

	init_exec(prompt);
	if (!token[0].cmd[0])
	{
		printf(CRED"Error\033[0m No commands detected\n");
		return ;
	}
	index = 0;
	while (index < prompt->pipe_nb)
	{
		if (token[index].cmd && is_builtin(token[index].cmd[0]))
			execute_builtins(token, prompt, index);
		else
		{
			cmd_type = get_cmd_type(prompt->pipe_nb, index);
			createpipe(prompt, cmd_type);
			init_signals_inprocess();
			pid = fork();
			if (pid == -1)
				exit_msg();
			else if (pid == 0)
				child_process(token, prompt, cmd_type, index);
			prompt->saved_pid[index] = pid;
			parent_process(token, prompt, cmd_type);
		}
		index++;
	}
	check_cmds_status(token, prompt);
	terminate_exec(prompt);
}

///////////////////////////////////////////////////////////////////////////////

void	execute_builtins(t_token *token, t_prompt *prompt, int index)
{
	int	status;

	simple_redirect(token, prompt, index);
	status = 0;
	if (ft_strncmp(token->cmd[0], "echo", 4) == 0)
		echo(token);
	else if (ft_strncmp(token->cmd[0], "cd", 2) == 0)
		cd(token->cmd[1], prompt);
	if (ft_strncmp(token->cmd[0], "pwd", 3) == 0)
		pwd(token);
	else if (ft_strncmp(token->cmd[0], "export", 6) == 0)
		export(token, prompt);
	else if (ft_strncmp(token->cmd[0], "unset", 5) == 0)
		unset(token, prompt);
	else if (ft_strncmp(token->cmd[0], "env", 3) == 0)
		env(token, prompt);
	else if (ft_strncmp(token->cmd[0], "exit", 4) == 0)
	{
		status = my_exit(token);
		if (prompt->pipe_nb == 1 && status != -1)
		{
			terminate_exec(prompt);
			exit(status);
		}
	}
}

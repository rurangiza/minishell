/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/04/05 10:13:29 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 
 * Description: 
 * - This function execute commands, handle redirections and exit status
 * Arguments
 * - [0] token :	list of command structures containing valuable data about
 * 					each command 
 * - [1] prompt :	main structure contain all tokens and informations about
 * 					the program such as (envp, nbr of pipes, ...)
*/

void	execute(t_token *token, t_prompt *prompt)
{	
	int		index;
	int		status;

	status = init_exec(token, prompt);
	if (status == STAT_NEG)
		return ;
	index = 0;
	while (index < prompt->pipe_nb)
	{
		if (token[index].cmd && is_builtin(token[index].cmd[0]))
			exec_builtins(token, prompt, index);
		else
			exec_cmds(token, prompt, index);
		index++;
	}
	check_cmds_status(token, prompt);
	terminate_exec(prompt);
}

///////////////////////////////////////////////////////////////////////////////

int	init_exec(t_token *token, t_prompt *prompt)
{
	if (token[0].cmd && !token[0].cmd[0])
	{
		printf(CRED"Error\033[0m No commands detected\n");
		return (STAT_NEG);
	}
	prompt->stdio[0] = dup(STDIN_FILENO);
	prompt->stdio[1] = dup(STDOUT_FILENO);
	if (prompt->pipe_nb > 0)
	{
		prompt->saved_pid = malloc(prompt->pipe_nb * sizeof(pid_t));
		if (!prompt->saved_pid)
			return (STAT_NEG);
	}
	prompt->prevpipe = -1;
	return (STAT_POS);
}

///////////////////////////////////////////////////////////////////////////////

int	get_cmd_type(int size, int index)
{
	if (size == 1)
		return (_single);
	else if (index == size - 1 && index != 0)
		return (_last);
	return (_middle);
}

void	exec_cmds(t_token *token, t_prompt *prompt, int index)
{
	int		cmd_type;
	pid_t	pid;

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

///////////////////////////////////////////////////////////////////////////////

void	exec_builtins(t_token *token, t_prompt *prompt, int index)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/27 14:50:01 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

///////////////////////////////////////////////////////////////////////////////

void	execute(t_token *token, t_prompt *prompt)
{	
	int	index = 0, pipends[2], prevpipe = 69, cmd_type, status;
	pid_t *pid_bucket;
	
	if (prompt->pipe_nb > 0)
	{
		pid_bucket = malloc(prompt->pipe_nb * sizeof(pid_t));
		if (!pid_bucket)
			return ;
	}
	while (index < prompt->pipe_nb)
	{
        cmd_type = get_cmd_type(prompt->pipe_nb, index);
        if (cmd_type == _middle)
		{
			if (pipe(pipends) == -1)
			{
				free(pid_bucket);
				exit_msg();
			}
		}
		if (prompt->pipe_nb == 1 && ft_strncmp("exit", token[index].cmd[0], 4) == 0)
			exit(my_exit(token));
		pid_t pid = fork();
		if (pid == -1)
			exit_msg();
		else if (pid == 0)
		{
			if (cmd_type == _single)
			{
				if (token[index].cmd && is_builtin(token[index].cmd[0]))
					execute_builtins(token);
				else
					single_child(&token[index]);
			}
			else if (cmd_type == _last)
				last_child(&token[index], prevpipe);
			else
				middle_child(&token[index], index, prevpipe, pipends);
		}
		pid_bucket[index] = pid;
		if (cmd_type == _middle)
		{
			close(pipends[WRITE]);
			prevpipe = pipends[READ];
			if (is_empty_pipe(pipends[READ]) && ft_strncmp("cat", token->cmd[0], 3) == 0)
				close(pipends[READ]);
		}
		// else if (cmd_type == _last)
		// 	close(prevpipe);
		index++;
	}
	for (int i = 0; i < prompt->pipe_nb; i++)
	{
		waitpid(pid_bucket[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_tools.exit_code = WEXITSTATUS(status);
			if (prompt->pipe_nb == 1 && token[i].cmd && ft_strncmp("exit", token[i].cmd[0], 4) == 0)
				exit(0);
		}
	}
	if (prompt->pipe_nb > 0)
		free(pid_bucket);
}

///////////////////////////////////////////////////////////////////////////////

int get_cmd_type(int size, int index)
{
    if (size == 1)
        return (_single);
    else if (index == size - 1 && index != 0)
        return (_last);
    return (_middle);
}

///////////////////////////////////////////////////////////////////////////////

char	*find_pathway(void)
{
	int	index = 0;

	while (g_environment[index])
	{
		if (ft_strncmp(g_environment[index], "PATH=", 5) == 0)
			return (&g_environment[index][5]);
		index++;
	}
	return (NULL);
}

void	single_child(t_token *token)
{
	//display_tree(0, __func__, token);
	char *pathway = find_pathway();
	(void)pathway;
	if (token->infile != -1)
		redirect_in(token);
	if (token->outfile != -1)
		redirect_out(token);
	handle_execution_errors(token);
	execve(token->cmd_path, token->cmd, g_environment);
	exit_msg();
}

///////////////////////////////////////////////////////////////////////////////

void	last_child(t_token *token, int prevpipe)
{	
	if (token->infile != -1)
		redirect_in(token);
	else
		dup2(prevpipe, STDIN_FILENO);
	close(prevpipe);
	if (token->outfile != -1)
		redirect_out(token);
	if (token->cmd && is_builtin(token->cmd[0]))
	{
		execute_builtins(token);
		exit(0);
	}
	else
	{
		handle_execution_errors(token);
		execve(token->cmd_path, token->cmd, g_environment);
		exit_msg();
	}
}

///////////////////////////////////////////////////////////////////////////////

void	middle_child(t_token *token, int index, int prevpipe, int *pipends)
{
	close(pipends[READ]);
		
	if (token->infile != -1)
		redirect_in(token);
	else if (index > 0)
	{
		dup2(prevpipe, STDIN_FILENO);
		close(prevpipe);
	}
	if (token->outfile != -1)
		redirect_out(token);
	else
		dup2(pipends[WRITE], STDOUT_FILENO);
	close(pipends[WRITE]);
	if (token->cmd && is_builtin(token->cmd[0]))
	{
		execute_builtins(token);
		exit(0);
	}
	else
	{
		handle_execution_errors(token);
		execve(token->cmd_path, token->cmd, g_environment);
		exit_msg();
	}
}

///////////////////////////////////////////////////////////////////////////////

void    parent_process(int child_pid, t_state cmd_type, int *pipends, int *prevpipe)
{
	(void)child_pid;
    if (cmd_type == _middle)
    {
        close(pipends[WRITE]);
        *prevpipe = pipends[READ];
    }
    else if (cmd_type == _last)
        close(*prevpipe);
}

///////////////////////////////////////////////////////////////////////////////

int	execute_builtins(t_token *token)
{
	int exit_code;

	exit_code = 0;
	if (ft_strncmp(token->cmd[0], "echo", 4) == 0)
		echo(token);
	else if (ft_strncmp(token->cmd[0], "cd", 2) == 0)
		cd(token->cmd[1]);
	if (ft_strncmp(token->cmd[0], "pwd", 3) == 0)
		pwd(token);
	else if (ft_strncmp(token->cmd[0], "export", 6) == 0)
		export(token);
	else if (ft_strncmp(token->cmd[0], "unset", 5) == 0)
		unset(token);
	else if (ft_strncmp(token->cmd[0], "env", 3) == 0)
		env(token);
	else if (ft_strncmp(token->cmd[0], "exit", 4) == 0)
		exit(my_exit(token));
	return (exit_code);
}

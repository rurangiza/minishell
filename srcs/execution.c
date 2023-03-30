/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akorompa <akorompa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/30 15:14:44 by akorompa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	destroy(t_prompt *prompt)
{
	int i;
	
	i = 0;	
	while (i < prompt->pipe_nb)	
	{
		ft_free_matrix(prompt->cmds[i].cmd);
		if (prompt->cmds[i].cmd_path)
			free(prompt->cmds[i].cmd_path);
		if (prompt->cmds[i].delimiter)
			free(prompt->cmds[i].delimiter);
		i++;	
	}
	free(prompt->cmds);
}

///////////////////////////////////////////////////////////////////////////////

void	execute(t_token *token, t_prompt *prompt)
{	
	int		index;
	int		cmd_type;
	int		status;
	pid_t	pid;

	// init_execution()
	prompt->stdio[0] = dup(STDIN_FILENO);
	prompt->stdio[1] = dup(STDOUT_FILENO);
	index = 0;
	if (prompt->pipe_nb > 0)
	{
		prompt->saved_pid = malloc(prompt->pipe_nb * sizeof(pid_t));
		if (!prompt->saved_pid)
			return;
	}
	prompt->prevpipe = -1;

	// Loop through all commands
	while (index < prompt->pipe_nb)
	{
		if (is_builtin(token[index].cmd[0]))
			execute_builtins(token, prompt);
		else
		{
			cmd_type = get_cmd_type(prompt->pipe_nb, index);
			if (cmd_type == _middle)
			{
				if (pipe(prompt->pipends) == -1)
				{
					free(prompt->saved_pid);
					exit_msg();
				}
			}
			signal(SIGINT, handle_inprocess_signals);
			signal(SIGQUIT, SIG_IGN);
			pid = fork();
			if (pid == -1)
				exit_msg();
			else if (pid == 0)
			{
				//signal(SIGINT, handle_signals);
				if (cmd_type == _single)
				{
					if (token[index].cmd && is_builtin(token[index].cmd[0]))
						execute_builtins(token, prompt);
					else
						single_child(&token[index], prompt);
				}
				else if (cmd_type == _last)
					last_child(&token[index], prompt->prevpipe, prompt);
				else
					middle_child(&token[index], index, prompt->prevpipe, prompt->pipends, prompt);
			}
			prompt->saved_pid[index] = pid;
			if (cmd_type == _middle)
			{
				close(prompt->pipends[WRITE]);
				prompt->prevpipe = prompt->pipends[READ];
				if (is_empty_pipe(prompt->pipends[READ]) && ft_strncmp("cat", token->cmd[0], 3) == 0)
					close(prompt->pipends[READ]);
			}
		}
		index++;
	}
	for (int i = 0; i < prompt->pipe_nb; i++)
	{
		waitpid(prompt->saved_pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_exitcode = WEXITSTATUS(status);
			if (WEXITSTATUS(status) != 0 && prompt->pipe_nb == 1 && ft_strncmp("exit", token[i].cmd[0], 4) == 0)
			{
				printf("Code before out = %i\n", g_exitcode);
				exit(g_exitcode);
			}
			if (WIFSIGNALED(status) && WTERMSIG(status) == SIGINT)
			{
				printf("Received SIGINT\n");
				g_tools.killed = 1;
			}
		}
	}
	// terminate_execution()
	dup2(prompt->stdio[0], STDIN_FILENO);
	close(prompt->stdio[0]);
	dup2(prompt->stdio[1], STDOUT_FILENO);
	close(prompt->stdio[1]);
	if (prompt->pipe_nb > 0)
		free(prompt->saved_pid);
	destroy(prompt);
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

void	single_child(t_token *token, t_prompt *prompt)
{
	//display_tree(1, __func__, token);
	(void)prompt;
	if (token->infile != -1)
		redirect_in(token, prompt);
	if (token->outfile != -1)
		redirect_out(token);
	handle_execution_errors(token, prompt);
	execve(token->cmd_path, token->cmd, prompt->envp);
	exit_msg();
}

///////////////////////////////////////////////////////////////////////////////

void	last_child(t_token *token, int prevpipe, t_prompt *prompt)
{	
	if (token->infile != -1)
		redirect_in(token, prompt);
	else
		dup2(prevpipe, STDIN_FILENO);
	close(prevpipe);
	if (token->outfile != -1)
		redirect_out(token);
	if (token->cmd && is_builtin(token->cmd[0]))
	{
		execute_builtins(token, prompt);
		exit(0);
	}
	else
	{
		handle_execution_errors(token, prompt);
		execve(token->cmd_path, token->cmd, prompt->envp);
		exit_msg();
	}
}

///////////////////////////////////////////////////////////////////////////////

void	middle_child(t_token *token, int index, int prevpipe, int *pipends, t_prompt *prompt)
{
	close(pipends[READ]);
		
	if (token->infile != -1)
		redirect_in(token, prompt);
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
		execute_builtins(token, prompt);
		exit(0);
	}
	else
	{
		handle_execution_errors(token, prompt);
		execve(token->cmd_path, token->cmd, prompt->envp);
		exit_msg();
	}
}

///////////////////////////////////////////////////////////////////////////////

void    parent_process(int child_pid, t_state cmd_type, int *pipends, int *prevpipe, t_prompt *prompt)
{
	(void)child_pid;
	(void)prompt;
    if (cmd_type == _middle)
    {
        close(pipends[WRITE]);
        *prevpipe = pipends[READ];
    }
    else if (cmd_type == _last)
        close(*prevpipe);
}

///////////////////////////////////////////////////////////////////////////////

void	execute_builtins(t_token *token, t_prompt *prompt)
{
	int	status;
	
	if (token->infile != -1)
	{
		printf("Chanding IN\n");
		redirect_in(token, prompt);
	}
	if (token->outfile != -1)
	{
		printf("Chanding OUT\n");
		redirect_out(token);
	}
	if (index > 0)
		close(prompt->prevpipe);
	
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
		if (prompt->pipe_nb == 1 )
			exit(status);
	}
	//dup2(fdout, STDOUT_FILENO);
}

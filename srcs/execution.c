/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/28 12:56:56 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

///////////////////////////////////////////////////////////////////////////////

void	execute(t_token *token, t_prompt *prompt)
{	
	int		index;
	int		cmd_type;
	int		status;
	pid_t	pid;
	
	// Initialization
	index = 0;
	if (prompt->pipe_nb > 0)
	{
		prompt->saved_pid = malloc(prompt->pipe_nb * sizeof(pid_t));
		if (!prompt->saved_pid)
			return ;
	}
	prompt->prevpipe = -1;

	// handle exit() before pipes and forks
	if (prompt->pipe_nb == 1 && token[0].cmd && ft_strncmp("exit", token[0].cmd[0], 4) == 0)
	{
		status = my_exit(token);
		exit(status);
	}

	// Loop through all commands
	while (index < prompt->pipe_nb)
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
		pid = fork();
		if (pid == -1)
			exit_msg();
		else if (pid == 0)
		{
			if (cmd_type == _single)
			{
				if (token[index].cmd && is_builtin(token[index].cmd[0]))
					execute_builtins(token, prompt->pipe_nb);
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
		index++;
	}
	for (int i = 0; i < prompt->pipe_nb; i++)
	{
		waitpid(prompt->saved_pid[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_tools.exit_code = WEXITSTATUS(status);
			if (WEXITSTATUS(status) != 0 && prompt->pipe_nb == 1 && ft_strncmp("exit", token[i].cmd[0], 4) == 0)
			{
				printf("Code before out = %i\n", g_tools.exit_code);
				exit(g_tools.exit_code);
			}
		}
	}
	// free allocated memory
	if (prompt->pipe_nb > 0)
		free(prompt->saved_pid);
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

void	single_child(t_token *token, t_prompt *prompt)
{
	//display_tree(1, __func__, token);
	(void)prompt;
	if (token->infile != -1)
		redirect_in(token);
	if (token->outfile != -1)
		redirect_out(token);
	handle_execution_errors(token);
	execve(token->cmd_path, token->cmd, g_environment);
	exit_msg();
}

///////////////////////////////////////////////////////////////////////////////

void	last_child(t_token *token, int prevpipe, t_prompt *prompt)
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
		execute_builtins(token, prompt->pipe_nb);
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

void	middle_child(t_token *token, int index, int prevpipe, int *pipends, t_prompt *prompt)
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
		execute_builtins(token, prompt->pipe_nb);
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

void	execute_builtins(t_token *token, int nbr_of_cmds)
{
	int	exit_code;
	
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
	{
		exit_code = my_exit(token);
		if (nbr_of_cmds == 1 )
			exit(exit_code);
	}
	exit(exit_code);
}

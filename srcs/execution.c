/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/20 17:14:31 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

///////////////////////////////////////////////////////////////////////////////

void	execute(t_token *token, t_prompt *prompt)
{
	//display_start();
	
	int	index = 0, pipends[2], prevpipe = 69, cmd_type, status;
	pid_t *pid_bucket;
	int result_wpid;
	
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
			//close(pipends[READ]); (BEFORE)
			if (pipe(pipends) == -1)
				exit_msg();
		}
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
		}
		else if (cmd_type == _last) //(PROBLEM WITH THIS)
			close(prevpipe);
			
		result_wpid = waitpid(pid, &status, WNOHANG);
		if (result_wpid > 0)
		{
			// Child process has terminated, retrieve exit status
            if (WIFEXITED(status)) {
                printf("Child process exited with status %d\n", WEXITSTATUS(status));
            } else {
                printf("Child process terminated abnormally\n");
            }
		}
		index++;
	}
	for (int i = 0; i < prompt->pipe_nb; i++)
	{
		//printf("index %d, lim %d, pid_buck %d\n", i, prompt->pipe_nb, pid_bucket[i]);
		waitpid(pid_bucket[i], &status, 0);
		if (WIFEXITED(status))
		{
			g_tools.exit_code = WEXITSTATUS(status);
			// if (WEXITSTATUS(status) != 0 && cmd_type == _last) // cmd_type always true because above
			// 	return ;
			// else 
			if (prompt->pipe_nb == 1 && token[i].cmd && ft_strncmp("exit", token[i].cmd[0], 4) == 0)
				exit(0);
		}
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGTERM)
			{
				printf("-- got terminated\n");
				return ;
			}
			else if (WTERMSIG(status) == SIGKILL)
			{
				printf("-- got killed\n");
				return ;
			}
		}
		//printf("index %d, lim %d, pid_buck %d\n", i, prompt->pipe_nb, pid_bucket[i]);
	}
	if (prompt->pipe_nb > 0)
		free(pid_bucket);
	//display_end();
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
	//display_tree(1, __func__, token);
	
	char *pathway = find_pathway();
	(void)pathway;
	if (token->infile != -1)
		redirect_in(token);
	if (token->outfile != -1)
		redirect_out(token);
	//printf("Cmd = %s\nInfile = %i\nOutfile = %i\n", token->cmd[0], token->infile, token->outfile);
	
	// if (token->cmd == NULL)
	// {
	// 	printf("minishell: syntax error near unexpected token `newline'\n");
	// 	exit(258);
	// }
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
	{
		//printf("  |__. prevpipe (%i) -> STDIN\n", prevpipe);
		dup2(prevpipe, STDIN_FILENO); // duppign a closed file with STDIN
	}
	close(prevpipe);
	if (token->outfile != -1)
		redirect_out(token);

	if (token->cmd == NULL)
	{
		exit_wrongcmd_msg("", 127);
	}
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
	
	// if (token->cmd == NULL)
	// 	exit_wrongcmd_msg("", 127);
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
		//close(pipends[READ]);
    }
    else if (cmd_type == _last)
        close(*prevpipe);
}

///////////////////////////////////////////////////////////////////////////////

void	execute_builtins(t_token *token)
{
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
		my_exit(token);
}
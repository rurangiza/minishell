/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/03/06 10:31:25 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_token *token, int nbr_of_pipes)
{
	int	index = 0, pipends[2], prevpipe = 69, cmd_type;

	while (index < nbr_of_pipes)
	{
        cmd_type = get_cmd_type(nbr_of_pipes, index);
        if (cmd_type == _middle)
		{
			if (pipe(pipends) == -1)
				exit_msg();
		}
		
		if (is_builtin(token[index].cmd[0]))
			execute_builtins(token);
		else
		{
			pid_t pid = fork();
			if (pid == -1)
				exit_msg();
			else if (pid == 0)
			{
				if (cmd_type == _single)
					single_child(&token[index]);
				else if (cmd_type == _last)
					last_child(&token[index], prevpipe);
				else
					middle_child(&token[index], index, prevpipe, pipends);
			}
			parent_process(pid, cmd_type, pipends, &prevpipe);
		}
		index++;
	}
	hanging_cats(token);
}

int get_cmd_type(int size, int index)
{
    if (size == 1)
        return (_single);
    else if (index == size - 1 && index != 0)
        return (_last);
    return (_middle);
}

void	single_child(t_token *token)
{
	if (token->infile != -1)
		redirect_in(token);
	if (token->outfile != -1)
		redirect_out(token);

	// Execute commands
	if (token->cmd && is_builtin(token->cmd[0]))
	{
		execute_builtins(token);
		exit(0);
	}
	else
	{
		execve(token->cmd_path, token->cmd, g_environment);
		exit_msg();
	}
}

void	last_child(t_token *token, int prevpipe)
{
	printf("----- Last\n");
	if (token->infile != -1)
		redirect_in(token);
	else
		dup2(prevpipe, STDIN_FILENO);
	close(prevpipe);
	if (token->outfile != -1)
		redirect_out(token);

	// Execute commands
	if (is_builtin(token->cmd[0]))
		execute_builtins(token);
	else
		execve(token->cmd_path, token->cmd, g_environment);
	exit_msg();
}

void	middle_child(t_token *token, int index, int prevpipe, int *pipends)
{
	close(pipends[READ]);
	if (token->infile != -1)
		redirect_in(token);
	else if (index > 0)
		dup2(prevpipe, STDIN_FILENO);
	if (index != 0)
		close(prevpipe);

	if (ft_strncmp(token->cmd[0], "cat", 3) == 0 && token->cmd[1] == NULL && index == 0)
		exit(0);

	if (token->outfile != -1)
		redirect_out(token);
	else
	{
		if (dup2(pipends[WRITE], STDOUT_FILENO) == -1)
			printf("Error with DUP2()\n");
	}	
	close(pipends[WRITE]);
	
	// Execute commands
	if (is_builtin(token->cmd[0]))
		execute_builtins(token);
	else
		execve(token->cmd_path, token->cmd, g_environment);
	exit_msg();
}

void    parent_process(int child_pid, t_state cmd_type, int *pipends, int *prevpipe)
{
    int status;

    if (cmd_type == _middle)
    {
        close(pipends[WRITE]);
        *prevpipe = pipends[READ];
    }
    else if (cmd_type == _last)
        close(*prevpipe);
    waitpid(child_pid, &status, 0);
	if (WIFEXITED(status))
	{
		if (WEXITSTATUS(status) != 0 && cmd_type == _last)
			return ;
	}
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGTERM)
			return ;
		else if (WTERMSIG(status) == SIGKILL)
			return ;
	}
}

void	execute_builtins(t_token *token)
{
	if (ft_strncmp(token->cmd[0], "echo", 4) == 0)
		echo(token);
	// else if (ft_strncmp(token->cmd[0], "cd", 2) == 0)
	// 	cd(token);
	if (ft_strncmp(token->cmd[0], "pwd", 3) == 0)
		pwd(token);
	else if (ft_strncmp(token->cmd[0], "export", 6) == 0)
		export(token);
	else if (ft_strncmp(token->cmd[0], "unset", 5) == 0)
		unset(token);
	else if (ft_strncmp(token->cmd[0], "env", 3) == 0)
		env(token);
	// else if (ft_strncmp(token->cmd[0], "exit", 4) == 0)
	// 	exit(token);

	// printf(CBLUE"---- EXECUTE_BUILTINS() -----\n"CRESET);
	// for (int i = 0; g_environment[i]; i++)
	// 	printf("%s\n", g_environment[i]);
}
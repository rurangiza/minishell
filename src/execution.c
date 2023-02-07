/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arurangi <arurangi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 20:01:10 by Arsene            #+#    #+#             */
/*   Updated: 2023/02/07 16:54:39 by arurangi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	execute(t_token *tree, int nbr_of_pipes)
{
	int	index = 0, pipends[2], prevpipe = 69, pipeline_position;

	while (index < nbr_of_pipes)
	{
        pipeline_position = get_pipeline_position(nbr_of_pipes, index);
        if (pipeline_position == _middle)
		{
			if (pipe(pipends) == -1)
				exit_msg();
		}
        pid_t pid = fork();
        if (pid == -1)
            exit_msg();
        else if (pid == 0)
		{
			if (pipeline_position == _single) 
				single_child(&tree[index]);
			else if (pipeline_position == _last)
				last_child(&tree[index], prevpipe);
			else
				middle_child(&tree[index], index, prevpipe, pipends);
		}
        parent_process(pid, pipeline_position, pipends, &prevpipe);
		index++;
	}
}

/*
 * - no need to use pipe
*/
void	single_child(t_token *token)
{
	int	error_code;

	if (token->infile != -1)
		redirect_in(token);
	if (token->outfile != -1)
		redirect_out(token);
	error_code = execvp(token->cmd[0], token->cmd);
	if (error_code == -1)
		exit_msg();
}

/*
 * - no need to create a pipe, need to redirect output
*/
void	last_child(t_token *token, int prevpipe)
{
	int error_code;

	if (token->infile != -1)
		redirect_in(token);
	else
		dup2(prevpipe, STDIN_FILENO);
	close(prevpipe);
	if (token->outfile != -1)
		redirect_out(token);
	error_code = execvp(token->cmd[0], token->cmd);
	if (error_code == -1)
		exit_msg();
}

/*
 * - create pipe, redirect I/O
*/
void	middle_child(t_token *token, int index, int prevpipe, int *pipends)
{
	int error_code;
	
	close(pipends[READ]);
	if (token->infile != -1)
		redirect_in(token);
	else if (index > 0)
		dup2(prevpipe, STDIN_FILENO);
	close(prevpipe);
	if (token->outfile != -1)
		redirect_out(token);
	else
		dup2(pipends[WRITE], STDOUT_FILENO);
	close(pipends[WRITE]);
	error_code = execvp(token->cmd[0], token->cmd);
	if (error_code == -1)
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
